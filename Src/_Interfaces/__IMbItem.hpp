//#####################################################################################
//	Файл				__IMBITEM.hpp
//	Название:		Интерфейс класса, работающего с ModBus
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 май 29 | Бабкин П.А	 		| Первый релиз
//#####################################################################################


#ifndef IMBITEM_H
#define IMBITEM_H

#include "stdint.h"

#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 

//=================================================================================================
//  Интерфейс класса для работы с ModBus
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//  Интерфейс класса, имеющего 1 регистр
//-------------------------------------------------------------------------------------------------
class IMbItem1Reg{
  public:
    virtual        void     putToMbMap  (IMbItem1Reg* mbItem1Reg) = 0;               // Положить объект в карту (объект IMbItem1Reg)
    //  Методы обработки команд протокола
    virtual inline uint16_t com3Handler  (void) = 0;           // Возвращает значение на команду 3 (чтение регистра)
    virtual inline void     com6Handler  (void) = 0;           // Возвращает результат на команду 6 (запись регистра)
    virtual inline void     com16Handler (void) = 0;           // Возвращает результат на команду 16 (запись последовательности регистров)
    virtual inline uint8_t  getAdr 		 (void) = 0;           // Возвращает модбас адрес объекта
//    virtual inline void     setAdr 		 (uint8_t adres) = 0;  // Устанавливает модбас адрес объекта
};  



//-------------------------------------------------------------------------------------------------
//  Интерфейс класса, имеющего 2 регистра
//-------------------------------------------------------------------------------------------------
class IMbItem2Reg : public IMbItem1Reg{
  public:
    virtual inline uint8_t  getAdr2 		 (void) = 0;            // Возвращает модбас адрес2 объекта
};  

} //src
#ifdef __cplusplus
}
#endif
#endif	//define IMBITEM_H

