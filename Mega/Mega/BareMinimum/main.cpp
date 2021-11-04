/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>

Servo myservo;

int pos = 0;
int REDled = 7;
int GREENled = 6;
String rfid = "E2 46 CF 1B";
void Menu(int howMany);
void setup()
{
	//myservo.attach(8);
	//pinMode(REDled, OUTPUT);
	//pinMode(GREENled, OUTPUT);
	Wire.begin(1); // join i2c bus (address optional for master)
	Wire.onReceive(Menu);
	Serial.begin(9600);
}

void Menu(int howMany){
	String test = "";
	while(1 < Wire.available()) // loop through all but the last
	{
		char c = Wire.read();
		test += c;
	}
	int x = Wire.read();
	switch (x)
	{
		case 1:
		if (test == rfid){
			Serial.println("Access granted");
			//digitalWrite(GREENled, HIGH);
			//for (pos = 0; pos <= 180; pos += 1) {
			//myservo.write(pos);
			//delay(20);
			//}
			//digitalWrite(GREENled, LOW);
			//delay(1000);							//Waits for 1sec before closing again
			//for (pos = 180; pos >= 0; pos -= 1) {
			//myservo.write(pos);
			//delay(15);
			//}
		}
		else{
			Serial.println("Access denied");
			//digitalWrite(REDled, HIGH);
			//delay(1000);
			//digitalWrite(REDled, LOW);
		}
		break;
		case 2:
		
		break;
		case 3:
		
		break;
		case 4:
		
		break;
		default:
		/* Your code here */
		break;
	}
}

void loop()
{
	Wire.onReceive(Menu);
	delay(500);
}
