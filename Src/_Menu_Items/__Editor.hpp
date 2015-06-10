//#####################################################################################
//	Файл				Editor.h
//	Название:		Редактор. Работает с объектами типа IVariable
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 10 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "stdint.h"
#include <stdio.h>

#include "..\_Interfaces\__IMenuItem.hpp"
#include "..\_Interfaces\__IVariable.hpp"
#include "..\_Interfaces\__IDisplayed.hpp"
#include "..\_Interfaces\__IControlCommands.hpp"


#ifdef __cplusplus
 extern "C" {
#endif 

using namespace std;
   
namespace src{	 

  //===========================================================================================
  //  Редактор. Работает с объектами типа IVariable 
  //===========================================================================================

class Editor : public IControlCommands{
  public:

  //  Методы интерфейса IControlCommands
    virtual inline void rcPlus(void)  { printf("Editor PLUS PDU handler\n"); }
    virtual inline void rcMinus(void) { printf("Editor MINUS PDU handler\n"); }
    virtual inline void rcEnter(void) { printf("Editor ENTER PDU handler\n"); }
    virtual inline void rcClear(void) { printf("Editor CLEAR PDU handler\n");}
    virtual inline void rcOpen(void)  { printf("Editor OPEN PDU handler\n"); }
    virtual inline void rcClose(void) { printf("Editor CLOSE PDU handler\n"); }
    virtual inline void rcDown(void)  { printf("Editor DOWN PDU handler\n"); }
    virtual inline void rcRight(void) { printf("Editor RIGHT PDU handler\n"); }

	void setDisplay(IDisplay* display) { _display = display; }
    void setVariable(IVariable* variable) { _variable = variable; }
    IDisplay*   _display;                //  Агрегация объекта, отображающего данные на дисплее
    IVariable*  _variable;               //  Редактируемый объект
  
};
  
}	// namespace src

#ifdef __cplusplus
}
#endif
#endif




