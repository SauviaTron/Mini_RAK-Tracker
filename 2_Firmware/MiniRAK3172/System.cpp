
#include <Arduino.h>
#include <Wire.h>
#include "System.h"

#define Pin_BlueLED PA9

void BlueLED_Setup( ){
  pinMode( Pin_BlueLED, OUTPUT );
}

void BlueLED_TurnONOFF( bool BlueLED_ON ){
  if( BlueLED_ON == true ){ digitalWrite( Pin_BlueLED, HIGH) ; }  // If we want to turn the Blue LED ON, we make it
  digitalWrite( Pin_BlueLED, LOW ) ;                             // Else, we don't.
}

void Blink_LED( void *data){ 
  digitalWrite( Pin_BlueLED, HIGH ); delay( 1000 );
  digitalWrite( Pin_BlueLED, LOW ); delay( 1000 );
}

void StartTimer_BlinkBlueLED( bool Display_Serial ){
  if (api.system.timer.create(RAK_TIMER_0, (RAK_TIMER_HANDLER)Blink_LED, RAK_TIMER_PERIODIC) != true) {
    Serial.printf("Creating timer failed.\r\n");
  } else if (api.system.timer.start(RAK_TIMER_0, 2000, NULL) != true) {
    Serial.printf("Starting timer failed.\r\n");
  }
}

void Wire_SetUp( ){
  Wire.begin();
}

void I2C_Scanning( bool Display_Serial ) {

  byte error, address; // Variable declaration
  int nDevices = 0 ; 

  Serial.println("Scanning...");

  for( address = 1 ; address < 127 ; address++ ) {

    // The i2c_scanner uses the return value of
    // the Write.endTransmission to see if
    // a device did acknowledge to the address.

    Wire.beginTransmission(address); // Checking the address
    error = Wire.endTransmission(); // Get the value of the transmission

    if (error == 0) {                                     // If no error has been detected ...
      Serial.print("I2C device found at address 0x");         // ... then, a device has been found
      if (address<16){ Serial.print("0"); }                   // ... so we will display it address
      Serial.print(address,HEX);                              // ...
      Serial.println("  !");                                  // ...
      nDevices++;                                             // ... and increment the number of device detected
    }
    else if (error==4) {                                  // If an error has been detected, ...
      Serial.print("Unknown error at address 0x");            // ... we informe the user
      if (address<16){ Serial.print("0"); }                   // ... by display the address where the error has been found
      Serial.println(address,HEX);                            // ...
    }

  } // for( address = 1 ; address < 127 ; address++ )  

  if (nDevices == 0)                                      // If no device has been found, ...
    Serial.println("No I2C devices found\n");                 // ... we inform the user.
  else                                                    // Else
    Serial.println("done\n");                                 // ... we display an end msg.
}
