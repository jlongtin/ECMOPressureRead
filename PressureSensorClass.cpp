/*********************************************************************************
  ELVH Pressure Sensor Reading Library 

  SPI read of ELVH pressure sensors

  ECMO VIP Team - Stony Brook University

  Notes:
    1. Does NOT workw ith Arduino Uno R3 --- mangles MISO line.  Uno R4 does not work at all.
       FIXED! MISO line, not MOSI line required. 
    2. Need to use SPI Mode 3, not default, to properly recored signals.
    3. Sensors are read-only.  They refresh approx every 0.5 ms.
**********************************************************************************/

#include "PressureSensorClass.h"
    
void ELVHPressureSensor::readPressureSensor(void){
    uint8_t p[4];  // buffer to store 4 bytes from sensor 

    SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE3));
    // take the SS pin low to select the chip:
    digitalWrite(CSpin_, LOW);
    delayMicroseconds(10);  // spec sheet for similar pressure sensor says wait 8 us
    SPI.transfer(p,4);  // transfer 4 bytes into p
    flag_ = (p[0] && 0b11000000)>>6; // highest two bits are flag status; preserve them, then shift left so flag in [0-3]
    pRaw_ = ((uint16_t)(p[0] & 0b00111111) << 8) | (uint16_t)(p[1]);  // raw pressure is next 14 bits. after stripping flag
    Traw_ = ((uint16_t)(p[2]) << 3) | ((uint16_t)(p[3] & 0b11100000) >> 5); // then temperature is next 5 bits
    delayMicroseconds(5);
    digitalWrite(CSpin_, HIGH);1
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

float ELVHPressureSensor::convertPressure(pressureUnit pu) {  // returns pressure in pressure units pu
  // Convert a raw digital pressure read from the sensor to a floating point value in PSI.
  // Based on the following formula in the datasheet: Pressure(units) = 1.25 x ((P_out_dig - OS_dig) / 2^14) x FSS(units)
  float tmpP =  1.25*((float) pRaw_ - (float) pressure_zero_ref) / FULL_SCALE_REF * pMax_;  // pressure in Pa. Not sure why 1.25 is needed
  return tmpP/convert2Pa(1.,pu);
}

float ELVHPressureSensor::convertTemperature(void) {
  // Convert a raw digital temperature read from the sensor to a floating point value in Celcius.
  // Based on the following formula in the datasheet: Temperature(degC) = T_out_dig x (200 / 2^11 - 1) - 50
  return Traw_ * (200.0 / 2047.0) - 50.0;  //degC
  // convert temperture here, when feature added
}

float ELVHPressureSensor::getP(pressureUnit pu ){     // does a fresh read of sensor
  ELVHPressureSensor::readPressureSensor();
  return ELVHPressureSensor::convertPressure(pu);     // return pressure in units pu
}

float ELVHPressureSensor::getT(void) {                // does a fresh read of sensor
  ELVHPressureSensor::readPressureSensor();
  return ELVHPressureSensor::convertTemperature();    // return temperature in degC
}


uint8_t ELVHPressureSensor::getFlag(void) {           // does NOT do a fresh read of sensor; reports last flag
  return flag_;
}