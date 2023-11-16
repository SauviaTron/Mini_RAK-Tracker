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

#define LED_Blue  PA9 // The blue LED is connected to pin PA9 on the microcontroller.
#define LED_White PB2 // The white LED is connected to pin PB2 on the microcontroller.


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          SETUP()                                                                               //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

void setup() {

  // > Configure the baud rate
  Serial.begin( 115200 ) ; 

  // > Configure the pins as an output: 
  //   The pin delivers either 3.3V (HIGH state), the LED is on, or 0V (LOW state) the LED is off.

  pinMode(LED_Blue , OUTPUT); // Configuration of the blue LED
  pinMode(LED_White, OUTPUT); // Configuration of the white LED

}


// —————————————————————————————————————————————————————————————————————————————————————————————— //
//          SETUP()                                                                               //
// —————————————————————————————————————————————————————————————————————————————————————————————— //

void loop() {

  // > New loop
  Serial.println(".") ;

  // > Blue LED
  Serial.println( "> Blue LED  : ON") ;
  digitalWrite(LED_Blue, HIGH); delay(500); // Turn the blue LED on (HIGH is the voltage level) and wait for 500ms
  Serial.println( "> Blue LED  : OFF") ;
  digitalWrite(LED_Blue, LOW ); delay(500); // Turn the blue LED off (LOW is the voltage level) and wait for 500ms
  
  // > White LED
  Serial.println( "> White LED : ON") ;
  digitalWrite(LED_White, HIGH); delay(500); // Turn the blue LED on (HIGH is the voltage level) and wait for 500ms
  Serial.println( "> White LED : OFF") ;
  digitalWrite(LED_White, LOW ); delay(500); // Turn the blue LED off (LOW is the voltage level) and wait for 500ms

}
