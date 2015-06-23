//#####################################################################################
//	Файл				SPI_Port_PIC.cpp
//	Название:		SPI порт, реализованный на микроконтроллере PIC.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |     	Кто		 		| Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 23 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#include "stdint.h"
#include "__SPI_Port_PIC.hpp"


using namespace src;

// Обмен завершен. _spiHandler - инициатор вызова этого метода.
void SpiPortPic::transferComplete (void)
{

}