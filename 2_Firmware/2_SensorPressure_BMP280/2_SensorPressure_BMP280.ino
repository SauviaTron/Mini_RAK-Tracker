/*  
 *  Last Update: 16/11/2023
 *       Author: Andrea Sauviat
 *       E-mail: a-sauviat@laposte.net
 * 
 *  Description: How to use and get information from the BMP280 sensor ?
 *        
 *  GitHub     : https://github.com/SauviaTron/Mini_RAK-Tracker
 *  Datasheet  : https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf
 * 
 */
 

// > The libraries you need :
#include <Wire.h> // For I2C       
#include "BMP280_Functions.h" // Adafruit and custom library for BMP280


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          GLOBAL VARIABLES                                                                      //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

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
  Serial.println( "Welcome to the BMP280 test program ! " ) ;


  // > Configure the I2C
  Wire.begin();


  // > Configure the BMP280
  BMP280_GetStatus( ) ; // Check if the sensor respond to basic command
  BMP280_WakeUp(    ) ; // Configure the sensor with the default parameter
  // If you want to change the operating mode, the sampling, the filter or the standy, that in the BMP280_Setting function.

}


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          LOOP()                                                                                //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

void loop() {

  // > New loop
  Serial.println(".");

  BMP280_WakeUp() ; // Wake up the sensor

  BMP280_GetTemperature( Enable_SerialPrint ) ; // [°]  - Mesure the temperature
  BMP280_GetPressure(    Enable_SerialPrint ) ; // [Pa] - Mesure the pressure in Pa
  BMP280_GetAltitude(    Enable_SerialPrint ) ; // [m]  - Deduce the altitude from the mesured pressure

  BMP280_Sleep() ; // Put the sensor to sleep for power management

  delay(1000);

}
