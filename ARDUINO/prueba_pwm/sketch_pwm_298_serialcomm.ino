int IN1 = 8;
int IN2 = 7;
int ENA = 9;
int potencia;

void setup() 
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);  
  Serial.begin(9600);
}

void loop() 
{
    int i;
    char val[3];
    while(Serial.available()>0) {
          val[i]=Serial.read();
          i++;
    }
       potencia= atoi(&val[0]);
       Serial.println();
       Serial.print(potencia);
       Serial.println();
       delay(1);
       if(potencia>255){
          potencia=255;
       }
          digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW);
          analogWrite(ENA,potencia);
}
