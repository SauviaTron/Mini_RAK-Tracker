
#include <Adafruit_BMP280.h>
#include "BMP280_Functions.h"

Adafruit_BMP280 BMP280 ; // Set variable name 

void BMP280_GetStatus( ) {

  // Get the status of the BMP280 - I2C Address : 0x76
  unsigned status = BMP280.begin( 0x76 ) ; 

  if (!status) { // If the status is falty ...
    Serial.println("Could not find a valid BMP280 sensor, check wiring or try a different address!"); // ... then display some information
    Serial.print("SensorID was: 0x"); Serial.println(BMP280.sensorID(),16);
    Serial.print("ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("ID of 0x60 represents a BME 280.\n");
    Serial.print("ID of 0x61 represents a BME 680.\n");
    while (1) { } ;
  }

}

void BMP280_WakeUp( ) {

    BMP280.setSampling( Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                        Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                        Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                        Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                        Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    Serial.println("BMP280 - Wakeup") ;
                        
}

void BMP280_Sleep( ) {

    BMP280.setSampling( Adafruit_BMP280::MODE_SLEEP,     /* Operating Mode. */
                        Adafruit_BMP280::SAMPLING_NONE,     /* Temp. oversampling */
                        Adafruit_BMP280::SAMPLING_NONE,    /* Pressure oversampling */
                        Adafruit_BMP280::FILTER_OFF,      /* Filtering. */
                        Adafruit_BMP280::STANDBY_MS_1); /* Standby time. */
                        
    Serial.println("BMP280 - Sleep");
}

float BMP280_GetTemperature( bool Display_Value ) {
  float BMP280_Temperature = BMP280.readTemperature() ;
  if ( Display_Value == true ){
    Serial.println( String("Temperature : ") + BMP280_Temperature + String(" °C") ) ;
  }
  return BMP280_Temperature ;
}

float BMP280_GetPressure( bool Display_Value ) {
  float BMP280_Pressure = BMP280.readPressure() ;
  if ( Display_Value == true ){
    Serial.println( String("Pressure : ") + BMP280_Pressure + String(" Pa") ) ;
  }
  return BMP280_Pressure ;
}

float BMP280_GetAltitude( bool Display_Value ) {
  float BMP280_Altitude = BMP280.readAltitude( 1013.15 ) ; // Default value, you need to adjuste it to your local forecast.
  if ( Display_Value == true ){
    Serial.println( String("Altitude : ") + BMP280_Altitude + String(" m") ) ;
  }
  return BMP280_Altitude ;
}





