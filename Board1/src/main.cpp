#include <Arduino.h>
#include <Wire.h>

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
void sendrfid(){
  Serial.print("sender");
  Wire.beginTransmission(1); // transmit to device #4
  Wire.write(1);
  Wire.write("E2 46 CF 1B");
  Wire.endTransmission(); // stop transmitting
}

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop()
{
  Wire.onReceive(receiveEvent);
  sendrfid();
  

  delay(500);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

