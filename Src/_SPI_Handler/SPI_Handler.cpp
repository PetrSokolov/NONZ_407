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


using namespace src;

//  Добавление сообщения в список на передачу
void SpiHandler::sendMessage  (ISpiMessage* message)
{
  _txMessages.push_back(message);
}
  
  
//  Добавление сообщения в список на прием
void SpiHandler::recieveMessage (ISpiMessage* message)
{
  _rxMessages.push_back(message);
}


//  Удаление сообщения из списока на передачу
void SpiHandler::sendMessageCompleted  (ISpiMessage* message)
{
//  _txMessages.remove(message);
}
  
  
//  Удаление сообщения из списока на прием
void SpiHandler::recieveMessageCompleted (ISpiMessage* message)
{
//  _rxMessages.remove(message);
}



//  Возвращает занятость SPI
uint8_t SpiHandler::getReady (void)
{
 return (HAL_SPI_GetState(_hspi) == HAL_SPI_STATE_READY );
}


//  Удаление сообщения из списока на прием
void SpiHandler::periodicHandler (void)
{
// Потом убрать эти промежуточные данные
//  ISpiMessage* message_;
  uint16_t  sizeOfTransfer_, sizeOfrecieve_;
  uint8_t* pointerToTransfer_;
  uint8_t* pointerToRecieve_;
  
  // Удаление из очереди отработанной посылки
  if(_txComplete) {if(_currentMessage != NULL) { _currentMessage->transferComplete(); } _txMessages.pop_front(); _txComplete =0; }
  if(_rxComplete) { _rxMessages.pop_front(); _rxComplete =0; }

  //  Если очередь не пустая и SPI свободен, заряжаю следующую посылку
  if ( !_txMessages.empty() && getReady() ){
    _currentMessage = _txMessages.front();
    sizeOfTransfer_    = _currentMessage->getSizeOfTransfer();
    pointerToTransfer_ = _currentMessage->getPointerToTransfer();
    HAL_SPI_TransmitReceive_DMA(_hspi, pointerToTransfer_, pointerToRecieve_, sizeOfTransfer_);
  }
}

