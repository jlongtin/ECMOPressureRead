/*********************************************************************************

  ECMO Pressure Measurement Prototype
    reads pressure across ECMO device for early-stage detection 
	of clotting/clogging

  ECMO VIP Team - Stony Brook University

**********************************************************************************/


// include the SPI library:
#include "PressureSensorClass.h"
#include <SPI.h>

constexpr char Version[] = "1.0.0";

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
uint8_t rxP1,rxP2,rxP3,rxP4;
uint16_t p2;
uint8_t p[4];


// pressure sensors from left to right (right = direction hose barbs are pointing)
//                differential ==>     pLow ==>       pHigh==>
// CS pin                 8                9            10
// pressure range     +/-250 mbar       +/-5 psi      +/-5 psi
//
ELVHPressureSensor dp(8, 250, mbar);  // define differential pressure sensor
ELVHPressureSensor pL(9, 5, psi);    // define high-side absolute pressure sensor
ELVHPressureSensor pH(10, 5, psi);    // define high-side absolute pressure sensor

// offsets for the pressure sensors (entered manually)
constexpr float dp0 = 0.2574;  //mmHg
constexpr float pH0 = -0.1185;
constexpr float pL0 = -0.0718; // mmHg


void setup() {
  // set the slaveSelectPin as an output:
  Serial.begin(115200);
  pinMode (8,OUTPUT);
  digitalWrite(8,HIGH);
  pinMode (9,OUTPUT);
  digitalWrite(9,HIGH);
  // initialize SPI:
  pinMode (10,OUTPUT);
  digitalWrite(10,HIGH);
  // initialize SPI:
  SPI.begin();
}
 
void loop() {
  
   Serial.print("dP:");
   Serial.print(dp.getP(mmHg) - dp0,2);
   Serial.print(", pH:");
   delay(10);  // wait just a bit
   Serial.print(pH.getP(mmHg) - pH0,1);
   Serial.print(", pL:");
   delay(10);
   Serial.print(pL.getP(mmHg) - pL0,1);
//   Serial.print(pH.getT(),2);
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