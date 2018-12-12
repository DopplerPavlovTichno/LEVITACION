// defines variables
double kp;
double ki;
double kd;
double p_term;
double i_term;
double d_term;
double PIDValue;
double setpoint;
int dt;
double error;
double last_error;
long duration;
int distance;
const int trigPin = 12;
const int echoPin = 13;
const int controlPin = 1;
unsigned long delay1 = 100;
unsigned long delay2 = 100;
unsigned long tiempo_cada_pwm = 30000 ; // 30 segundos cada nivel de PWM, para estudiar el ciclo de histéresis en estacionario en cada nivel
unsigned long t1 ;
unsigned long t2 ;
unsigned long t0 ;
int n0 ;
int n ;
double pidresult ;
double distancia_maxima ;
double distancia_minima ;
int valorpwm = 140 ;
const int pwm_pin = 9;
int para_actuador ;
int contador = 0 ;
int cont2 = 0 ;

void setup() {
  // initialize the serial port:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  kp = 1;
  ki = 0.01;
  kd = 0.1;
  setpoint = 250 ;
  last_error = 0 ;
  dt = 100;
  t0 = t1 = t2 = millis() ;
  distancia_maxima = 400;
  distancia_minima = 4;
  n0 = int(tiempo_cada_pwm / delay1) ;
  n = n0 ;
}

void loop() {
  if(millis() - t1 > delay1) { //this will be executed every delay1 ms
//    para_actuador = input_actuador(pidresult) ; // esta es con control
    contador = contador + 1 ; // esto es para alimentar con una escalera primero ascendente y luego descendente, para ver el ciclo de histéresis. No tiene control.
    if(contador == n) {
      if(cont2 < 10){
        valorpwm = valorpwm + 5 ; // si tuviera control, valorpwm saldría directamente de la función para_actuador
        cont2 = cont2 + 1 ;
      } else if(cont2 < 20){
        valorpwm = valorpwm - 5 ;
        cont2 = cont2 + 1 ;
      }
      n = n + n0 ;
    }
    analogWrite(pwm_pin, valorpwm); // en el caso con control aca viene analogWrite(pwm_pin, para_actuador); 
    Serial.print("Input actuador = ");
    Serial.print(valorpwm); // en el caso con control es Serial.print(para_actuador) ;
    Serial.println() ;
    t1 = millis();
  }
  if(millis() - t2 > delay2) { //this will be executed every delay1 ms
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration*0.34/2;
    Serial.print("Distancia = ");
    Serial.print(distance);
    Serial.println();
    pidresult = calculatePID(distance, setpoint, kp, ki, kd);
    t2 = millis() ;
    //delay(dt);
  }
}

double calculatePID(double distance, double setpoint, double kp, double ki, double kd) {
  double PIDValue ;
  error = distance - setpoint;
  p_term = kp*error;
  i_term = i_term + ki*error*dt/1000;
  d_term = kd*(error-last_error)*1000/dt;;
  last_error = error;
  PIDValue = p_term + i_term + d_term;
  //Serial.println(PIDValue);
  return PIDValue ;
 //analogWrite(controlPin, PIDValue);
}

int calibracion(double distance, double distancia_maxima, double distancia_minima) {
  int para_actuador ;
  int minpwm = 0 ;
  int maxpwm = 255 ;
  if (distance < distancia_minima) {
    para_actuador = minpwm ;
  } else if (distance > distancia_maxima) {
    para_actuador = maxpwm ;
  } else {
    para_actuador = int(minpwm + (maxpwm - minpwm) * PIDValue / (distancia_maxima - distancia_minima)) ; // es perfectible
  }
  Serial.println(para_actuador) ;
  return para_actuador ;
}

int input_actuador(double PIDv) {
  int para_actuador ;
  if (PIDv < 0) {
    para_actuador = 0 ;
  } else if (PIDv > 255) {
    para_actuador = 255;
  } else {
    para_actuador = PIDv ;
  }
  return para_actuador ;
}
