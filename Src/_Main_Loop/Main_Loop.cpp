#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "__Main_Loop.hpp"
#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"

using namespace src;
using namespace std;

extern SPI_HandleTypeDef hspi1;
uint8_t aTxBuffer[32] = {1,2,3,4,5,6,7,8,9,11,12,134,15,26,36,47,4,58};
uint8_t aRxBuffer[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//------------------------------------------------------------------------------
//  Основной цикл приложения
//------------------------------------------------------------------------------

void MainLoop()
{
//------------------------------------------------------------------------------
  //  Низкоуровневая инициализация
//------------------------------------------------------------------------------
  //  Разрешение выходов буферов
  GPIOC->BSRR = BIT_14;
//------------------------------------------------------------------------------
//  Агрегация объектов
//  Определяется только при инициализации программы
//------------------------------------------------------------------------------
  
  mainMenu.addObserver( &menuEngine );  //  Объект menuEngine подписался на рассылку событий, объявленных в IControlCommands
  
//------------------------------------------------------------------------------
//  Начальные условия
//------------------------------------------------------------------------------
  menuEngine.setMenuValue("");
 
//------------------------------------------------------------------------------
//  Основной цикл программы
//------------------------------------------------------------------------------
 while(1){

//  5 mls --------------------------------------------------------------------
   if (Timer5mls >83){
     Timer5mls =0;
     displayLed4Digit.display();
     spi1Handler.periodicHandler();
   }

//  100 mls --------------------------------------------------------------------
   if (Timer100mls >1666){
    Timer100mls =0;

/*##-2- Start the Full Duplex Communication process ########################*/  
  /* While the SPI in TransmitReceive process, user can transmit data through 
     "aTxBuffer" buffer & receive data through "aRxBuffer" */
//  if(HAL_SPI_TransmitReceive_DMA(&hspi1, aTxBuffer, aRxBuffer, 10) != HAL_OK)
//  {
    /* Transfer error in transmission process */
   // Error_Handler();
//  }


  /*##-3- Wait for the end of the transfer ###################################*/  
  /*  Before starting a new communication transfer, you need to check the current   
      state of the peripheral; if it’s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the 
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */  
//  while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
//  {
//  } 

   }

//  333 mls --------------------------------------------------------------------
   if (Timer333mls >5550){
     Timer333mls =0;
     rc.cycleHandler();
     menuEngine.cycleHandler();
   }
  
//------------------------------------------------------------------------------
  
  }
}

