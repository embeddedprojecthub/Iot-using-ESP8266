/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "BBFF-JuL6mPUuy5EcUzoZIPFGPK9CBgzGam" // Your Ubidots TOKEN
#define WIFINAME "Ubidots" //Your SSID
#define WIFIPASS "123456789" // Your Wifi Pass

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
   Serial.println();
   
  if(payload[0] == '0')
  {
    //turn off the LED
    digitalWrite(D0,LOW);  
  }
  else
  {
    //Turn on the LED
    digitalWrite(D0,HIGH);
  }
 
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  //setup LED pin
  pinMode(D0,OUTPUT);
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.ubidotsSetBroker("business.api.ubidots.com");
  client.begin(callback);
  client.ubidotsSubscribe("esp8266","led"); //Insert the dataSource and Variable's Labels
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("esp8266","led"); //Insert the dataSource and Variable's Labels
      }
  client.loop();
  }
