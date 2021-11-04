#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFiNINA.h>
#include <MQTT.h>
#include <arduino_secrets.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

#define RST_PIN   6    // Configurable, see typical pin layout above
#define SS_PIN    7   // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);

WiFiClient net;
MQTTClient client;

void connect(){
  client.begin("mqtt3.thingspeak.com", net);
  Serial.print("\nconnecting...");
  while (!client.connect("ARs2GAgDEgAVNxEUNgcEJyk", "ARs2GAgDEgAVNxEUNgcEJyk", "JrxUN1E6LcguUgqHwBPf0EiW")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload); 
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
    ;
    SPI.begin(); 
    mfrc522.PCD_Init();
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

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();

  if (!client.connected()) {
    connect();
  }
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
		delay(50);
		return;
	}
  String content= "";
	for (byte i = 0; i < mfrc522.uid.size; i++){
		content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
		content.concat(String(mfrc522.uid.uidByte[i], HEX));
	}
	content.toUpperCase();
  String publishText = "field1=";
  publishText += content;
  client.publish("channels/1559675/publish", publishText);
  delay(60000);
}
