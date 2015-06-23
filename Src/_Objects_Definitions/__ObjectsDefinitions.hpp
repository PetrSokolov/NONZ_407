#ifndef OBJECTSDEFINITIONS_HPP
#define OBJECTSDEFINITIONS_HPP

#include "stdint.h"

#include "..\_ADC\_ADC.hpp"
#include "..\_PWM\__PWM.hpp"
#include "..\_AnalogSensors\__AnalogSensors.hpp"
#include "..\_Menu_Items\__MainMenu.hpp"
#include "..\_Menu_Items\__Engine.hpp"
#include "..\_Menu_Items\__Parameters.hpp"
#include "..\_Menu_Items\__DisplayLed4Digit.hpp"
#include "..\_RC\__RC.hpp"
#include "..\_SPI_Handler\__SPI_Handler.hpp"
#include "..\_SPI_Port_PIC\__SPI_Port_PIC.hpp"
#include "..\_BMS\__BMS.hpp"


using namespace src;


  //  АЦП1, АЦП3
  extern Adc adc1, adc3;

  // ШИМ
  extern Pwm2phaseNONZ pwm;

   //  Датчик напряжения на шине постоянного тока. Напряжение  и ток на заряжаемой батарее
  extern AnalogRmsSensor uDC, uCharge, iCharge;

  //  Обработчик отображения на индикаторе. Реализует интерфейс IDisplay
  extern DisplayLed4Digit displayLed4Digit;

   //  Менеджер меню
  extern MainMenu mainMenu;
   
  //  Движок меню
  extern MenuEngine menuEngine;

  // ПДУ
  extern Rc rc;

  //  Обработчик SPI
  extern SpiHandler spi1Handler, Spi2Handler;

  // Модули БМС (0-10)
  extern Bms bms0, bms6, bms8;

  // SPI порты на микроконтроллере PIC
  extern SpiPortPic spiPortPic6;

  //  Контейнер настроечных объектов - параметров
  extern ContainerOfVariables containerOfVariables;

  // Настроечные параметры ШИМ
  extern ParameterFlt  pwmDeathTime, pwmValue;
   
  extern volatile uint16_t Timer1mls, Timer5mls, Timer100mls, Timer333mls;
   

#endif	//define OBJECTSDEFINITIONS_HPP
