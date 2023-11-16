/*  
 *  Created on: 16/11/2023
 *      Author: Andrea Sauviat
 *      E-mail: a-sauviat@laposte.net
 * 
 *  Description:  Blinks LEDs on the Mini RAK-Tracker
 *        
 *  GitHub     : https://github.com/SauviaTron/Mini_RAK-Tracker
 * 
 */


// > The libraries you need :
#include <Wire.h> // For I2C


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          GLOBAL VARIABLES                                                                      //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

byte I2C_Error         ; // I2C error
byte I2C_deviceAddress ; // Get I2C address of the component
int I2C_howManyDevices ; // Counts the number of components detected


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          SETUP()                                                                               //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

void setup() {

  // > Configure the baud rate
  Serial.begin( 115200 ) ; 
  while ( !Serial ) {} ;    // Wait for the serial to be available
  delay(2500) ;             // Add a custom delay for user to 'see' the setup function


  // > Welcome Msg 
  Serial.println("\nWelcome to the I2C Scanner program !") ;


  // > Configure the I2C
  Wire.begin();

}


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          LOOP()                                                                                //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

void loop() {

  // > New loop
  Serial.println("\n> I2C - Scanning...");

  I2C_howManyDevices = 0 ; // Initializes the counter

  // Check all the I2C address to see if there is a device wired on it
  for(I2C_deviceAddress = 1; I2C_deviceAddress < 127; I2C_deviceAddress++ ) {
    
    Wire.beginTransmission( I2C_deviceAddress ) ; // Try to communicate with the component
    I2C_Error = Wire.endTransmission()          ; // Get error

    
    if( I2C_Error == 0 ) {                              // If no error detected
      Serial.print("  Device found at address 0x") ;        // Display a msg
      if( I2C_deviceAddress<16 ){ Serial.print("0"); }      // Display address
      Serial.println(I2C_deviceAddress,HEX) ;               // ...
      I2C_howManyDevices = I2C_howManyDevices + 1 ;         // +1 to the number of devices detected
    }
    else if( I2C_Error==4 ) {                           // If a weird device is detected
      Serial.print("  Unknown error at address 0x");        // Display a msg
      if( I2C_deviceAddress<16 ){ Serial.print("0"); }      // Display address
      Serial.println(I2C_deviceAddress,HEX) ;               // ...     
    }

  }

  if( I2C_deviceAddress == 0 ){ Serial.println("  No I2C devices found"); }
  else { Serial.println("  I2C Scanning done"); }

  delay(5000);           // wait 5 seconds for next scan

}

