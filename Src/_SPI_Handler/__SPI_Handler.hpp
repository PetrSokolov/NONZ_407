//#####################################################################################
//	Файл				SPI_Handler.hpp
//	Название:		Обработчик запросов на обмен по SPI
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |     	Кто		 		| Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 17 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################
#ifndef SPIHANDLER_HPP
#define SPIHANDLER_HPP

#include "stm32f4xx_hal.h"
#include "stdint.h"
#include <list>
//#include "..\_Interfaces\__ISpiMessage.hpp"
#include "..\_Interfaces\__ISpiDmaExchange.hpp"

//#include "..\\_Interfaces\__IObservable.hpp"

using namespace std;


namespace src{	 

//-------------------------------------------------------------------------------------
//  Обработчик обмена по SPI.
//  При вызове метода sendMessage\recieveMessage, указатель на объект типа ISpiMessage
//  добавляется в соответствующий контейнер. После обработки удаляется.
//-------------------------------------------------------------------------------------
class SpiHandler : public ISpiDmaExchange{
  public:
    SpiHandler (SPI_HandleTypeDef* hspi, uint32_t spiClkFrequency)
      {
        _hspi = hspi; 
        _spiClkFrequency = spiClkFrequency;
        _currentMessage = NULL;
      }
    //  Методы интерфейса ISpiDmaExchange
    virtual void transferMessage    (ISpiMessage* message);
//    virtual void recieveMessage (ISpiMessage* message);
  
    //  Методы класса
    inline void setTxComplete (void) { _txComplete =1; }
    inline void setRxComplete (void) { _rxComplete =1; }
    void periodicHandler (void);

  private:
//    void sendMessageCompleted    (ISpiMessage* message);
//    void recieveMessageCompleted (ISpiMessage* message);
    void chipSelect (uint8_t cs);                         // Выбрать устройство на SPI шине
    void chipDeselect (void);                             // Отменить выбор устройства на SPI шине
    uint8_t getReady (void);                              //  Возвращает занятость SPI
    void setSpiFrequency (ISpiMessage* message);          //  Устанавливает делитель, соответствующий заданной скорости передачи

    list<ISpiMessage*> _txMessages;      //  Список сообщений на передачу
    list<ISpiMessage*> _rxMessages;      //  Список сообщений на прием
    uint8_t            _txComplete :1;   //  Передача завершена, необходимо удалить соответствующий объект из очереди
    uint8_t            _rxComplete :1;   //  Прием завершен, необходимо удалить соответствующий объект из очереди
    SPI_HandleTypeDef* _hspi;            //  Указатель на структуру HAL SPI
    uint32_t           _spiClkFrequency; //  Частота синхронизации SPI (APB1, APB2)
    ISpiMessage*       _currentMessage;  //  Текущее сообщение

};
//    list<IObserver*> _observers; // Список наблюдателей

	

}	// namespace src

#endif	//define RC_MODULE_HPP
