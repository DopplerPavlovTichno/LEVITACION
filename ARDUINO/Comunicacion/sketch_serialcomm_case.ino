//char val[4];
int motor;
int kp;
int ki;
int kd;
void setup() {
Serial.begin(9600);
}

void loop() {
  
    int i;
    char val[4];
    while(Serial.available()>0) {
          val[i]=Serial.read();
          i++;
    }
    switch(val[0]){
      case 'p':
        kp=atoi(&val[1]);
        Serial.print("Kp= ");
        Serial.print(kp);
        Serial.println();
        break;
      case 'i':
        kd=atoi(&val[1]);
        Serial.print("Ki= ");
        Serial.print(ki);
        Serial.println();
        break;
      case 'd':
        kd=atoi(&val[1]);
        Serial.print("Kd= ");
        Serial.print(kd);
        Serial.println();
        break;
      case 'm':
        motor=atoi(&val[1]);
        Serial.print("motor= ");
        Serial.print(motor);
        Serial.println();
        break;
      default:
        break;
     }
    
    //potencia= atoi(&val[0]);
    //}
    Serial.print("Kp= ");
    Serial.print(kp);
    Serial.println();
    Serial.print("Kd= ");
    Serial.print(kd);
    Serial.println();
    delay(1000);
    
  //}
 // String val=String(Serial.read());
 //Serial.println(val);

}
