int incomingByte = 0; // for incoming serial data

void setup() {
  Serial1.begin(115200); // opens serial port, sets data rate to 9600 bps
  Serial1.println("Hello");
}

void loop() {

  Serial1.println(".");
  // send data only when you receive data:
  incomingByte = 0;

  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();

    // say what you got:
    Serial1.print("I received: "); Serial1.println(incomingByte, DEC);
    
    if( incomingByte == 48 ){ Serial1.println("Button 0 pressed.");}
    if( incomingByte == 49 ){ Serial1.println("Button 0 pressed.");}
    if( incomingByte == 50 ){ Serial1.println("Button 0 pressed.");}
    if( incomingByte == 51 ){ Serial1.println("Button 0 pressed.");}
    if( incomingByte == 52 ){ Serial1.println("Button 0 pressed.");}
    if( incomingByte == 53 ){ Serial1.println("Button 0 pressed.");}
  
  }



  delay(1000);
  
}