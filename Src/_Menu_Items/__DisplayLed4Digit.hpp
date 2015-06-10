//#####################################################################################
//	Файл				DisplayLed4Digit.hpp
//	Название:		Обработчик дисплея с 4 семисегметными элементами
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 8 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#ifndef DISPLAYLED4DIGIT_HPP
#define DISPLAYLED4DIGIT_HPP

#include "stdint.h"
#include <stdio.h>
#include "..\_Interfaces\__IDisplayed.hpp"
#include "__DisplayLedDecoder.hpp"


#ifdef __cplusplus
 extern "C" {
#endif 

using namespace std;
   
namespace src{	 

//-------------------------------------------------------------------------------------
//	Класс отображения на 4 символьном индикаторе
//-------------------------------------------------------------------------------------

class DisplayLed4Digit : public IDisplay{
  public:
    //  Методы интерфейса IDisplay
    virtual void setString (char* string);
    virtual void display (void);
    virtual void displayOff (void);

  private:
    LedDecoder  _ledDecoder;                  //  Декодер в семисегментный индиктор
    uint8_t     _digit;                       //  Номер отображаемого символа
    char        _string[16];                  //  Данные на отображение
    char        _displayBufer[16];            //  Данные на отображение
    char*       _symbolPointer;               //  Указатель на отображаемый символ
    char*       _endPointer;                  //  Указатель на конец строки

};

}	// namespace src


#ifdef __cplusplus
}
#endif
#endif




