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
    virtual inline uint8_t* getPointerToTransfer();
    virtual inline uint8_t* getPointerToRecieve();
    virtual inline uint16_t  getSizeOfTransfer();
    virtual inline uint16_t  getSizeOfrecieve();
    virtual inline uint16_t  getCs();
	  virtual void             transferComplete();
	  virtual void             recieveComplete();
};

} //src

#endif

