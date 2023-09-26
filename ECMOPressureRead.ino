/*
  Digital Pot Control

  This example controls an Analog Devices AD5206 digital potentiometer.
  The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
  A - connect this to voltage
  W - this is the pot's wiper, which changes when you set it
  B - connect this to ground.

 The AD5206 is SPI-compatible,and to command it, you send two bytes,
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).

 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resistor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)

 created 10 Aug 2010
 by Tom Igoe

 Thanks to Heather Dewey-Hagborg for the original tutorial, 2005

*/


// include the SPI library:
#include "PressureSensorClass.h"
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
uint8_t rxP1,rxP2,rxP3,rxP4;
uint16_t p2;
uint8_t p[4];

ELVHPressureSensor dp(10, 250, mbar);  // define differnetial pressure sensor


void setup() {
  // set the slaveSelectPin as an output:
  Serial.begin(115200);
  pinMode(slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
 // SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));
 // pinMode(11,INPUT);
}

void loop() {
  
  
  // Serial.print(rxP1,HEX); Serial.print(", ");
  // Serial.print(rxP2,HEX); Serial.print(", ");
  // Serial.print(rxP3,HEX); Serial.print(", ");
  // Serial.print(rxP4,HEX); Serial.print(", ");
  // Serial.print(rxP1*0xFF+rxP2);
  // Serial.println();

  delay(1000);
}