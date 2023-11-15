/*

The MIT License (MIT)

Copyright (c) 2015 thewknd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "Wire.h"
#include "veml6040.h"

VEML6040 RGBWSensor;

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  if(!RGBWSensor.begin()) {
    Serial.println("ERROR: couldn't detect the sensor");
    while(1){}
  }
   
  /*
   * init RGBW sensor with: 
   *  - 320ms integration time
   *  - auto mode
   *  - color sensor enable
   */
    
	VEML6040_Configuration( );

}

void loop() {
  VEML6040_GetRed( true );
  VEML6040_GetGreen( true );
  VEML6040_GetBlue( true );
  VEML6040_GetCCT( true );
  VEML6040_GetAmbiantLight( true );
  delay(1000);
}

void VEML6040_Configuration( ) {
  RGBWSensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
}

int VEML6040_GetRed( bool Display_Serial ) {
  int VEML6040_Red = RGBWSensor.getRed() ;
  if( Display_Serial == true ) {
    Serial.println( (String)"Red : " + VEML6040_Red );
  }
  return VEML6040_Red ;
}

int VEML6040_GetGreen( bool Display_Serial ) {
  int VEML6040_Green= RGBWSensor.getGreen() ;
  if( Display_Serial == true ) {
    Serial.println( (String)"Green : " + VEML6040_Green );
  }
  return VEML6040_Green ;
}

int VEML6040_GetBlue( bool Display_Serial ) {
  int VEML6040_Blue = RGBWSensor.getBlue() ;
  if( Display_Serial == true ) {
    Serial.println( (String)"Blue : " + VEML6040_Blue );
  }
  return VEML6040_Blue ;
}

int VEML6040_GetWhite( bool Display_Serial ) {
  int VEML6040_White = RGBWSensor.getWhite() ;
  if( Display_Serial == true ) {
    Serial.println( (String)"White : " + VEML6040_White );
  }
  return VEML6040_White ;
}

int VEML6040_GetCCT( bool Display_Serial ) {
  int VEML6040_CCT = RGBWSensor.getCCT() ;
  if( Display_Serial == true ) {
    Serial.println( (String)"Correlated Color Temperature in 260K : " + VEML6040_CCT );
  }
  return VEML6040_CCT ;
}

int VEML6040_GetAmbiantLight( bool Display_Serial ) {
  int VEML6040_AmbientLight = RGBWSensor.getAmbientLight() ;
  if( Display_Serial == true ) {
    Serial.println( (String)"Ambiante Light : " + VEML6040_AmbientLight + (String)" lux" );
  }
  return VEML6040_AmbientLight ;
}


















