//#####################################################################################
//	Файл				DisplayLedDecoder.cpp
//	Название:		Декодер на LED индикатор
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 5 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################


//#include "stm32f10x.h"
#include "__DisplayLedDecoder.hpp"
//#include "_Parameters.h"

using namespace src;


//-------------------------------------------------------------------------------------
//  Декодитрование символа на битовые составляющие индикатора
//-------------------------------------------------------------------------------------
void LedDecoder::decode (char symbol)
{
  switch(symbol){
    case 'A': {_segments.all = 0x77; } break;
    case 'B': {_segments.all = 0x7C; } break;
    case 'C': {_segments.all = 0x39; } break;
    case 'D': {_segments.all = 0x5E; } break;
    case 'E': {_segments.all = 0x79; } break;
    case 'F': {_segments.all = 0x71; } break;
    case 'G': {_segments.all = 0x6F; } break;
    case 'H': {_segments.all = 0x74; } break;
    case 'I': {_segments.all = 0x06; } break;
    case 'J': {_segments.all = 0x0E; } break;
    case 'L': {_segments.all = 0x38; } break;
    case 'O': {_segments.all = 0x3F; } break;
    case 'P': {_segments.all = 0x73; } break;
    case 'S': {_segments.all = 0x6D; } break;
    case 'U': {_segments.all = 0x3E; } break;
    case 'Y': {_segments.all = 0x6E; } break;
    case '0': {_segments.all = 0x3F; } break;
    case '1': {_segments.all = 0x06; } break;
    case '2': {_segments.all = 0x5B; } break;
    case '3': {_segments.all = 0x4F; } break;
    case '4': {_segments.all = 0x66; } break;
    case '5': {_segments.all = 0x6D; } break;
    case '6': {_segments.all = 0x7D; } break;
    case '7': {_segments.all = 0x07; } break;
    case '8': {_segments.all = 0x7F; } break;
    case '9': {_segments.all = 0x6F; } break;
    case '.': {_segments.seg.dp = 1; } break;
    default:  {_segments.all = 0x40; } break;
  }

}



