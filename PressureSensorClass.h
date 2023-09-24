/*
  ELVH Pressure Sensor Reading Library 

  SPI read of ELVH pressure sensors

  Notes:
    1. Does NOT workw ith Arduino Uno R3 --- mangles MISO line.  Uno R4 does not work at all.
    2. Need to use SPI Mode 3, not default, to properly recored signals.
    3. Sensors are read-only.  They refresh approx every 0.5 ms.

*/

#ifndef PressureClass_h
#define PressureClass__h
#include "Arduino.h"

enum  pUnit  {mmHg, mmH2O, inH2O, ftH2O, Pa, kPa, psi, bar, atm};

const uint32_t minTimeElapse = 1000;  // minimum time to elapse before requesting another reading. Ensures pressure sensor has time to cycle.

const float xPa = 1.0;  // base pressure stored as Pa
const float xkPa = 0.001;
const float xmmHg = 0.0;
const float xmmH2O = 0.0;
const float xpsi = 0.0;
const float xbar = 0.0;
const float xatm = 0.0;


/*

class EVHPressureSensor {

  private:
  
    uint8_t _CSpin;
    uint32_t _lastReadTime = 0;
    enum unit (Pa, mmHg,psi,)
  public:
  

  void EVHPressurSensor ((uint8_t CSpin){
    
    _CSPin = CSpin;
     //setup SPI 
  }

  void getTemp(void){

  //read temperature    uint8_t p[4];  // buffer to read 4 bytes
    
    if ((millis() - lastReadTime) > 500){
      // get fresh reading
    }

    return _Temp;
    lastReadTime = millis();  //last read time
  }

}

*/

#endif



