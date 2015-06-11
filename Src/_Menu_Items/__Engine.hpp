//#####################################################################################
//	Файл				Engine.h
//	Название:		Движок меню. На базе автомата состояний.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 23 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#ifndef MENU_ENGINE_H
#define MENU_ENGINE_H

#include "stdint.h"
#include <stdio.h>
#include <vector>
#include <map>

#include "__Editor.hpp"
#include "..\_Interfaces\__IMenuItem.hpp"
#include "..\_Interfaces\__IDisplayed.hpp"
#include "..\_Interfaces\__IControlCommands.hpp"


#ifdef __cplusplus
 extern "C" {
#endif 

using namespace std;
   
namespace src{	 


  //===========================================================================================
  //  Движок меню. 
  //  Осуществляет навингацию по объектам IMenuItem
  //  Агрегирует объект, содержащий карты параметров. (Потом убрать)
  //===========================================================================================

  class MenuEngine : public IControlCommands/*, public IDisplay*/{
	public:
    // Конструктор
//    MenuEngine(IDisplay* display);

    //  Методы интерфейса IControlCommands
    virtual inline void rcPlus(void)  { _commandsBits.rcPlus =1; /*printf("MenuEngine PLUS PDU handler\n");*/ }
    virtual inline void rcMinus(void) { _commandsBits.rcMinus =1; /* printf("MenuEngine MINUS PDU handler\n");*/ }
    virtual inline void rcEnter(void) { _commandsBits.rcEnter =1; /* printf("MenuEngine ENTER PDU handler\n");*/ }
    virtual inline void rcClear(void) { _commandsBits.rcClear =1; /* printf("MenuEngine CLEAR PDU handler\n");*/}
    virtual inline void rcOpen(void)  { _commandsBits.rcOpen =1; /* printf("MenuEngine OPEN PDU handler\n");*/ }
    virtual inline void rcClose(void) { _commandsBits.rcClose =1; /* printf("MenuEngine CLOSE PDU handler\n");*/ }
    virtual inline void rcDown(void)  { _commandsBits.rcDown =1; /* printf("MenuEngine DOWN PDU handler\n");*/ }
    virtual inline void rcRight(void) { _commandsBits.rcRight =1; /* printf("MenuEngine RIGHT PDU handler\n");*/ }

    //  Методы интерфейса IDisplay
//    void setString (char* string);
//    void display (void);
//    void displayOff (void);

    //  Методы класса
    //  Методы работы с элементами меню
    void          putItem   (IMenuItem* menuItem);     // Положить в карту меню элемент
    void          findAvailableElements(vector<IMenuItem*> &resultVector, char* indexString);// Производит поиск доступных элементов меню на данном уровне меню
    void          findAvailableElements(char* indexString);                                  // Производит поиск доступных элементов меню на данном уровне меню
    uint16_t      getCountOfElements(void);            // Возвращает общее количество элементов
    uint16_t      getCountOfAvailableElements(void);   // Возвращает количество элементов на данном уровне
    IMenuItem*     getAvailableElement(uint16_t index);// Возвращает указатель на элемент меню на данном уровне. index[0..getCountOfAvailableElements]
    inline void   setMenuValue(char* m) { strncpy(_m, m, sizeof(_m));  setIm(0); }    // Устанавливает текущий уровень (сигнатуру) меню
    inline char*  getMenuValue(void)    { return _m; } // Возвращает текущий уровень (сигнатуру) меню

    // Методы навигации по элементам меню
    inline void     setIm (uint16_t im) { _im = im; }
    inline uint16_t getIm (void)        { return _im; }
           void     menuMoveDown (void);
           void     menuMoveUp (void);
           void     menuMoveForward (void);
           void     menuMoveBackward (void);
    
           void     cycleHandler(void);               //  Циклический обработчик. Обрабатывает пришедшие команды. Вызывается раз в 300млс

	protected:
    vector<IMenuItem*>  _availableElements;      //  Список доступных элементов меню. На текущем уровне.
    vector<IMenuItem*>  _menuIdVector;           //  Вектор, содержащий все элементы меню
	  char                _m[16];	                 //  Текущее состояние (уровень) меню
	  uint16_t            _im;                     //  Индекс листига текущего меню
    Editor              _editor;                 //  Редактор объекта IVariable
    struct{                                      //  Команды, пришедшие по интерфейсу IControlCommands      
        uint16_t  rcPlus   :1;
        uint16_t  rcMinus  :1;
        uint16_t  rcEnter  :1;
        uint16_t  rcClear  :1;
        uint16_t  rcOpen   :1;
        uint16_t  rcClose  :1;
        uint16_t  rcDown   :1;
        uint16_t  rcRight  :1;
	  }_commandsBits;
};

}	// namespace src

//extern src::MenuEngine menuEngine;

#ifdef __cplusplus
}
#endif
#endif	//define MENU_ENGINE_H




