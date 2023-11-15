

#define LED_Blue  PA9 // The blue LED is positioned on the RAK3172's PA9 pin (see KIKAD schematic).
#define LED_White PB2 // The white LED (GPS PPS) is positioned on the RAK3172's PA9 pin (see KIKAD schematic).

int incomingByte = 0; // for incoming serial data

void setup() {

  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  Serial.println("\nMenu code");

  pinMode( LED_Blue , OUTPUT ); digitalWrite( LED_Blue, HIGH );
  pinMode( LED_White, OUTPUT );

  delay(1 * 1000);

  Serial.println("Choose a mode");

  unsigned long startTime = millis() ;                                  // Get time now
  while( millis() - startTime < 30000 ){                                // For 30 seconds, we will execute the loop :
    if (Serial.available() > 0) {                                           // If the user enters anything in the serial monitor, ...
      incomingByte = Serial.read();                                             // ... we will read the command and memorize it
      // Serial.print("I received: "); Serial.println(incomingByte, DEC);       // ... and display it for debug.
      break ;                                                                   // ... and stop / waiting in the while loop.
    }
  }

  digitalWrite( LED_Blue, LOW );

}

void loop() {

  switch( incomingByte ){

    case 49: Serial.println( "Mode 1" ) ; 
      digitalWrite( LED_Blue, HIGH); delay(1000) ;
      digitalWrite( LED_Blue, LOW ); delay(1000) ;
      break ; // Caes number refer to the ASCII table 

    case 50: Serial.println( "Mode 2" ) ; 
      digitalWrite( LED_White, HIGH); delay(1000) ;
      digitalWrite( LED_White, LOW ); delay(1000) ;    
    break ;

    case 51: Serial.println( "Mode 3" ) ; 
      digitalWrite( LED_Blue, HIGH); digitalWrite( LED_White, HIGH); delay(1000) ;
      digitalWrite( LED_Blue, LOW ); digitalWrite( LED_White, LOW ); delay(1000) ;
    break ;

    default: Serial.println( "Mode 0" ) ; 
      digitalWrite( LED_Blue , HIGH); delay(1000) ;
      digitalWrite( LED_Blue , LOW ); delay(1000) ;
      digitalWrite( LED_White, HIGH); delay(1000) ;
      digitalWrite( LED_White, LOW ); delay(1000) ;  
    break ;
  }

}