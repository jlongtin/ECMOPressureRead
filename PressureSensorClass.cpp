

#ifndef PressureClass_cpp
#define PressureClass_cpp
#include "Arduino.h"
#include "PressureSensorClass.h"

class ELVHPressureSensor {

  private:
  
    uint8_t   CSpin_;
    uint32_t  lastReadTime_ = 0;
    pUnit     pressUnit_ = Pa;
    uint16_t  T_;        // sensor temperature, raw value from sensor
    uint16_t  Praw_;     // sensor pressure, raw value from sensor
    uint8_t   flag_;     // sensor read flag 
  
  public:
  
  void ELVHPressurSensor (uint8_t CSpin, pUnit = Pa){
    
    CSpin_ = CSpin;
     //setup SPI 
  }

  float getTemp(void){

  //read temperature    uint8_t p[4];  // buffer to read 4 bytes
    
    if ((millis() - lastReadTime_) > 500){
      // get fresh reading
      //T_ = new temperature
    }

    return T_;
    lastReadTime_ = millis();  //last read time
  }

};

#endif