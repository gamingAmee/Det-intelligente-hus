/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>

Servo myservo;
int ifkey = 0;
int pos = 0;

int REDled = 7;
int GREENled = 6;
String rfid = " E2 46 CF 1B";

void Menu(int howMany);
void setup()
{
	SPI.begin();
	Serial.begin(9600);
	myservo.attach(8);
	pinMode(REDled, OUTPUT);
	pinMode(GREENled, OUTPUT);
	Wire.begin(1);
	Wire.onReceive(Menu);
	
}
void turnservo(int key){
	if (key == 1)
	{
		digitalWrite(GREENled, HIGH);
		for (pos = 0; pos <= 180; pos += 1)
		{
			myservo.write(pos);
			delay(15);
		}
		
		delay(1000);
		digitalWrite(GREENled, LOW);
		for (pos = 180; pos >= 0; pos -= 1)
		{
			myservo.write(pos);
			delay(15);
		}
	}
	else
	{
		digitalWrite(REDled, HIGH);
		delay(1000);
		digitalWrite(REDled, LOW);
	}
	ifkey = 0;
}

void Menu(int howMany)
{
	String test = "";
	while(1 < Wire.available())
	{
		char c = Wire.read();
		test += c;
	}
	int x = Wire.read();
	switch (x)
	{
		case 1:
		if (test == rfid)
		{
			ifkey = 1;
		}
		else
		{
			
			ifkey = 2;
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
	
	if(ifkey == 1){
		turnservo(ifkey);
	}
	if (ifkey == 2)
	{
		turnservo(ifkey);
	}
	delay(500);
}


