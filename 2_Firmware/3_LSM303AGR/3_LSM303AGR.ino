/**
 ******************************************************************************
 * @file    X_NUCLEO_IKS01A2_LSM303AGR_DataLog_Terminal.ino
 * @author  AST
 * @version V1.0.0
 * @date    7 September 2017
 * @brief   Arduino test application for the STMicrolectronics X-NUCLEO-IKS01A2
 *          MEMS Inertial and Environmental sensor expansion board.
 *          This application makes use of C++ classes obtained from the C
 *          components' drivers.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


// Includes.
#include "src/LSM303AGR_ACC_Sensor.h"
#include "src/LSM303AGR_MAG_Sensor.h"


// #if defined(ARDUINO_SAM_DUE)
// #define DEV_I2C Wire1   //Define which I2C bus is used. Wire1 for the Arduino Due
// #define Serial Serial
// #else
#define DEV_I2C Wire    //Or Wire
// #define Serial Serial
// #endif

// Components.
LSM303AGR_ACC_Sensor Acc(&DEV_I2C);
LSM303AGR_MAG_Sensor Mag(&DEV_I2C);

void setup() {

  // Initialize serial for output.
  Serial.begin(115200);
  
  // Initialize I2C bus.
  DEV_I2C.begin();

  // Initlialize components.
 
  LSM303AGR_Initialisation( true, true, true ) ;

  Acc.Enable();
  Acc.EnableTemperatureSensor();
  Mag.Enable();
}

void loop() {

  Serial.println("");

  LSM303AGR_GetAcc( true ) ;
  LSM303AGR_GetMag( true ) ;
  LSM303AGR_GetTemperature( true ) ;

  delay(1000);
}

void LSM303AGR_Initialisation( bool Init_Acc, bool Init_Mag, bool Display_Serial ){
  if( Init_Acc == true ){
    Acc.begin() ;
    if( Display_Serial == true ){ Serial.println("Accelerometer initialized.") ; }
  }
  if( Init_Mag == true ){
    Mag.begin() ;
    if( Display_Serial == true ){ Serial.println("Magnetometer initialized.") ; } 
  }
}




int32_t LSM303AGR_GetAcc( bool Display_Serial ) {
  int32_t Acc_XYZ[3] ;
  Acc.GetAxes( Acc_XYZ );
  if( Display_Serial == true ){
      Serial.print("| Acc[mg]: ");
      Serial.print(Acc_XYZ[0]); Serial.print(" "); // X axis
      Serial.print(Acc_XYZ[1]); Serial.print(" "); // Y axis
      Serial.println(Acc_XYZ[2]);                  // Z axis
  }
  return Acc_XYZ[3] ;
}

int32_t LSM303AGR_GetMag( bool Display_Serial ) {

  int32_t Mag_XYZ[3] ;

  Mag.GetAxes( Mag_XYZ );
  if( Display_Serial == true ){
      Serial.print("| Mag[mGauss]: ");
      Serial.print(Mag_XYZ[0]); Serial.print(" "); // X axis
      Serial.print(Mag_XYZ[1]); Serial.print(" "); // Y axis
      Serial.print(Mag_XYZ[2]);                  // Z axis
  }

  // Calculate the compass heading / angle of the vector y,x 
  Mag_XYZ[3] = (atan2(Mag_XYZ[1],Mag_XYZ[0]) * 180) / 3.14159;
  if (Mag_XYZ[3] < 0) { Mag_XYZ[3] = 360 + Mag_XYZ[3]; } // Normalize to 0-360
  Serial.printf(" - Heading[°]: %i\n", Mag_XYZ[3]);
 
  return Mag_XYZ[3] ;

}

float LSM303AGR_GetTemperature( bool Display_Serial ) {
  float Temperature ;
  Acc.GetTemperature( &Temperature );
  if( Display_Serial == true ){
      Serial.print("| Temperature : ");
      Serial.print( Temperature , 2 ) ; Serial.println(" °C"); 
  }
  return Temperature ;
}









