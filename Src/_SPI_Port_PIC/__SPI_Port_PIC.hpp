//#####################################################################################
//	Файл				SPI_Port_PIC.hpp
//	Название:		SPI порт, реализованный на микроконтроллере PIC.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |     	Кто		 		| Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 23 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################
#ifndef SPIPORTPIC_HPP
#define SPIPORTPIC_HPP

#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "..\_Interfaces\__ISpiMessage.hpp"
#include "..\_Interfaces\__ISpiDmaExchange.hpp"


using namespace std;


namespace src{	 

//-------------------------------------------------------------------------------------
//  Обработчик обмена по SPI.
//  При вызове метода sendMessage\recieveMessage, указатель на объект типа ISpiMessage
//  добавляется в соответствующий контейнер. После обработки удаляется.
//-------------------------------------------------------------------------------------
class SpiPortPic : public ISpiMessage{
  public:
    SpiPortPic(uint8_t  cs, uint16_t spiFrequency, ISpiDmaExchange* spiHandler, uint8_t portALevel, uint8_t portBLevel, uint8_t portADir, uint8_t portBDir)
      {
        _cs = cs;
        _spiFrequency = spiFrequency;
        _spiHandler   = spiHandler; 
        _portALevel   = portALevel;
        _portBLevel   = portBLevel;
        _portADir     = portADir;
        _portBDir     = portBDir;
      }

    // Методы интерфейса ISpiMessage
    virtual inline uint8_t* getPointerToTransfer(void) { return _transferBufer; }
    virtual inline uint8_t* getPointerToRecieve(void)  { return _recieveBufer; }
    virtual inline uint16_t getSizeOfTransfer(void)    { return ( _sizeOfTransmit + _sizeOfRecieve ); }
    virtual inline uint16_t getSizeOfrecieve(void)     { return _sizeOfRecieve; }
    virtual inline uint8_t  getCs(void)                { return _cs; }
    virtual inline uint16_t getSpiFrequency(void)      { return _spiFrequency; }
	  virtual inline void     addedToQueue(void)         { _transferBusy =1; }
    virtual inline uint8_t  getTransferBusy(void)      { return _transferBusy; }
	  virtual        void     transferComplete(void);

    //  Методы класса
    void init (void);

  private:
    ISpiDmaExchange* _spiHandler;    //  Агрегация обработчика задач на SPI
    uint8_t  _transferBufer[20];
    uint8_t  _recieveBufer[32];
    uint8_t  _cs;
    uint16_t _spiFrequency;
    uint8_t  _transferBusy;
    uint16_t _sizeOfTransmit;
    uint16_t _sizeOfRecieve;
    uint8_t   crc_calc(uint8_t len, uint8_t* data);
    uint8_t  _portALevel;
    uint8_t  _portBLevel;
    uint8_t  _portADir;
    uint8_t  _portBDir;
};


}	// namespace src

#endif
