/***
 *  This example shows LoRaWan protocol joining the network in OTAA mode, class A, region EU868.
 *  Device will send uplink every 20 seconds.
***/

#define OTAA_PERIOD   (60000)
/*************************************

   LoRaWAN band setting:
     RAK_REGION_EU433
     RAK_REGION_CN470
     RAK_REGION_RU864
     RAK_REGION_IN865
     RAK_REGION_EU868
     RAK_REGION_US915
     RAK_REGION_AU915
     RAK_REGION_KR920
     RAK_REGION_AS923

 *************************************/
#define OTAA_BAND     (RAK_REGION_EU868)
#define OTAA_DEVEUI   {0xAC, 0x1F, 0x09, 0xFF, 0xFE, 0x0E, 0x49, 0x55} 
#define OTAA_APPEUI   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} 
#define OTAA_APPKEY   {0x8F, 0x29, 0xB7, 0xC3, 0xA4, 0x18, 0xBC, 0x2D, 0x7F, 0x16, 0xF8, 0xE2, 0x5E, 0x9C, 0x90, 0x00} 

/** Packet buffer for sending */
uint8_t collected_data[64] = { 0 };

void recvCallback(SERVICE_LORA_RECEIVE_T * data)
{
    if (data->BufferSize > 0) {
        Serial.println("Something received!");
        for (int i = 0; i < data->BufferSize; i++) {
            Serial.printf("%x", data->Buffer[i]);
        }
        Serial.print("\r\n");
    }
}

void joinCallback(int32_t status)
{
    Serial.printf("Join status: %d\r\n", status);
}

/*************************************
 * enum type for LoRa Event
    RAK_LORAMAC_STATUS_OK = 0,
    RAK_LORAMAC_STATUS_ERROR,
    RAK_LORAMAC_STATUS_TX_TIMEOUT,
    RAK_LORAMAC_STATUS_RX1_TIMEOUT,
    RAK_LORAMAC_STATUS_RX2_TIMEOUT,
    RAK_LORAMAC_STATUS_RX1_ERROR,
    RAK_LORAMAC_STATUS_RX2_ERROR,
    RAK_LORAMAC_STATUS_JOIN_FAIL,
    RAK_LORAMAC_STATUS_DOWNLINK_REPEATED,
    RAK_LORAMAC_STATUS_TX_DR_PAYLOAD_SIZE_ERROR,
    RAK_LORAMAC_STATUS_DOWNLINK_TOO_MANY_FRAMES_LOSS,
    RAK_LORAMAC_STATUS_ADDRESS_FAIL,
    RAK_LORAMAC_STATUS_MIC_FAIL,
    RAK_LORAMAC_STATUS_MULTICAST_FAIL,
    RAK_LORAMAC_STATUS_BEACON_LOCKED,
    RAK_LORAMAC_STATUS_BEACON_LOST,
    RAK_LORAMAC_STATUS_BEACON_NOT_FOUND,
 *************************************/

void sendCallback(int32_t status)
{
    if (status == RAK_LORAMAC_STATUS_OK) {
        Serial.println("Successfully sent");
    } else {
        Serial.println("Sending failed");
    }
}

void setup(){
    Serial.begin(115200, RAK_AT_MODE);
    delay(2500);
  
    Serial.println("RAKwireless LoRaWan OTAA Example");
    Serial.println("------------------------------------------------------");
    delay(2500);

    if(api.lorawan.nwm.get() != 1) {
        Serial.printf("Set Node device work mode %s\r\n",
            api.lorawan.nwm.set(1) ? "Success" : "Fail");
        api.system.reboot();
    }
    delay(2500);

    uint8_t node_device_eui[8] = OTAA_DEVEUI;
    uint8_t node_app_eui[8] = OTAA_APPEUI;
    uint8_t node_app_key[16] = OTAA_APPKEY;
  


  
  delay(2500);

  // LoRa Keys //
  uint8_t buff8[8] = {0} ;
  uint8_t buff16[16] = {0};
  Serial.println("Setting LoRa Keys");

  Serial.printf( "..DevEUI - %s - 0x", api.lorawan.deui.set(node_device_eui, 8) ? "OK" : "Fail" );
  api.lorawan.deui.get(buff8, 8); for (int i = 0; i < 8; i++) { Serial.printf("%02X", buff8[i]); } Serial.println();
  Serial.printf( "..APPEUI - %s - 0x", api.lorawan.appeui.set(node_app_eui, 8) ? "OK" : "Fail" );
  api.lorawan.appeui.get(buff8, 8); for (int i = 0; i < 8; i++) { Serial.printf("%02X", buff8[i]); } Serial.println();
  Serial.printf( "..AppKEY - %s - 0x", api.lorawan.appkey.set(node_app_key, 16) ? "OK" : "Fail" );
  api.lorawan.appkey.get(buff16, 16); for (int i = 0; i < 16; i++) { Serial.printf("%02X", buff16[i]); } Serial.println();


  Serial.printf("..Band region        - %s - Set at %d\n", api.lorawan.band.set(OTAA_BAND) ? "OK" : "Fail"              , api.lorawan.band.get());
  Serial.printf("..LoRa Class         - %s - Set at %d\n", api.lorawan.deviceClass.set(RAK_LORA_CLASS_A) ? "OK" : "Fail", api.lorawan.deviceClass.get());
  Serial.printf("..Network Join Mode  - %s - Set at %d\n", api.lorawan.njm.set(RAK_LORA_OTAA) ? "OK" : "Fail"           , api.lorawan.njm.get());

  // Serial.printf("..LoRa Join  - %s\n", api.lorawan.join() ? "OK" : "Fail");


  /** Wait for Join success */
  while (api.lorawan.njs.get() == 0) {           // While the join is not confirmed, ...
    Serial.print("Wait for LoRaWAN join...");       // ... 
    api.lorawan.join();                             // ... we make join request, 
    delay(10000);                                   // ... and wait.
  }

  Serial.printf("> ADR  - %s\n", api.lorawan.adr.set(true) ? "OK" : "Fail");
  Serial.printf("> Retry  - %s\n", api.lorawan.rety.set(1) ? "OK" : "Fail");
  Serial.printf("> Confirm Mode  - %s\n", api.lorawan.cfm.set(true) ? "OK" : "Fail");
  
  
    /** Check LoRaWan Status*/
    // Serial.printf("Duty cycle is %s\r\n", api.lorawan.dcs.get()? "ON" : "OFF");	// Check Duty Cycle status
    // Serial.printf("Packet is %s\r\n", api.lorawan.cfm.get()? "CONFIRMED" : "UNCONFIRMED");	// Check Confirm status
    // uint8_t assigned_dev_addr[4] = { 0 };
    // api.lorawan.daddr.get(assigned_dev_addr, 4);
    // Serial.printf("Device Address is %02X%02X%02X%02X\r\n", assigned_dev_addr[0], assigned_dev_addr[1], assigned_dev_addr[2], assigned_dev_addr[3]);	// Check Device Address
    // Serial.printf("Uplink period is %ums\r\n", OTAA_PERIOD);
    // Serial.println("");

    delay(2500);

    api.lorawan.registerRecvCallback(recvCallback);
    api.lorawan.registerJoinCallback(joinCallback);
    api.lorawan.registerSendCallback(sendCallback);
    delay(2500);
}

void uplink_routine()
{
    /** Payload of Uplink */
    uint8_t data_len = 0;
    collected_data[data_len++] = (uint8_t) 't';
    collected_data[data_len++] = (uint8_t) 'e';
    collected_data[data_len++] = (uint8_t) 's';
    collected_data[data_len++] = (uint8_t) 't';
  
    Serial.println("Data Packet:");
    for (int i = 0; i < data_len; i++) {
        Serial.printf("0x%02X ", collected_data[i]);
    }
    Serial.println("");
  
    /** Send the data package */
    if (api.lorawan.send(data_len, (uint8_t *) & collected_data, 2, true, 1)) {
        Serial.println("Sending is requested");
    } else {
        Serial.println("Sending failed");
    }
}

void loop()
{
    static uint64_t last = 0;
    static uint64_t elapsed;
  
    if ((elapsed = millis() - last) > OTAA_PERIOD) {
        uplink_routine();
  
        last = millis();
    }
    //Serial.printf("Try sleep %ums..", OTAA_PERIOD);
    api.system.sleep.all(OTAA_PERIOD);
    //Serial.println("Wakeup..");
}
