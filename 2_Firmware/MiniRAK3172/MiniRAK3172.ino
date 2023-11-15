
// #include <Wire.h>

#include <SPI.h>
#include "System.h"


#define Use_BMP280    false  // Do you want to use the pressure sensor ? (Yes = true / No = false)
#define Use_VEML6040  false   // Do you want to use the light sensor ? (Yes = true / No = false)
#define Use_LSM303AGR false  // Do you want to use the accelerometer / magnetometer ? (Yes = true / No = false)
#define Use_GNSS      false  
#define Use_Flash     false   // Do you want to store sensor values into the flash memory ?

#if( Use_BMP280 == true )
  #include "src/BMP280/BMP280_Functions.h"
#endif

// > RGBW Color Sensor - VEML6040
//   Sensors     : RGB, White and Ambient Light Sensor 
//   I2C address : 0x10
//   Datasheet   : https://www.vishay.com/docs/84276/veml6040.pdf
#if( Use_VEML6040 == true )

  #include "src/RGBWLight/VEML6040.h"

  VEML6040 RGBWSensor;

  uint16_t Red, Green, Blue, White, CCT ;
  float AmbientLight ;

#endif


// > eCompass - LSM303AGR
//   Sensors     : 3-axis accelerometer and 3-axis magnetometer 
//   I2C address : 0x19 and 0x1E
//   Datasheet   : https://www.st.com/resource/en/datasheet/lsm303agr.pdf
#if( Use_LSM303AGR == true )

  #include "src/LSM303AGR_ACC_Sensor.h" // Accelerometer Library
  #include "src/LSM303AGR_MAG_Sensor.h" // Magnetometer Library

  #define DEV_I2C Wire    //Or Wire
  LSM303AGR_ACC_Sensor Acc(&DEV_I2C);
  LSM303AGR_MAG_Sensor Mag(&DEV_I2C);

  int32_t Acc_XYZ[3], Mag_XYZ[3] ;
  int Heading ;
  float Temperature, Temperature_ ;

#endif


// > GNSS - MAX M10S
//   Datasheet : 
#if( Use_GNSS == true )
  #include <TinyGPSPlus.h>
  TinyGPSPlus gps;
  String tmp_data = "";
  String debug_string = "";
  int direction_S_N = 0; // 0--S, 1--N
  int direction_E_W = 0; // 0--E, 1--W
#endif


// > Flash Memory - MX25R8035FZUIL0
//   Size      : 8M-BIT / 4262 pages of 256bytes 
//   ID Chip   : 0xC2 0x28 0x14
//   Datasheet : https://www.macronix.com/Lists/Datasheet/Attachments/8749/MX25R8035F,%20Wide%20Range,%208Mb,%20v1.6.pdf
#if( Use_Flash == true )

  #include "src/Flash/SPIFlash.h"       // Flash Library

  #define  csPin PA4                    // Refers to pin CS# which is connected to pin PA4 of the microcontroller
  SPIFlash SPIFlash(csPin)            ; // Specifying Chip Select

  uint16_t      flash_maxPage     = 4262 ; // Maximum number of pages in memory
  unsigned char flashPage[256]           ; // A page can contain 256 values. Each value must not exceed 255 (0xFF, 11111111).
  int           flashPage_address =    0 ; // Incremental variable to access one of the flashPage values
  uint16_t      page_number       =    0 ; // Incremental variable to select all pages 
  uint8_t       sector_number     =    0 ; // Initialisation
  int           Nb_Page_To_Read   =    0 ; // Number of pages that you want to read in memory
  int           pageByte          =    0 ;
  
#endif



// > setup()
//   Code executed only one time.
void setup() {
  
  Serial.begin( 115200 ) ; // Set baudrate at 115200
  delay(1000) ; // Adding a delay

  Serial.println("\nWelcome to the MiniRAK3172 program !") ; // Set a welcom message

  Wire_SetUp() ;
  I2C_Scanning( true ) ;
  pinMode( PA11, OUTPUT ) ;
  pinMode( PA12, OUTPUT ) ; 

  // LED Blue
  BlueLED_Setup( );

  // BMP280
  #if( Use_BMP280 == true )
    BMP280_GetStatus( );
  #endif

  // > RGBW Color Sensor - VEML6040
  #if( Use_VEML6040 == true )
    RGBWSensor.Configuration( );
  #endif

  // > eCompass - LSM303AGR
  #if( Use_LSM303AGR == true )

    // DEV_I2C.begin();

    // Initlialize components.
    Acc.begin() ;
    Mag.begin() ;

    // Acc.Enable();
    // Acc.EnableTemperatureSensor();
    // Mag.Enable();

  #endif

  // > GNSS | MAX-M10S
  #if( Use_GNSS == true )
    
    pinMode( PA1, OUTPUT ); digitalWrite(PA1, HIGH);

    // Initialize Serial for debug output
    time_t timeout = millis();
    Serial.begin(115200);
    while (!Serial) {
      if ((millis() - timeout) < 5000) { delay(100); }
      else { break; }
    }

    // gps init
    pinMode(WB_IO2, OUTPUT);
    digitalWrite(WB_IO2, 0); delay(1000);
    digitalWrite(WB_IO2, 1); delay(1000);

    Serial1.begin(9600);
    while (!Serial1)
      ;
    Serial.println("GPS uart init ok!");

  #endif
  digitalWrite(PA1, LOW); // GPS Diseable
  pinMode( PB2, OUTPUT ); digitalWrite(PB2, LOW);


  // > Flash Memory - MX25R8035FZUIL0
  #if( Use_Flash == true )

    pinMode(csPin, OUTPUT)    ; // SPI configuration
    digitalWrite(csPin, HIGH) ; // Enable SPI

    // Check SPI Flash ID
    SPIFlash.init()      ; // SPI initialisation
    SPIFlash.powerUp()   ; // SPI power up
    SPIFlash.getChipID() ; // Get SPI ID
    // SPIFlash.flash_chip_erase( false ); Serial.println("Flash erased!");

    if( 1 ){                                                                                  // ... for debug, we can print the page that we just write 
      SPIFlash.flash_read_pages(flashPage, page_number, 1) ;                                      // ... Read SPI Flash page data at page_number and read only one page 
      Serial.println((String)"  Page n°" + page_number ) ;                                        // ... Display page number
      for( int Sector = 0 ; Sector < 32 ; Sector++ ){                                             // ... For loop for display every data
        if( Sector < 10 ){ Serial.print( (String)"  Ligne n°0" + Sector + (String)" - " ) ;}        // ... Print Sector
        else{ Serial.print( (String)"  Ligne n°" + Sector + (String)" - " ); }                      // ...
        for( int SubSector = 0 ; SubSector < 8 ; SubSector++ ) {                                    // ... Display Data into 32 sectors
          char hexValue[3];                                                                         // ... Create an array of characters to store the formatted hexadecimal value
          sprintf(hexValue, "%02X", flashPage[Sector * 8 + SubSector]);                             // ... Hexadecimal formatting with at least 2 characters, prefixed by 0 if necessary
          Serial.print("0x"); Serial.print(hexValue); Serial.print(" ");                            // ... Display data
        } Serial.println(" ");                                                                      // ...
      }
    }

    SPIFlash.powerDown() ; // Put SPI flash into power down mode
    digitalWrite(csPin, LOW) ; // Enable SPI

  #endif

  pinMode(PA9, OUTPUT);

  api.system.sleep.lora(120000);

} // void setup()


void loop() {

  Serial.println('.') ; delay(100) ;

  digitalWrite( PA9, HIGH) ; Serial.println( "> Blue LED ON") ; delay(1000);

  RAK3172_Awake( ) ;

  #if( Use_BMP280 == true )
    Serial.println("> BMP280");
    BMP280_WakeUp();
    BMP280_GetTemperature( true );
    BMP280_GetPressure( true );
    BMP280_GetAltitude( true ) ;
    BMP280_Sleep();
  #endif

  // > RGBW Color Sensor - VEML6040
  #if( Use_VEML6040 == true )
    Serial.println("\n> VEML6040");

    RGBWSensor.Configuration() ; delay(325) ; // Adding delay to the sensor wake-up
    RGBWSensor.getData(&Red, &Green, &Blue, &White, &AmbientLight, &CCT );
    RGBWSensor.Sleep();

  #endif

  // > eCompass - LSM303AGR
  #if( Use_LSM303AGR == true )
    Serial.println("\n> LSM303AGR");

    Acc.Enable( ); Acc.GetAxes( Acc_XYZ ) ;            
    Acc.EnableTemperatureSensor( ); Acc.GetTemperature( &Temperature ); Temperature_ = Temperature ; 
    //Serial.println(Temperature_);
    Acc.DisableTemperatureSensor(); Acc.Disable() ;

    Mag.Enable(); Mag.GetAxes( Mag_XYZ) ; Mag.Disable(); 

    Heading = (atan2(Mag_XYZ[1],Mag_XYZ[0]) * 180) / 3.14159;  
    if (Heading< 0) { Heading = 360 + Heading; } // Normalize to 0-360
    Serial.printf("  Heading[°]: %i\n", Heading);
    
  #endif

  // > GNSS | MAX-M10S
  #if( Use_GNSS == true )
  digitalWrite(PA1, HIGH);
    //  Serial.println( "\n...") ;

	  bool newData = false;

	  // For one second we parse GPS data and report some key values
    // digitalWrite(PA1, HIGH);
    //  Serial.println("NMEA Data :") ;
	  for (unsigned long start = millis(); millis() - start < 10000;) {
		
      while (Serial1.available()) {
        char c = Serial1.read();
        // Serial.print(c);
        if (gps.encode(c)){

          newData = true ; 
          
          Serial.printf("\nNMEA Decoded | ");

          Serial.print(F("Location: ")); 
          if( gps.location.isValid() ) {
            Serial.print(gps.location.lat(), 6); Serial.print(F(",")); Serial.print(gps.location.lng(), 6);
          }
          else { Serial.print(F("INVALID")); }

          Serial.print(F(" - Date & Time: "));
          if( gps.date.isValid()) {
            Serial.print(gps.date.month()); Serial.print(F("/"));
            Serial.print(gps.date.day()); Serial.print(F("/"));
            Serial.print(gps.date.year());
          }
          else { Serial.print(F("INVALID")); }

          Serial.print(F(" "));
          if (gps.time.isValid()) {
            if (gps.time.hour() < 10) Serial.print(F("0"));
            Serial.print(gps.time.hour());
            Serial.print(F(":"));
            if (gps.time.minute() < 10) Serial.print(F("0"));
            Serial.print(gps.time.minute());
            Serial.print(F(":"));
            if (gps.time.second() < 10) Serial.print(F("0"));
            Serial.print(gps.time.second());
            Serial.print(F("."));
            if (gps.time.centisecond() < 10) Serial.print(F("0"));
            Serial.print(gps.time.centisecond());
          }
          else { Serial.print(F("INVALID")); }

        } // if (gps.encode(c))
      
      } // while (Serial1.available())

	  } // for (unsigned long start = millis(); millis() - start < 5000;)

    // digitalWrite(PA1, LOW);


    // if(newData == true) {

    //   Serial.printf("\nNMEA Decoded:\n");

    //   Serial.print(F("Location: ")); 
    //   if( gps.location.isValid() ) {
    //     Serial.print(gps.location.lat(), 6); Serial.print(F(",")); Serial.print(gps.location.lng(), 6);
    //   }
    //   else { Serial.print(F("INVALID")); }

    //   Serial.print(F(" - Date & Time: "));
    //   if( gps.date.isValid()) {
    //     Serial.print(gps.date.month()); Serial.print(F("/"));
    //     Serial.print(gps.date.day()); Serial.print(F("/"));
    //     Serial.print(gps.date.year());
    //   }
    //   else { Serial.print(F("INVALID")); }

    //   Serial.print(F(" "));
    //   if (gps.time.isValid()) {
    //     if (gps.time.hour() < 10) Serial.print(F("0"));
    //     Serial.print(gps.time.hour());
    //     Serial.print(F(":"));
    //     if (gps.time.minute() < 10) Serial.print(F("0"));
    //     Serial.print(gps.time.minute());
    //     Serial.print(F(":"));
    //     if (gps.time.second() < 10) Serial.print(F("0"));
    //     Serial.print(gps.time.second());
    //     Serial.print(F("."));
    //     if (gps.time.centisecond() < 10) Serial.print(F("0"));
    //     Serial.print(gps.time.centisecond());
    //   }
    //   else { Serial.print(F("INVALID")); }

    //   Serial.println();

    // }

  digitalWrite(PA1, LOW);
  #endif

  // > Flash Memory - MX25R8035FZUIL0
  #if( Use_Flash == true )
    Serial.println( "\n> Flash" );

    // If there is space left in the variable and pages are still available ...
    if( flashPage_address < 256 && page_number < flash_maxPage ){
      // Saves data in a table. The array consists of 256 values of 1byte, i.e. 8bit. 
      // Values must not exceed 255 (XXXX XXXX).  

      // > Save Temperature [XX.YY°C]
      /* 01 */ flashPage[flashPage_address]   = static_cast<int>(Temperature_)                                          ; // Get the integer part of the temperature [XX]
      /* 02 */ flashPage[flashPage_address+1] = static_cast<int>((Temperature_ - static_cast<int>(Temperature_)) * 100) ; // Get the floating part of the temperature [YY]
      
      flashPage_address = flashPage_address + 2 ; // Incrementes index for next values
      
      Serial.println( (String)"  Data stored into variable. Actual Address : " + flashPage_address);
    } 
    else if( flashPage_address >= 256 && page_number < flash_maxPage ) {                    // If there is no more free space in the save variable and there are pages available
                                                                                                // ... So we save the data
      digitalWrite(csPin, HIGH) ;                                                               // ... Enable Serial Peripheral Interface
      SPIFlash.powerUp();                                                                       // ... We power up the flash for backup
      SPIFlash.flash_page_program( flashPage, page_number ) ;                                   // ... we write page into flash memory

      if( 1 ){                                                                                  // ... for debug, we can print the page that we just write 
        SPIFlash.flash_read_pages(flashPage, page_number, 1) ;                                      // ... Read SPI Flash page data at page_number and read only one page 
        Serial.println((String)"  Page n°" + page_number ) ;                                        // ... Display page number
        for( int Sector = 0 ; Sector < 32 ; Sector++ ){                                             // ... For loop for display every data
          if( Sector < 10 ){ Serial.print( (String)"  Ligne n°0" + Sector + (String)" - " ) ;}        // ... Print Sector
          else{ Serial.print( (String)"  Ligne n°" + Sector + (String)" - " ); }                      // ...
          for( int SubSector = 0 ; SubSector < 8 ; SubSector++ ) {                                    // ... Display Data into 32 sectors
            char hexValue[3];                                                                         // ... Create an array of characters to store the formatted hexadecimal value
            sprintf(hexValue, "%02X", flashPage[Sector * 8 + SubSector]);                             // ... Hexadecimal formatting with at least 2 characters, prefixed by 0 if necessary
            Serial.print("0x"); Serial.print(hexValue); Serial.print(" ");                            // ... Display data
          } Serial.println(" ");                                                                      // ...
        }
      }

      page_number = page_number + 1 ;                                                           // ... Increment the page number variable for next memorise
      Serial.println((String)"  Page n°" + page_number + " has been written in the memory.");   // ... Display a msg
      flashPage_address = 0 ;                                                                   // ... Since we've just saved a page, we'll start again from zero, so we'll start saving variables from index 0 of the 'flashPage' variable.
      SPIFlash.powerDown() ;                                                                    // ... Shut down the flash memory
      digitalWrite(csPin, LOW) ;                                                                // ... Disable SPI
    }
    else { Serial.println("  Reached last page of Flash Memory - Data logging stopped."); }     // ... Msg in case of overflow the flash

  #endif  

  digitalWrite( PA9, LOW) ; Serial.println( "> Blue LED OFF") ; delay(100);
  RAK3172_Sleep( 2500 ) ;
  
} // void loop()


void RAK3172_Awake(  ){

  Wire_SetUp();

}

void RAK3172_Sleep( int sleepTimer ){

  pinMode( PA4, OUTPUT ) ; digitalWrite( PA4, HIGH ) ;
  pinMode( PA5, OUTPUT ) ; digitalWrite( PA5, LOW ) ;
  pinMode( PA6, OUTPUT ) ; digitalWrite( PA6, LOW ) ;
  pinMode( PA7, OUTPUT ) ; digitalWrite( PA7, LOW ) ;

  pinMode( PA4, OUTPUT ) ; digitalWrite( PA4, HIGH ) ; // Flash
  pinMode( PA5, OUTPUT ) ; digitalWrite( PA5, LOW ) ;
  pinMode( PA6, OUTPUT ) ; digitalWrite( PA6, LOW ) ;
  pinMode( PA7, OUTPUT ) ; digitalWrite( PA7, LOW ) ;

  pinMode( PA11, OUTPUT ) ; digitalWrite( PA11, HIGH ) ; // SDA
  pinMode( PA12, OUTPUT ) ; digitalWrite( PA12, HIGH ) ; // SCL
  pinMode( PA14, OUTPUT ) ; digitalWrite( PA14, LOW ) ;
  pinMode( PA13, OUTPUT ) ; digitalWrite( PA13, LOW ) ;
  pinMode( PA1, OUTPUT ) ; digitalWrite( PA1, LOW ) ; // Enable GPS
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
  pinMode( PA10, OUTPUT ) ; digitalWrite( PA10, HIGH ) ; // Vbat


  Serial.println( (String)"> RAK3172 - Sleep Mode (" + sleepTimer/1000 + "s)") ;
  api.system.sleep.all(  sleepTimer ) ;

}
