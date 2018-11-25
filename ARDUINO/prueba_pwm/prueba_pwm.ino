/*
  Fading

  This example shows how to fade an LED using the analogWrite() function.

  The circuit:
  - LED attached from digital pin 9 to ground.

  created 1 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

int ledPin = 11;    // LED connected to digital pin 11
int analogPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read
int medio=0;
void setup() {
  Serial.begin(9600);              //  setup serial
}

void loop() {
  // fade in from min to max in increments of 5 points:
 for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 1) {
// fadeValue=155;
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
     val = analogRead(analogPin);     // read the input pin
     medio=(medio+val)*0.5;
  Serial.println(medio);// debug value
     //medio=val;
   // wait for 150 milliseconds to see the dimming effect
    //delay(150);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 1) {
    // sets the value (range from 0 to 255):
  //fadeValue=155;
    analogWrite(ledPin, fadeValue);
       val = analogRead(analogPin);     // read the input pin
       medio=(medio+val)*0.5;
    Serial.println(medio);             // debug value
       //medio=val;
   // wait for 150 milliseconds to see the dimming effect
    //delay(150);
  }
}
