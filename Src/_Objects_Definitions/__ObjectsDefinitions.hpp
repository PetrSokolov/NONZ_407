#ifndef OBJECTSDEFINITIONS_HPP
#define OBJECTSDEFINITIONS_HPP

#include "stdint.h"

#include "..\_ADC\_ADC.hpp"
#include "..\_PWM\__PWM.hpp"
#include "..\_AnalogSensors\__AnalogSensors.hpp"
#include "..\_Menu_Items\__Engine.hpp"
#include "..\_Menu_Items\__Parameters.hpp"
#include "..\_RC_DEcoder\__RC_Decoder.hpp"


using namespace src;

#ifdef __cplusplus
 extern "C" {
#endif 

  //  АЦП1, АЦП3
  extern Adc adc1, adc3;

  // ПДУ
  extern RcDecoder rcDecoder;

  // ШИМ
  extern Pwm2phaseNONZ pwm;

   //  Датчик напряжения на шине постоянного тока. Напряжение  и ток на заряжаемой батарее
  extern AnalogRmsSensor uDC, uCharge, iCharge;

  //  Движок меню
  extern MenuEngine menuEngine;

  //  Контейнер настроечных объектов - параметров
  extern ContainerOfVariables containerOfVariables;

  // Настроечные параметры ШИМ
  extern ParameterFlt  pwmDeathTime, pwmValue;
   
  extern volatile uint16_t Timer100mls;
   
#define BIT_0   0x0001
#define BIT_1   0x0002
#define BIT_2   0x0004
#define BIT_3   0x0008
#define BIT_4   0x0010
#define BIT_5   0x0020
#define BIT_6   0x0040
#define BIT_7   0x0080
#define BIT_8   0x0100
#define BIT_9   0x0200
#define BIT_10  0x0400
#define BIT_11  0x0800
#define BIT_12  0x1000
#define BIT_13  0x2000
#define BIT_14  0x4000
#define BIT_15  0x8000

/*namespace src{	 

};*/ // namespace
#ifdef __cplusplus
};
#endif
#endif	//define OBJECTSDEFINITIONS_HPP
