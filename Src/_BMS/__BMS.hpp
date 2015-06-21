//#####################################################################################
//	Файл				_BMS.hpp
//	Название:		Обработка BMS.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |      Кто       | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 18 | Бабкин П.А	    | Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################
#ifndef BMS_HPP
#define BMS_HPP


#include "stdint.h"
#include <list>
//#include "__RC_Decoder.hpp"
#include "..\_Interfaces\__ISpiMessage.hpp"
#include "..\_Interfaces\__ISpiDmaExchange.hpp"



using namespace std;


namespace src{	 

class Bms : public ISpiMessage{
  public:
    Bms(uint8_t  cs, uint8_t chipAdres, ISpiDmaExchange* spiHandler) { _cs = cs; _chipAdres = chipAdres; _spiHandler = spiHandler; }

    // Методы интерфейса ISpiMessage
    virtual inline uint8_t* getPointerToTransfer(void) { return _transferBufer; }
    virtual inline uint8_t* getPointerToRecieve(void)  { return _recieveBufer; }
    virtual inline uint16_t  getSizeOfTransfer(void)   { return ( _sizeOfTransmit + _sizeOfRecieve ); }
    virtual inline uint16_t  getSizeOfrecieve(void)    { return _sizeOfRecieve; }
    virtual inline uint8_t   getCs(void)               { return _cs; }
	  virtual        void      transferComplete(void);
	  virtual inline void      addedToQueue(void)        { _transferBusy =1; }
//	  virtual void             recieveComplete();

    //  Методы класса
    void wrCfg  (void);  //  Write Configuration Register Group
    void rdCfg  (void);  //  Read Configuration Register Group
    void stcvad (void);  //  Function that starts Cell Voltage measurement
    void rdCv   (void);  //  Read All Cell Voltage Group
    inline uint8_t getTransferBusy(void)  { return _transferBusy; }

  private:
    virtual inline uint8_t   getChipAdres() { return _chipAdres; }
    ISpiDmaExchange* _spiHandler;    //  Агрегация обработчика задач на SPI
    uint8_t  _transferBufer[20];
    uint8_t  _recieveBufer[32];
    uint8_t  _chipAdres;
    uint8_t  _cs;
    uint8_t  _transferBusy;
    uint16_t _sizeOfTransmit;
    uint16_t _sizeOfRecieve;
    uint8_t  pec8_calc(uint8_t len, uint8_t *data);
    uint8_t  _configRegistersRd[6];
    uint8_t  _configRegistersWr[6];
    uint16_t _cell_codes[12];

};

}	// namespace src
#endif	//define RC_HPP
