//#####################################################################################
//	Файл				Editor.cpp
//	Название:		Редактор. Работает с объектами типа IVariable
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 10 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################


#include "stm32f4xx_hal.h"
#include "__Editor.hpp"
//#include "__Parameters.hpp"
#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"

using namespace src;

//---------------------------------------------------------------------------------------
  //  Методы интерфейса IControlCommands
//---------------------------------------------------------------------------------------
void Editor::rcPlus(void)
 {
   if(_variable->getRw() && !getModificationMode()) { setModificationMode();}
   if(getModificationMode()) { incValueHandler(1,0); }
 }
//---------------------------------------------------------------------------------------
void Editor::rcMinus(void)
 { decValueHandler(1,0); }


//---------------------------------------------------------------------------------------
void Editor::rcEnter(void)
 {
   endEditing();
   rcDown();
 }


//---------------------------------------------------------------------------------------
void Editor::rcClear(void)
 { }


//---------------------------------------------------------------------------------------
void Editor::rcOpen(void)
  {  }


//---------------------------------------------------------------------------------------
void Editor::rcClose(void)
 {  }


//---------------------------------------------------------------------------------------
void Editor::rcDown(void)
  { clrViewerMode(); clrModificationMode(); }


//---------------------------------------------------------------------------------------
void Editor::rcRight(void)
 {  }


//---------------------------------------------------------------------------------------
//  Методы интерфейса IDisplayed
//---------------------------------------------------------------------------------------
void Editor::getString(string& str, uint16_t row)
{
  char bufer[8];
  if (getModificationMode()){ //  Режим изменения значения
    snprintf(bufer, sizeof(bufer), "%d", getEditingValue());
  }
   else{                      //  Режим просмотра значения
    snprintf(bufer, sizeof(bufer), "%d", _variable->getValue());
   }
  
  str = bufer;
}

//---------------------------------------------------------------------------------------
void Editor::getRow(uint16_t& row)
{
//  row = _im;
}


//---------------------------------------------------------------------------------------
//  Методы класса Editor
//---------------------------------------------------------------------------------------

// Инкремент параметра  -------------------------------------------------------------------------------------
void Editor::incValueHandler(uint16_t x, uint8_t power)
{
  if(editingValue + x <= _variable->getMax() ) {editingValue += x;} else { editingValue = _variable->getMin(); }
}


// Декремент параметра  -------------------------------------------------------------------------------------
void Editor::decValueHandler(uint16_t x, uint8_t power)
{
  if(editingValue - x >= _variable->getMin()) {editingValue -= x;} else { editingValue = _variable->getMax(); } 
}




