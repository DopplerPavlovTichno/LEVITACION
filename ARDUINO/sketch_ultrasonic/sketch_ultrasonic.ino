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
unsigned long t1 ;
unsigned long t2 ;
double pidresult ;
int valor ;
const int led = 9;

void setup() {
  // initialize the serial port:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  kp = 0.1;
  ki = 0.01;
  kd = 0.1;
  setpoint = 250 ;
  last_error = 0 ;
  dt = 1000;
  t1 = t2 = millis() ;
}

void loop() {
  if(millis() - t1 > delay1) { //this will be executed every delay1 ms
    valor = 200  ;
    analogWrite(led,min(pidresult,255));
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
    Serial.println(distance);
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
