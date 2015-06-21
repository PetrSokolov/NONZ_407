//#####################################################################################
//	Файл				__ISpiMessage.hpp
//	Название:		Интерфейс класса, инициирующего обмен по SPI
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 17 | Бабкин П.А	 		| Первый релиз
//#####################################################################################


#ifndef ISPIMESSAGE_HPP
#define ISPIMESSAGE_HPP

#include "stdint.h"

namespace src{	 

class ISpiMessage{
  public:
    virtual inline uint8_t* getPointerToTransfer(void) =0;
    virtual inline uint8_t* getPointerToRecieve(void) =0;
    virtual inline uint16_t  getSizeOfTransfer(void) =0;
    virtual inline uint16_t  getSizeOfrecieve(void) =0;
    virtual inline uint8_t   getCs(void) =0;
	  virtual        void      transferComplete(void) =0;
    virtual inline void      addedToQueue(void) =0;

};

} //src

#endif

