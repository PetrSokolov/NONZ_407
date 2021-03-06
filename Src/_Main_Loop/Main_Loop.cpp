#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "__Main_Loop.hpp"
#include "..\_Objects_Definitions\__ObjectsDefinitions.hpp"
#include "..\_Objects_Definitions\__ConstantsDefinitions.hpp"

using namespace src;
using namespace std;

extern SPI_HandleTypeDef hspi1;
uint8_t aTxBuffer[32] = {1,2,3,4,5,6,7,8,9,11,12,134,15,26,36,47,4,58};
uint8_t aRxBuffer[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t bmsComandTmp =0;

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

  //  Инициализация SPI портов
  

//------------------------------------------------------------------------------
//  Агрегация объектов
//  Определяется только при инициализации программы
//------------------------------------------------------------------------------
  
  mainMenu.addObserver( &menuEngine );  //  Объект menuEngine подписался на рассылку событий, объявленных в IControlCommands
  
//------------------------------------------------------------------------------
//  Начальные условия
//------------------------------------------------------------------------------
  menuEngine.setMenuValue("");
 
//  if (!bms6.getTransferBusy()){
//    bms6.rdCfg();
//  }
//     if (!bms6.getTransferBusy()){
//       bms6.stcvad();
//     }

  
//------------------------------------------------------------------------------
//  Основной цикл программы
//------------------------------------------------------------------------------
 while(1){

//  1 mls --------------------------------------------------------------------
   if (Timer1mls >16){
     Timer1mls =0;
     spi1Handler.periodicHandler();
   }

   //  5 mls --------------------------------------------------------------------
   if (Timer5mls >83){
     Timer5mls =0;
     displayLed4Digit.display();

   }

//  100 mls --------------------------------------------------------------------
   if (Timer100mls >1666){
    Timer100mls =0;
//     if (!bms6.getTransferBusy()){
//       bms6.rdCv();
//     }
   }

//  333 mls --------------------------------------------------------------------
   if (Timer333mls >5550){
     Timer333mls =0;
     rc.cycleHandler();
     menuEngine.cycleHandler();

     switch(bmsComandTmp){
       case 1:{
         if (!bms6.getTransferBusy()){
           bms6.rdCfg();
         }
//         bmsComandTmp =0;
       }break;
       case 2:{
         if (!bms6.getTransferBusy()){
           bms6.wrCfg();
         }
//         bmsComandTmp =0;
       }break;
       case 3:{
         if (!bms6.getTransferBusy()){
           bms6.stcvad();
         }
//         bmsComandTmp =0;
       }break;
       case 4:{
         if (!bms6.getTransferBusy()){
           bms6.rdCv();
         }
//         bmsComandTmp =0;
       }break;
       default: { bmsComandTmp =0; }break;
     }
       
       
   }
  
//------------------------------------------------------------------------------
  
  }
}

