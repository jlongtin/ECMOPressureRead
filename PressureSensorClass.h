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
#include <SPI.h>
#include "Arduino.h"

enum  pressureUnit  {mmHg, mmH2O, inH2O, ftH2O, Pa, kPa, psi, bar, mbar, atm, Torr}; //TOD: enum class??  Place inside of ELVH.. clas??

class ELVHPressureSensor {

  enum  Status {       // status flag definition.  Assume this holds for ELVH series
      CURRENT     = 0,
      RESERVED    = 1,
      STALE_DATA  = 2,
      ERROR       = 3,
    };

  private: 
      const uint32_t minTimeElapse = 1000;  // minimum time to elapse before requesting another reading. Ensures pressure sensor has time to cycle.
      uint8_t           CSpin_;
      uint32_t          lastReadTime_ = 0;
      pressureUnit      pUnit_;
      float             pMax_;     // TODO: can I make this a constant?
      uint16_t          Traw_;     // sensor temperature, raw value from sensor
      uint16_t          Praw_;     // sensor pressure, raw value from sensor
      uint8_t           flag_;     // sensor read flag 

      float convert2Pa(float, pressureUnit);  // converts argument of unit supplied to Pa
    
  public:

    ELVHPressureSensor (uint8_t pin, float pmax, pressureUnit pu) : CSpin_{pin}, pMax_{pmax}, pUnit_{pu}{
        // empty constructor
    }
    void readPressureSensor(void); 
};

#endif





