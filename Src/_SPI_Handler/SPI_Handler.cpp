//#####################################################################################
//	Файл				SPI_Handler.cpp
//	Название:		Обработчик запросов на обмен по SPI
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |     	Кто		 		| Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 июнь 17 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#include "stdint.h"
#include "__SPI_Handler.hpp"
#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"


using namespace src;

//  Добавление сообщения в список на передачу
void SpiHandler::transferMessage  (ISpiMessage* message)
{
  _txMessages.push_back(message);
  message->addedToQueue();

}
  
  
//  Добавление сообщения в список на прием
//void SpiHandler::recieveMessage (ISpiMessage* message)
//{
//  _rxMessages.push_back(message);
//}


//  Удаление сообщения из списока на передачу
//void SpiHandler::sendMessageCompleted  (ISpiMessage* message)
//{
//  _txMessages.remove(message);
//}
  
  
//  Удаление сообщения из списока на прием
//void SpiHandler::recieveMessageCompleted (ISpiMessage* message)
//{
//  _rxMessages.remove(message);
//}



//  Возвращает занятость SPI
uint8_t SpiHandler::getReady (void)
{
 return (HAL_SPI_GetState(_hspi) == HAL_SPI_STATE_READY );
}


// Выбрать устройство на SPI шине
void SpiHandler::chipSelect (uint8_t cs)
{
  cs &= 0xF;
  GPIOE->BSRR = (BIT_0|BIT_1|BIT_2|BIT_3)<<16;
  GPIOE->BSRR = cs;
}


// Снять выбор устройства на SPI шине
void SpiHandler::chipDeselect (void)
{
  GPIOE->BSRR = (BIT_0|BIT_1|BIT_2|BIT_3);
}

//  Удаление сообщения из списока на прием
void SpiHandler::periodicHandler (void)
{
// Потом убрать эти промежуточные данные
//  ISpiMessage* message_;
  uint16_t  sizeOfTransfer_, sizeOfrecieve_;
  uint8_t* pointerToTransfer_;
  uint8_t* pointerToRecieve_;
  uint16_t txempty_, rxempty_, spiReady_;
  
  // Удаление из очереди отработанной посылки
  if(_rxComplete){
    if(_currentMessage != NULL){
      _currentMessage->transferComplete();
    }
    _txMessages.pop_front(); chipDeselect(); _rxComplete =0; 
  }
//  if(_txComplete) { _rxMessages.pop_front();  chipDeselect(); _txComplete =0; }
  
  spiReady_ = getReady();
  txempty_ = _txMessages.empty();
  rxempty_ = _rxMessages.empty();

  //  Если очередь не пустая и SPI свободен, заряжаю следующую посылку
  if ( !_txMessages.empty() && getReady() ){
    _currentMessage = _txMessages.front();
    sizeOfTransfer_    = _currentMessage->getSizeOfTransfer();
    pointerToTransfer_ = _currentMessage->getPointerToTransfer();
    pointerToRecieve_ = _currentMessage->getPointerToRecieve();
    chipSelect(_currentMessage->getCs());
    HAL_SPI_TransmitReceive_DMA(_hspi, pointerToTransfer_, pointerToRecieve_, sizeOfTransfer_);
  }
}

