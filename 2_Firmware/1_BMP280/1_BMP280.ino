/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include "BMP280_Functions.h"


void setup() {

  Serial.begin(9600);

  while ( !Serial ){ } ;   // wait for native usb
  delay( 2500 ) ; // Add a delay of 2.5secondes

  Serial.println( "Welcome to the BMP280 test program ! " ) ; // Welcome msg

  BMP280_GetStatus( ) ;

  /* Default settings from datasheet. */
  BMP280_Settings( ) ;

}

void loop() {

  BMP280_GetTemperature( true );
  BMP280_GetPressure( true );
  BMP280_GetAltitude( true ) ;

  Serial.println(" ") ;
  delay(1000);

}










