// /*
//   Blink

//   Turns an LED on for one second, then off for one second, repeatedly.

//   Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
//   it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
//   the correct LED pin independent of which board is used.
//   If you want to know what pin the on-board LED is connected to on your Arduino
//   model, check the Technical Specs of your board at:
//   https://www.arduino.cc/en/Main/Products

//   modified 8 May 2014
//   by Scott Fitzgerald
//   modified 2 Sep 2016
//   by Arturo Guadalupi
//   modified 8 Sep 2016
//   by Colby Newman

//   This example code is in the public domain.

//   https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
// */

// // the setup function runs once when you press reset or power the board
// void setup() {
//   // initialize digital pin LED_BUILTIN as an output.
//   pinMode(PA9, OUTPUT);
//   pinMode(PB2,OUTPUT);
// }

// // the loop function runs over and over again forever
// void loop() {
//   digitalWrite(PA9, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(100);                       // wait for a second
//   digitalWrite(PA9, LOW);    // turn the LED off by making the voltage LOW
//   delay(100);                       // wait for a second
//     digitalWrite(PB2, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(100);                       // wait for a second
//   digitalWrite(PB2, LOW);    // turn the LED off by making the voltage LOW
//   delay(100);                       // wait for a second
// }

#include <Wire.h>

void setup()
{
  Wire.begin();

  Serial.begin(115200);
  while (!Serial);
  Serial.println("\nI2C Scanner");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmission to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}

