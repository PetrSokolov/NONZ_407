//#####################################################################################
//	Файл				DisplayLed4Digit.cpp
//	Название:		Декодер на LED индикатор
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 8 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#include "stm32f4xx_hal.h"
#include "__DisplayLed4Digit.hpp"
#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"
#include "..\_Objects_Definitions\__ConstantsDefinitions.hpp"

using namespace src;

//========================================================================================================
//  Реализация интерфейса IDisplay
//========================================================================================================

//  Конструктор
DisplayLed4Digit::DisplayLed4Digit(IDisplayed* object)
  {
    _object = object;
  }

//-------------------------------------------------------------------------------------
//  Передача данных на отображение
//-------------------------------------------------------------------------------------
/*void DisplayLed4Digit::setString (char* string)
{
 strncpy(_string, string, 8);

}*/


//-------------------------------------------------------------------------------------
//  Отображение данных
//-------------------------------------------------------------------------------------
void DisplayLed4Digit::display (void)
{
  //  Сброс управляющих пинов
  GPIOD->BSRR = (BIT_8|BIT_9|BIT_10|BIT_11|BIT_12);
  GPIOD->BSRR = ((BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7) & 0xFF)<<16;

  //  Перезагрузка буфера на отображение (_displayString) производится в начале отображения
  if (_digit == 0){
   _object->getString(_string, 0);
   _displayString = _string;
   _it = _displayString.begin();
    
    //    strcpy(_displayBufer, _string);
//    _symbolPointer = _displayBufer;                       // Указатель на отображаемый символ
//    _endPointer = _symbolPointer + strlen(_displayBufer);  // Указатель на конец строки
  }

  //  По достижении конца строки символы гасятся
  if (_it >= _displayString.end()){
      _ledDecoder.decode(' ');
  }
   else{
         _ledDecoder.decode(*_it++);
         if (*_it == '.'){
           _ledDecoder.decode(*_it++);
         }
   }

//  _ledDecoder.decode(_string[_digit]);
  switch(_digit){
    case 0:{
             GPIOD->BSRR = _ledDecoder.getAll();
             GPIOD->BSRR = BIT_8<<16;
            _digit++;
      }break;
    case 1:{
            GPIOD->BSRR = _ledDecoder.getAll();
            GPIOD->BSRR = BIT_9<<16;
            _digit++;
      }break;
    case 2:{
            GPIOD->BSRR = _ledDecoder.getAll();
            GPIOD->BSRR = BIT_10<<16;
            _digit++;
      }break;
    case 3:{
            GPIOD->BSRR = _ledDecoder.getAll();
            GPIOD->BSRR = BIT_12<<16;
            _digit =0;
      }break;
    default:  _digit =0; break;
  }
}


