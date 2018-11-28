/* 
 Ejemplo de control de motor DC usando modulo L298
 http://electronilab.co/tienda/driver-dual-para-motores-full-bridge-l298n/
 
 Creado 16/05/14
 por Andres Cruz
 ELECTRONILAB.CO
 */

int IN1 = 5;    // Input3 conectada al pin 5
int IN2 = 4;    // Input4 conectada al pin 4 
int ENA = 3;    // ENB conectada al pin 3 de Arduino
void setup()
{
 pinMode (ENA, OUTPUT); 
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
}
void loop()
{
  //Preparamos la salida para que el motor gire en un sentido
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  // Aplicamos PWM al pin ENB, haciendo girar el motor, cada 2 seg aumenta la velocidad
//  analogWrite(ENB,55);
//  delay(2000);
//  analogWrite(ENA,105);
//  delay(2000);
  analogWrite(ENA,255);
  //  delay(2000);
  // Apagamos el motor y esperamos 5 seg
//  analogWrite(ENA,0);
//  delay(5000);
}
