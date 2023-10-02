/*********************************************************************************

  ECMO Pressure Measurement Prototype
    reads pressure across ECMO device for early-stage detection 
	of clotting/clogging

  ECMO VIP Team - Stony Brook University

**********************************************************************************/


// include the SPI library:
#include "PressureSensorClass.h"
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
uint8_t rxP1,rxP2,rxP3,rxP4;
uint16_t p2;
uint8_t p[4];

ELVHPressureSensor dp(8, 250, mbar);  // define differnetial pressure sensor
ELVHPressureSensor P1(10, 5, psi);  // define differnetial pressure sensor



void setup() {
  // set the slaveSelectPin as an output:
  Serial.begin(115200);
  pinMode (8,OUTPUT);
  digitalWrite(8,HIGH);
  pinMode (10,OUTPUT);
  digitalWrite(10,HIGH);
  // initialize SPI:
  SPI.begin();
 // SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));
 // pinMode(11,INPUT);
}

void loop() {
  
   Serial.print("dP:");
   Serial.print(dp.getP(mbar)-0.1226,4);
   Serial.print(", P1:");
   delay(10);  // wait just a bit
   Serial.print(P1.getP(psi),4);
  // Serial.print(", dp_T: ");
  // Serial.print(dp.convertTemperature(),1);
   //Serial.print(rxP1,HEX); Serial.print(", ");
   Serial.println();
  // Serial.print(rxP2,HEX); Serial.print(", ");
  // Serial.print(rxP3,HEX); Serial.print(", ");
  // Serial.print(rxP4,HEX); Serial.print(", ");
  // Serial.print(rxP1*0xFF+rxP2);
  // Serial.println();

  delay(1000);
}