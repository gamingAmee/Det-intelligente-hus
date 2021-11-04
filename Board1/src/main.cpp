#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <MQTT.h>

//WIFI Access Point
const char ssid[] = "SibirienAP";
const char pass[] = "Siberia51244";

WiFiClient net;
MQTTClient client;
long lastPublishMillis = 0;
void connect() 
{
 client.begin("mqtt3.thingspeak.com", net);
  Serial.print("\nconnecting...");
  while (!client.connect("BA0hJhsyEQstHwUvDRERAzM", "BA0hJhsyEQstHwUvDRERAzM", "TLhieQNcuDDkPiM3eSNIQcEi")) {
    
    Serial.print(".");
    if ( abs(millis() - lastPublishMillis) > 1000) {
     
    lastPublishMillis = millis();
  }
  }
  Serial.println("\nconnected!");
  
  
}


void receiveEvent(int howMany)
{
  int x;
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  //RECEIVE CHOICE
   switch (x) {
  case 1:
     Serial.print("from 1");
    break;
  case 2:
    Serial.print("from 2");
    break;
  case 3:
    Serial.print("from 3" );
    break;
  case 4:
    Serial.print("from 4" );
    break;
  default:
    // if nothing else matches, do the default
    // default is optional
    break;
  }
}
void sendrfid(String topic, String payload)
{
  
  Serial.print("sender");
  Wire.beginTransmission(1); // transmit to device #1
  Wire.write(payload.c_str());
  Wire.write(1);
  
  Wire.endTransmission(); // stop transmitting
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  sendrfid(topic, payload);
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}



void setup()
{
  Wire.begin();               
  //Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  while (!Serial)
    ;
   
    while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  
  
  client.onMessage(messageReceived);

  connect();
}

void loop()
{
  //Wire.onReceive(receiveEvent);
  client.loop();
  

  if (!client.connected()) {
    connect();
    client.subscribe("channels/1559675/subscribe");
  }
  client.onMessage(messageReceived);
  
  if ( abs(millis() - lastPublishMillis) > 10000) {
     
    lastPublishMillis = millis();
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

