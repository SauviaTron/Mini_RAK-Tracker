/*  
 *  Last Update: 17/11/2023
 *       Author: Andrea Sauviat
 *       E-mail: a-sauviat@laposte.net
 * 
 *  Description:  How to use the RGBW Light sensor ?
 *        
 *  GitHub     : https://github.com/SauviaTron/Mini_RAK-Tracker
 *  Datasheet  : https://www.vishay.com/docs/84276/veml6040.pdf
 * 
 */


// > The libraries you need :
#include <Wire.h>      // For I2C  
#include "VEML6040.h"  // In order to use the VEML6040


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          GLOBAL VARIABLES                                                                      //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

VEML6040 RGBWSensor;
uint16_t Red, Green, Blue, White, CCT ;
float AmbientLight ;

bool Enable_SerialPrint = true ; // Display information or not on the serial monitor


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          SETUP()                                                                               //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

void setup() {

  // > Configure the baud rate
  Serial.begin( 115200 ) ; 
  while ( !Serial ) {} ;    // Wait for the serial to be available
  delay(2500) ;             // Add a custom delay for user to 'see' the setup function


  // > Welcome Msg
  Serial.println( "Welcome to the VEML6040 test program ! " ) ;


  // > Configure the I2C
  Wire.begin();


  // > Configure the RGBW Light Sensor
  if( !RGBWSensor.begin() ) {                             // If the sensor can not boot up
    Serial.println("ERROR: couldn't detect the sensor");      // Display n error msg
    while(1){}                                                // Do nothing 
  }
	RGBWSensor.Configuration( );
  // If you want to change the operating mode, the sampling and so on, that in the VEML6040_Configuration function.

}


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          LOOP()                                                                                //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

void loop() {

  // > New loop
  Serial.println(".");

  RGBWSensor.Configuration() ; delay(325) ;                               // Adding delay to the sensor wake-up
  RGBWSensor.getData(&Red, &Green, &Blue, &White, &AmbientLight, &CCT );  // Get Sensor info
  RGBWSensor.Sleep();                                                     // Put back the sensor to sleep mode

  delay(1000);

}
