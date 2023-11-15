#include <stdint.h>
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
#include <Arduino.h>
#include "Wire.h"
#ifndef __MATH_H
#include <math.h>
#endif
#include "VEML6040.h"


VEML6040::VEML6040(void) {
  
}

bool VEML6040::begin(void) {
  bool sensorExists = false;
  Wire.begin();
  Wire.beginTransmission(VEML6040_I2C_ADDRESS);
  if (Wire.endTransmission() == 0) {
    sensorExists = true;
  }
  return sensorExists;
}

void VEML6040::setConfiguration(uint8_t configuration) {
  Wire.beginTransmission(VEML6040_I2C_ADDRESS);  
  Wire.write(COMMAND_CODE_CONF); 
  Wire.write(configuration); 
  Wire.write(0);
  Wire.endTransmission(); 
  lastConfiguration = configuration;
}

uint16_t VEML6040::read(uint8_t commandCode) {
  uint16_t data = 0; 
  
  Wire.beginTransmission(VEML6040_I2C_ADDRESS);
  Wire.write(commandCode);
  Wire.endTransmission(false);
  Wire.requestFrom(VEML6040_I2C_ADDRESS,2);
  while(Wire.available()) 
  {
    data = Wire.read(); 
    data |= Wire.read() << 8;
  }
  
  return data; 
}

uint16_t VEML6040::getRed(void) {
  uint16_t red = read(COMMAND_CODE_RED) ;
  Serial.println( (String)"Red : " + red );
  return red;
}

uint16_t VEML6040::getGreen(void) {
  uint16_t green = read(COMMAND_CODE_GREEN) ;
  Serial.println( (String)"Green : " + green );
  return green;
}

uint16_t VEML6040::getBlue(void) {
  uint16_t blue = read(COMMAND_CODE_BLUE) ;
  Serial.println( (String)"Blue : " + blue );
  return blue;
}

uint16_t VEML6040::getWhite(void) {
  uint16_t white = read(COMMAND_CODE_WHITE) ;
  Serial.println( (String)"White : " + white );
  return white;
}

float VEML6040::getAmbientLight(void) {
  uint16_t sensorValue; 
  float ambientLightInLux;
  
  sensorValue = read(COMMAND_CODE_GREEN);
  
  switch(lastConfiguration & 0x70) {
  
    case VEML6040_IT_40MS:    ambientLightInLux = sensorValue * VEML6040_GSENS_40MS;
                              break;
    case VEML6040_IT_80MS:    ambientLightInLux = sensorValue * VEML6040_GSENS_80MS;
                              break;
    case VEML6040_IT_160MS:   ambientLightInLux = sensorValue * VEML6040_GSENS_160MS;
                              break;
    case VEML6040_IT_320MS:   ambientLightInLux = sensorValue * VEML6040_GSENS_320MS;
                              break;
    case VEML6040_IT_640MS:   ambientLightInLux = sensorValue * VEML6040_GSENS_640MS;
                              break; 
    case VEML6040_IT_1280MS:  ambientLightInLux = sensorValue * VEML6040_GSENS_1280MS; 
                              break;   
    default:                  ambientLightInLux = -1;
                              break;                             
  } 

  Serial.println( (String)"Ambient light : " + ambientLightInLux );
  return ambientLightInLux;
}

uint16_t VEML6040::getCCT(float offset) {
  uint16_t red,blue,green;
  float cct,ccti;
  
  red = read(COMMAND_CODE_RED);
  green = read(COMMAND_CODE_GREEN);
  blue = read(COMMAND_CODE_BLUE);
  
  ccti = ((float)red-(float)blue) / (float)green;
  ccti = ccti + offset; 
  cct = 4278.6 * pow(ccti,-1.2455);

  Serial.println( (String)"Correlated Color Temperature in 260K : " + (uint16_t)cct );
  return((uint16_t)cct);
}

void VEML6040::Configuration( ) {
  
  begin();
  setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
  delay(10);
  Serial.println("  VEML6040 - WakeUp");
}

void VEML6040::Sleep(){
  setConfiguration( VEML6040_IT_40MS +      // Integration Time setting
                    VEML6040_AF_AUTO +      // Auto force mode - Auto
                    VEML6040_SD_DISABLE);   // Chip shutdown - Disable Color sensor
  Serial.println("  VEML6040 - Sleep");
}

void VEML6040::getData( uint16_t *Red, uint16_t *Green, uint16_t *Blue, uint16_t *White, float *AmbientLight, uint16_t *CCT ){
  
  *Red = read(COMMAND_CODE_RED);
  *Green = read(COMMAND_CODE_GREEN);
  *Blue = read(COMMAND_CODE_BLUE);
  *White = read(COMMAND_CODE_WHITE) ;

  float ccti = ((float)*Red-(float)*Blue) / (float)*Green;
  ccti = ccti + 0.5 ; 
  float CCT_float = 4278.6 * pow(ccti,-1.2455);
  *CCT = (uint16_t)CCT_float ;

  uint16_t sensorValue = *Green ;
  
  switch(lastConfiguration & 0x70) {
  
    case VEML6040_IT_40MS:    *AmbientLight = sensorValue * VEML6040_GSENS_40MS;
                              break;
    case VEML6040_IT_80MS:    *AmbientLight = sensorValue * VEML6040_GSENS_80MS;
                              break;
    case VEML6040_IT_160MS:   *AmbientLight = sensorValue * VEML6040_GSENS_160MS;
                              break;
    case VEML6040_IT_320MS:   *AmbientLight = sensorValue * VEML6040_GSENS_320MS;
                              break;
    case VEML6040_IT_640MS:   *AmbientLight = sensorValue * VEML6040_GSENS_640MS;
                              break; 
    case VEML6040_IT_1280MS:  *AmbientLight = sensorValue * VEML6040_GSENS_1280MS; 
                              break;   
    default:                  *AmbientLight = -1;
                              break;                             
  } 

  Serial.print( (String)"  R(" + *Red   );
  Serial.print( (String)") G(" + *Green );
  Serial.print( (String)") B(" + *Blue  );
  Serial.print( (String)") W(" + *White ); Serial.println(")") ;
  Serial.println( (String)"  Ambient light : " + *AmbientLight );
  Serial.println( (String)"  Correlated Color Temperature in 260K : " + *CCT );
  

}



