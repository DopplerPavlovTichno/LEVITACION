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
const int trigPin = 9;
const int echoPin = 10;
const int controlPin = 1;

void setup() {
  // initialize the serial port:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  kp = 1.0;
  ki = 0.0;
  kd = 0.0;
  setpoint = 300;
  last_error = 0;
  dt = 1000;
}

void loop() {
  // Clears the trigPin
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
  calculatePID();
  delay(dt);
}

void calculatePID() {
  error = distance - setpoint;
  p_term = kp*error;
  i_term = i_term + ki*error*dt/1000;
  d_term = kd*(error-last_error)*1000/dt;;
  last_error = error;
  PIDValue = p_term + i_term + d_term;
 // Serial.println(PIDValue);
 //analogWrite(controlPin, PIDValue);
}
