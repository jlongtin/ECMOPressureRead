#include "PressureSensorClass.h"
    
void ELVHPressureSensor::readPressureSensor(void){
    uint8_t p[4];  // buffer to store 4 bytes from sensor 

    SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE3));
    // take the SS pin low to select the chip:
    digitalWrite(CSpin_, LOW);
    delayMicroseconds(5);
    SPI.transfer(p,4);  // transfer 4 bytes into p
    flag_= (p[0] && 0b11000000)>>6; // highest two bits are flag status; preserve them, then shift left so flag in [0-3]
    Praw_ = ((uint16_t)(p[0] & 0b00111111) << 8) | (uint16_t)(p[1]);
    Traw_ = ((uint16_t)(p[2]) << 3) | ((uint16_t)(p[3] & 0b11100000) >> 5);
    delayMicroseconds(5);
    digitalWrite(CSpin_, HIGH);
    SPI.endTransaction();
}

 
float ELVHPressureSensor::convert2Pa(float p, pressureUnit pUnit){
// converts p in units of 'pUnit' to Pa
// can be used as 1/x, i.e., in denominator to convert from Pa to pUnit

  switch (pUnit) {
    case mbar: 
      return 100.0*p;
      break;
    case bar:
      return 1e5*p;
      break;
    case Pa:     // no change, but included for completely 
      return 1.*p;
      break;
    case kPa:
      return 1000.*p;
      break;
    case atm:
      return 101325.*p;
      break;
    case mmHg: case Torr:
      return 133.22*p;
      break;
    case psi:
      return 6894.76*p; 
      break;
    case mmH2O:
      return 9.80665*p;
      break;
    case inH2O:
      return 248.84*p;
      break;
    case ftH2O:
      return 2986.116*p;
      break;
    
    default:
      return -1.0;  // should never get here

  }
}

/*
  float getTemp(void){

  //read temperature    uint8_t p[4];  // buffer to read 4 bytes
    
    if ((millis() - lastReadTime_) > 500){
      // get fresh reading
      readPressureSensor();
    }

    
    return Traw_;
    lastReadTime_ = millis();  //last read time
  }

};

*/
