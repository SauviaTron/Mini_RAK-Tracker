/*  
 *  Created on: 06/04/2022
 *      Author: Andrea Sauviat
 *      E-mail: a-sauviat@laposte.net
 * 
 *  Description: Read SPI Flash Memory for the LoRa Sensor Tile
 *               Print data in serial monitor at baud 115200
 *               DATE - TIME - LoRaWAN - GPS - Battery 
 *               
 *  Board: LoRa Sensor Tile OR Grasshopper - L082CZ
 *         MX25L12835FZNI - 16 MByte SPI NOR flash memory
 *         
 *  URL Board: https://www.tindie.com/products/tleracorp/lorasensortile/
 *  URL: https://github.com/kriswiner/CMWX1ZZABZ/tree/master/LoRaSensorTile
 *  
 */

#include <SPI.h>
#include "SPIFlash.h"


// Highest page number is 0xFFFF = 65535 for 128 Mbit flash
// Highest page number is 0x7FFF = 32767 for  64 Mbit flash
// Highest page number is 0x0EFF =  4095 for   8 Mbit flash

// MX25R8035F - 8Mbit flash

#define LED PA9

// --- SPI configuration --- //
#define  csPin PA4
SPIFlash SPIFlash(csPin)          ; // SPI pin = 25
uint16_t max_page_number = 0xFFFF ; // 16 Mbit flash


// --- SPI variables --- //
unsigned char flashPage[256]        ; // Definition of flashPage
uint16_t      page_number     = 0   ; // Initialisation 
uint8_t       sector_number   = 0   ; // Initialisation
int           Nb_Page_To_Read = 0  ; // Number of pages that you want to read in memory
int pageByte = 0;



// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//                                                                                                                                                                                     //
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


void setup(void) { 


    Serial.begin(115200) ; // Start serial connection
    delay(10000)          ; // Delay for enable Node-Red

    pinMode( LED , OUTPUT);


    // --- Welcome message --- //
    Serial.println();
    Serial.println("     --- SPI Flash Reading ---    ") ; 
    Serial.println();
    Serial.println("Decice        : RAK3172           ") ;
    Serial.println("Memory Size   : 8 MBit           ") ;
    Serial.println("Max. Page Nbr : 4262            ") ;
    Serial.println();



    // --- SPI Configuration --- // 
    pinMode(csPin, OUTPUT)    ; // SPI configuration
    digitalWrite(csPin, HIGH) ; // Enable SPI


    // Check SPI Flash ID
    SPIFlash.init()      ; // SPI initialisation
    SPIFlash.powerUp()   ; // SPI power up
    SPIFlash.getChipID() ; // Get SPI ID
    SPIFlash.flash_chip_erase(false) ; // Erase memory 


    // --- Read SPI flash --- //
    for(page_number = 0; page_number <= Nb_Page_To_Read; page_number++)  {
  
        //  Serial.print("Read Page 0x"); Serial.println(page_number, HEX);
        SPIFlash.flash_read_pages(flashPage, page_number, 1) ; // Read SPI Flash page data at page_number and read only one page 
        
        Serial.println();
        Serial.println((String)"Page n°" + page_number );

        for( int Sector = 0 ; Sector < 32 ; Sector++ ){

          Serial.print( (String)"Ligne n°" + Sector + (String)" - " );
        
          for( int SubSector = 0 ; SubSector < 8 ; SubSector++ ) {

            pageByte = Sector * 8 + SubSector ; 
            Serial.print( flashPage[ pageByte ] , HEX ) ;
            Serial.print( " " );

          } // for(sector_number = 0; sector_number < 8; sector_number++)

        Serial.println(" ");

        }
    
    } // for(page_number = 0; page_number < 20; page_number++)


    // flashPage[0] = 0 ;
    // flashPage[16] = 0 ;
    // flashPage[21] = 0 ;

    // SPIFlash.flash_page_program( flashPage, 0 );



    // SPIFlash.powerDown() ; // Put SPI flash into power down mode

} // void setup()


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//                                                                                                                                                                                     //
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


void loop(void){ 
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(1000);
 }
