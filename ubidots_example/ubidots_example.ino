#include "UbidotsMicroESP8266.h"
#define TOKEN  "A1E-dHwuMBAsNR9fTFYQDmOHAgvFF42nUe"  // Put here your Ubidots TOKEN
#define WIFISSID "1503523"
#define PASSWORD "D2E7D32DBC883"

Ubidots client(TOKEN);
unsigned long lastMillis = 0;

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){

    if (millis() - lastMillis > 10000) {
      
            lastMillis = millis();
            client.add("lastMillis", lastMillis);
            client.sendAll(true);
            
            }
   
}
