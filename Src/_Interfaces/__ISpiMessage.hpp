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
    virtual inline uint8_t* getPointerToTransfer(void) =0;  // Возвращает указатель на буфер-передатчик
    virtual inline uint8_t* getPointerToRecieve(void) =0;   // Возвращает указатель на буфер-приемник
    virtual inline uint16_t  getSizeOfTransfer(void) =0;    // Возвращает количество байт на передачу
    virtual inline uint16_t  getSizeOfrecieve(void) =0;     // Возвращает количество байт на прием
    virtual inline uint8_t   getCs(void) =0;                // Возвращает код выбора устройстка на шине SPI
    virtual inline uint16_t  getSpiFrequency(void) =0;      // Возвращает скорость передачи [кГц]
    virtual inline void      addedToQueue(void) =0;         // Вызывается внешним объектом ISpiDmaExchange, при постановке в очередь на обработку.
                                                            // До окончания обработки параметры обмена не изменять.
    virtual inline uint8_t   getTransferBusy(void) =0;      // Возвращает занятость интерфейса
    virtual        void      transferComplete(void) =0;     // Вызывается внешним объектом ISpiDmaExchange при завершении обмена, инициированного текущим объектом ISpiMessage

};

} //src

#endif

