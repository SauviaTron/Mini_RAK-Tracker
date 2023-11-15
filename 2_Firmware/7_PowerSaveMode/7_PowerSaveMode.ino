
#define LED_Blue PA9

void setup() {
  
  api.system.restoreDefault();
  Serial.begin( 115200 ) ;

  pinMode( LED_Blue, OUTPUT); digitalWrite( LED_Blue, HIGH ) ;


  
  pinMode( PA4, OUTPUT ) ; digitalWrite( PA4, HIGH ) ;
  pinMode( PA5, OUTPUT ) ; digitalWrite( PA5, LOW ) ;
  pinMode( PA6, OUTPUT ) ; digitalWrite( PA6, LOW ) ;
  pinMode( PA7, OUTPUT ) ; digitalWrite( PA7, LOW ) ;

  pinMode( PA11, OUTPUT ) ; digitalWrite( PA11, HIGH ) ;
  pinMode( PA12, OUTPUT ) ; digitalWrite( PA12, HIGH ) ;
  pinMode( PA14, OUTPUT ) ; digitalWrite( PA14, LOW ) ;
  pinMode( PA13, OUTPUT ) ; digitalWrite( PA13, LOW ) ;
  pinMode( PA1, OUTPUT ) ; digitalWrite( PA1, LOW ) ;
  pinMode( PB7, OUTPUT ) ; digitalWrite( PB7, LOW ) ;
  pinMode( PB6, OUTPUT ) ; digitalWrite( PB6, LOW ) ;
  pinMode( PA15, OUTPUT ) ; digitalWrite( PA15, LOW ) ;

  // pinMode( PA3, OUTPUT ) ; digitalWrite( PA3, LOW ) ;

  pinMode( PB3, OUTPUT ) ; digitalWrite( PB3, LOW ) ;
  pinMode( PB4, OUTPUT ) ; digitalWrite( PB4, LOW ) ;
  pinMode( PB5, OUTPUT ) ; digitalWrite( PB5, LOW ) ;
  pinMode( PA0, OUTPUT ) ; digitalWrite( PA0, LOW ) ;
  pinMode( PB12, OUTPUT ) ; digitalWrite( PB12, LOW ) ;
  pinMode( PB2, OUTPUT ) ; digitalWrite( PB2, LOW ) ;
  pinMode( PA10, OUTPUT ) ; digitalWrite( PA10, HIGH ) ;




}

void loop() {

  Serial.println( "." )               ;                                delay( 1000 ) ;
  Serial.println( "> Blue LED : ON" ) ; digitalWrite(LED_Blue, HIGH) ; delay( 1000 ) ;
  Serial.println( "> Blue LED : OFF") ; digitalWrite(LED_Blue, LOW ) ; delay( 1000 ) ;

  RAK3172_Sleep( 2000 ) ;

}

/**
 * @param sleepTimer Time in ms where the µC will be in sleep mode
 */
void RAK3172_Sleep( int sleepTimer ){

  Serial.println( (String)"> RAK3172 - Sleep Mode (" + sleepTimer/1000 + "s)") ;
  api.system.sleep.all(  sleepTimer ) ;

}
