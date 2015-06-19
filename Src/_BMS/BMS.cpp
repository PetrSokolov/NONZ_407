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
//#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"
//#include "..\_Interfaces\__IControlCommands.hpp"



using namespace src;


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

