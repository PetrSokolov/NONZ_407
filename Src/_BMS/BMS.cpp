//#####################################################################################
//	Файл				BMS.cpp
//	Название:		Обработка BMS.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |     	Кто		 		| Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 18 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#include "__BMS.hpp"
#include "stdint.h"
#include "stdio.h"

//#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"
//#include "..\_Interfaces\__IControlCommands.hpp"



using namespace src;

#define RDCFG   0x02
#define RDCV    0x04

//  Write Configuration Register Group
void Bms::wrCfg (void)
{
  //--------------
  _configRegistersWr[0] = 0;
  _configRegistersWr[1] = 0;
  _configRegistersWr[2] = 0;
  _configRegistersWr[3] = 0;
  _configRegistersWr[4] = 0;
  _configRegistersWr[5] = 10;
  //--------------
  _transferBufer[0] = 0x80 + getChipAdres();
  _transferBufer[1] = pec8_calc(1,_transferBufer);
  _transferBufer[2] = 0x01;
  _transferBufer[3] = 0xC7;

  _transferBufer[4] = _configRegistersWr[0];
  _transferBufer[5] = _configRegistersWr[1];
  _transferBufer[6] = _configRegistersWr[2];
  _transferBufer[7] = _configRegistersWr[3];
  _transferBufer[8] = _configRegistersWr[4];
  _transferBufer[9] = _configRegistersWr[5];

  _transferBufer[10] =  pec8_calc(sizeof(_configRegistersWr), _configRegistersWr);    // calculating the PEC for each ICs configuration register data
  
  _sizeOfTransmit = 11;
  _sizeOfRecieve = 0;
  if ((_sizeOfTransmit + _sizeOfRecieve)<sizeof(_recieveBufer)){
    _spiHandler->transferMessage(this);
  }
}


//  Read Configuration Register Group
void Bms::rdCfg (void)
{
  _transferBufer[0] = 0x80 + getChipAdres();
  _transferBufer[1] = pec8_calc(1,_transferBufer);
  _transferBufer[2] = RDCFG;
  _transferBufer[3] = 0xCE;
  
  _sizeOfTransmit = 4;
  _sizeOfRecieve = 6+1;
  if ((_sizeOfTransmit + _sizeOfRecieve)<sizeof(_recieveBufer)){
    _spiHandler->transferMessage(this);
  }
 
}

//  Старт измерения напряжения на ячейках
void Bms::stcvad()
{
  _transferBufer[0] = 0x10;
  _transferBufer[1] = 0xB0;

  _sizeOfTransmit = 2;
  _sizeOfRecieve = 0;
  if ((_sizeOfTransmit + _sizeOfRecieve)<sizeof(_recieveBufer)){
    _spiHandler->transferMessage(this);
  }
}


//  Read All Cell Voltage Group
void Bms::rdCv (void)
{
  _transferBufer[0] = 0x80 + getChipAdres();
  _transferBufer[1] = pec8_calc(1,_transferBufer);
  _transferBufer[2] = RDCV;
  _transferBufer[3] = 0xDC;

  _sizeOfTransmit = 4;
  _sizeOfRecieve = 19;
  if ((_sizeOfTransmit + _sizeOfRecieve)<sizeof(_recieveBufer)){
    _spiHandler->transferMessage(this);
  }
}


//-------------------------------------------------------------------------------------
//  Расчет контрольной суммы
//-------------------------------------------------------------------------------------
uint8_t Bms::pec8_calc(uint8_t len, uint8_t *data)
{
  uint8_t  remainder = 0x41;//PEC_SEED;
  /*
   * Perform modulo-2 division, a byte at a time.
   */
  for (int byte = 0; byte < len; ++byte)
  {
    /*
     * Bring the next byte into the remainder.
     */
    remainder ^= data[byte];

    /*
     * Perform modulo-2 division, a bit at a time.
     */
    for (uint8_t bit = 8; bit > 0; --bit)
    {
      /*
       * Try to divide the current data bit.
       */
      if (remainder & 128)
      {
        remainder = (remainder << 1) ^ 7;
      }
      else
      {
        remainder = (remainder << 1);
      }
    }
  }

  /*
   * The final remainder is the CRC result.
   */
  return (remainder);
}
//-------------------------------------------------------------------------------------


void  Bms::transferComplete(void)
{
  uint8_t received_pec_, data_pec_, com_;
  
  // Планировались данные на прием
  if(_sizeOfRecieve){
   received_pec_ =  _recieveBufer[_sizeOfTransmit+_sizeOfRecieve-1];
   data_pec_ = pec8_calc(_sizeOfRecieve-1, &_recieveBufer[_sizeOfTransmit]);
   if (received_pec_ == data_pec_)
    {
      // Обработка принятых данных
      if (_transferBufer[0] == 0x80 + getChipAdres() ){
        com_ = _transferBufer[2];
      }
      else { com_ = _transferBufer[0]; }
      
      switch (com_){
        case RDCFG:{
          _configRegistersRd[0] = _recieveBufer[_sizeOfTransmit];
          _configRegistersRd[1] = _recieveBufer[_sizeOfTransmit+1];
          _configRegistersRd[2] = _recieveBufer[_sizeOfTransmit+2];
          _configRegistersRd[3] = _recieveBufer[_sizeOfTransmit+3];
          _configRegistersRd[4] = _recieveBufer[_sizeOfTransmit+4];
          _configRegistersRd[5] = _recieveBufer[_sizeOfTransmit+5];
        }break;

        case RDCV:{
          uint8_t data_counter = _sizeOfTransmit;
//          uint8_t received_pec;
          uint16_t temp,temp2;

//          received_pec_ =  _recieveBufer[18];
//          data_pec = pec8_calc(18, &rx_data[0]);
//          if (received_pec != data_pec)
 //         {
   //         pec_error = -1;
     //     }

          for (uint8_t k = 0; k<12; k=k+2)
          {
            temp = _recieveBufer[data_counter++];
            temp2 = (uint16_t)(_recieveBufer[data_counter]&0x0F)<<8;
            _cell_codes[k] = temp + temp2 -512;
            temp2 = (_recieveBufer[data_counter++])>>4;
            temp =  (_recieveBufer[data_counter++])<<4;
            _cell_codes[k+1] = temp+temp2 -512;
          }
        }break;
      }
        
    }  
  }

  _transferBusy =0;
}

