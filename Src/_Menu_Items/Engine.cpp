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


//MenuEngine menuEngine;
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
  // поиск элементов следующего уровня меню
  // если они есть, то переход.
  // Присваивание вектору элементов текущего уровня, вектора найденных элементов.
}


//--------------------------------------------------------------------------------------------------------
// Метод menuMoveBackward
// Перемещает состояние (уровень) меню назад
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::menuMoveBackward (void)
{

}

//========================================================================================================
//  Реализация интерфейса IDisplayed
//========================================================================================================

void MenuEngine::display (void)
{
  switch(_digit){
    case 0:{
  _ledDecoder.decode('A');
  GPIOD->BSRR = (BIT_8|BIT_9|BIT_10|BIT_11|BIT_12);
  GPIOD->BSRR = ((BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7) & 0xFF)<<16;
  GPIOD->BSRR = _ledDecoder.getAll();
  GPIOD->BSRR = BIT_8<<16;
      _digit++;
      }break;
    case 1:{
  _ledDecoder.decode('B');
  GPIOD->BSRR = (BIT_8|BIT_9|BIT_10|BIT_11|BIT_12);
  GPIOD->BSRR = ((BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7) & 0xFF)<<16;
  GPIOD->BSRR = _ledDecoder.getAll();
  GPIOD->BSRR = BIT_9<<16;
      _digit++;
      }break;
    case 2:{
  _ledDecoder.decode('C');
  GPIOD->BSRR = (BIT_8|BIT_9|BIT_10|BIT_11|BIT_12);
  GPIOD->BSRR = ((BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7) & 0xFF)<<16;
  GPIOD->BSRR = _ledDecoder.getAll();
  GPIOD->BSRR = BIT_10<<16;
      _digit++;
      }break;
    case 3:{
  _ledDecoder.decode('D');
  GPIOD->BSRR = (BIT_8|BIT_9|BIT_10|BIT_11|BIT_12);
  GPIOD->BSRR = ((BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7) & 0xFF)<<16;
  GPIOD->BSRR = _ledDecoder.getAll();
  GPIOD->BSRR = BIT_12<<16;
      _digit =0;
      }break;
    default:  _digit =0; break;

  
  }
    



  
  printf("Digit = %d\n", _digit);
  
}
