/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "BBFF-JuL6mPUuy5EcUzoZIPFGPK9CBgzGam" //Your Ubidots TOKEN
#define WIFINAME "Ubidots" //Your SSID
#define WIFIPASS "123456789" // Your Wifi Pass

Ubidots client(TOKEN);

  float parameter1 = 10.2;
  float parameter2 = 1.1;
  int   parameter3 = 5;
  
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
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();       
      }

  
  // Publish values to 2 different data sources
  client.add("stuff", parameter1); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("Device1");
  client.add("stuff", parameter2);
  client.add("more-stuff", parameter3);
  client.ubidotsPublish("Device2");
  client.loop();

  parameter1 += 0.5;
  parameter2 += 0.2;
  parameter3 += 1;
  delay(1000);
  }
