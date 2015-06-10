//#####################################################################################
//	Файл				Engine.cpp
//	Название:		Движок меню. На базе автомата состояний.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 22 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################


#include "stm32f4xx_hal.h"
#include "__Engine.hpp"
#include "__Parameters.hpp"
#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"

using namespace src;


//  Конструктор
MenuEngine::MenuEngine(IDisplay* display)
  {
    _display = display;
    _editor.setDisplay(display);
  }

//--------------------------------------------------------------------------------------------------------
// Метод PutToMenu
// Положить указатель на объект в вектор, содержащий все элементы меню
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::putItem (IMenuItem* menuItem) // Положить ссылку на объект в карты  
{
  _menuIdVector.push_back( menuItem );
}


//--------------------------------------------------------------------------------------------------------
// Метод findAvailableElements
// Производит поиск доступных элементов меню на данном уровне меню
//--------------------------------------------------------------------------------------------------------
//findIndexMenuItems (vector<IMenuItem*> &resultVector, char* indexString)
void MenuEngine::findAvailableElements(vector<IMenuItem*> &resultVector, char* indexString)
{
  uint16_t i, n;
  uint16_t lenthIndexString;
  char* string_found, *first_point, *last_point;

  resultVector.clear();
  n = _menuIdVector.size();
  lenthIndexString = strlen(indexString);

  if (lenthIndexString){
   for (i=0; i < n; i++){
     string_found = strstr (_menuIdVector[i]->getMenu(),indexString);
     if(string_found){  // Символ найден
       // Если после indexString есть точка, и она является последней, то это элемент текущего меню 
       first_point = strchr((string_found + lenthIndexString),'.');
       last_point = strrchr((string_found + lenthIndexString),'.');
       if( first_point && (first_point == last_point) ){
         resultVector.push_back(_menuIdVector[i]);
       }
     }
   }
  }
  else{  // Длина индекса меню нулевая - выводятся элемены высшего уровня (A,B,C,...)
   for (i=0; i < n; i++){
     string_found = strstr (_menuIdVector[i]->getMenu(),".");
     if(!string_found){  // Символ не найден - элемент высшего уровня меню
       resultVector.push_back(_menuIdVector[i]);
     }
   }
  }
}


//--------------------------------------------------------------------------------------------------------
// Метод findAvailableElements
// Производит поиск доступных элементов меню на данном уровне меню
//--------------------------------------------------------------------------------------------------------
void MenuEngine::findAvailableElements(char* indexString)
{
/*  uint16_t i, n;
  uint16_t lenthIndexString;
  char* string_found;

  _availableElements.clear();
  n = _menuIdVector.size();
  lenthIndexString = strlen(indexString);

  for (i=0; i < n; i++){
    string_found = strstr (_menuIdVector[i]->getMenu(),indexString);
    if(string_found)  // Символ найден
    {
      if( strchr((string_found + lenthIndexString),'.') == strrchr((string_found + lenthIndexString),'.') ){
        _availableElements.push_back(_menuIdVector[i]);
        printf("   element %s added\n", _menuIdVector[i]->getMenu());
      }
    }
  }*/
  findAvailableElements(_availableElements, indexString);
}



//--------------------------------------------------------------------------------------------------------
// Метод getCountOfAvailableElements
// Возвращает количество элементов на данном уровне
//--------------------------------------------------------------------------------------------------------
uint16_t MenuEngine::getCountOfAvailableElements(void)
{
  return _availableElements.size();
}


//--------------------------------------------------------------------------------------------------------
// Метод getAvailableElement
// Возвращает указатель на элемент меню на данном уровне. index[0..getCountOfAvailableElements]
//--------------------------------------------------------------------------------------------------------
IMenuItem*  MenuEngine::getAvailableElement(uint16_t index)
{
 return _availableElements[index];
}

//--------------------------------------------------------------------------------------------------------
// Метод getCountOfElements
// Возвращает общее количество элементов
//--------------------------------------------------------------------------------------------------------
uint16_t  MenuEngine::getCountOfElements(void)
{
  return _menuIdVector.size();

}


//========================================================================================================
// Методы навигации по элементам меню
//========================================================================================================

//--------------------------------------------------------------------------------------------------------
// Метод menuMoveDown
// Перемещает указатель _im на 1 позицию вниз
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::menuMoveDown (void)
{
  if((_im+1) < getCountOfAvailableElements()) {
    _im++;
  }
}


//--------------------------------------------------------------------------------------------------------
// Метод menuMoveUp
// Перемещает указатель _im на 1 позицию вверх
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::menuMoveUp (void)
{
  if(_im){
    _im--;
  }
}


//--------------------------------------------------------------------------------------------------------
// Метод menuMoveForward
// Перемещает состояние (уровень) меню вперед
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::menuMoveForward (void)
{
  char str[16];
  vector<IMenuItem*> menuElements;
  // поиск элементов следующего уровня меню
  // если они есть, то переход.

  strncpy(str, (getAvailableElement(getIm()))->getMenu(), sizeof(str)); // В str заносится значение меню, на которй указывает _im
  
  findAvailableElements( menuElements, str);  // Поиск элементов меню, являющихся подменю значения str
  if (menuElements.size()){
    findAvailableElements(str);
    setMenuValue(str);
  }
}


//--------------------------------------------------------------------------------------------------------
// Метод menuMoveBackward
// Перемещает состояние (уровень) меню назад
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::menuMoveBackward (void)
{
  char str[16];
  char* ptr;
  
  strncpy(str, getMenuValue(), sizeof(str));
  ptr = strrchr(str, '.');  // Поиск последней точки
  if (ptr){                 // Отрезание индекса после точки (B.0.1 -> B.0)
    strcpy(ptr, "");
  }
   else{
    strcpy(str, "");
   }
  setMenuValue(str);
  findAvailableElements(str);
  
}


//--------------------------------------------------------------------------------------------------------
//  Циклический обработчик. Обрабатывает пришедшие команды. Вызывается раз в 300млс
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::cycleHandler(void)   
{
  //  Обработка команд, пришедших по интерфейсу IControlCommands
  if (_commandsBits.rcPlus)  { menuMoveDown();      _commandsBits.rcPlus  =0; }
  if (_commandsBits.rcMinus) { menuMoveUp();        _commandsBits.rcMinus =0; }
  if (_commandsBits.rcDown)  { menuMoveBackward();  _commandsBits.rcDown  =0; }
  if (_commandsBits.rcRight) { menuMoveForward();   _commandsBits.rcRight =0; }


//  menuEngine.setMenuValue("A");
  menuEngine.findAvailableElements(menuEngine.getMenuValue());  // Производит поиск доступных элементов меню на данном уровне меню

  _display->setString((getAvailableElement(getIm()))->getMenu());
}
