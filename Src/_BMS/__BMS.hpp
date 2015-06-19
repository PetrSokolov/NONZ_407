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



using namespace std;


namespace src{	 

class Bms : public ISpiMessage{
  public:
    // Методы интерфейса ISpiMessage
    virtual inline uint8_t* getPointerToTransfer() { return _transferBufer; }
    virtual inline uint8_t* getPointerToRecieve()  { return _recieveBufer; }
    virtual inline uint16_t  getSizeOfTransfer() { return _sizeOFMessage; }
    virtual inline uint16_t  getSizeOfrecieve()  { return _sizeOFMessage; }
    virtual inline uint16_t  getCs() { return _cs; }
	  virtual void             transferComplete();
	  virtual void             recieveComplete();
   
  private:
    uint8_t  _transferBufer[16];
    uint8_t  _recieveBufer[16];
    uint8_t  _cs;
    uint16_t _sizeOFMessage;
    uint8_t  pec8_calc(uint8_t len, uint8_t *data);

};

}	// namespace src
#endif	//define RC_HPP
