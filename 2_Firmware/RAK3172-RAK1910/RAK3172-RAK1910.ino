#include <Arduino.h>

#include <TinyGPS++.h> //http://librarymanager/All#TinyGPS

TinyGPSPlus gps;
String tmp_data = "";
String debug_string = "";
int direction_S_N = 0; // 0--S, 1--N
int direction_E_W = 0; // 0--E, 1--W

#define LED_BUILTIN PA9

// The serial connection to the GPS device
void setup() {

  pinMode( PA1, OUTPUT );
  digitalWrite(PA1, HIGH);

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

}



void loop(){
//  Serial.println( "\n...") ;

	//bool newData = false;

	// For one second we parse GPS data and report some key values
  digitalWrite(PA1, HIGH);
//  Serial.println("NMEA Data :") ;
	for (unsigned long start = millis(); millis() - start < 5000;) {
		
    while (Serial1.available()) {
			char c = Serial1.read();
			Serial.print(c);
			//if (gps.encode(c)){ newData = true ; }
		}

	}
  digitalWrite(PA1, LOW);

/*
	if(newData == true) {

		Serial.printf("\nNMEA Decoded:\n");

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

    Serial.println();

	}*/

  //delay(2000);

}