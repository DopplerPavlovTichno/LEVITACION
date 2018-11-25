/*
  Fading

  This example shows how to use the analogWrite() function.

  The circuit:
  - PWM output from digital pin 11 to analog pin 3.

  created 1 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe
  modificado de nuevo 24/11/2018

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

int ledPin = 11;    // LED connected to digital pin 11
int analogPin = 3;     // output connected to analog pin 3
                       // 
int val = 0;           // variable to store the value read
int medio=0;           // variable usada para promediar la salida pwm
void setup() {
  Serial.begin(9600);              //  setup serial
}

void loop() {
  // fade in from min to max in increments of 1 points:
 for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 1) {
// fadeValue=155;
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
     val = analogRead(analogPin);     // read the input pin
     medio=(medio+val)*0.5;           // la salida tiene un promedio solo para ver como actua. La salida real PWM varia en frecuencia
  Serial.println(medio);// debug value

   }

  // fade out from max to min in increments of 1 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 1) {
    // sets the value (range from 0 to 255):
  //fadeValue=155;
    analogWrite(ledPin, fadeValue);
       val = analogRead(analogPin);     // read the input pin
       medio=(medio+val)*0.5;           //para ver el efecto de un promedio. La salida real PWM es sin este promedio
    Serial.println(medio);             // debug value
    
  }
}
