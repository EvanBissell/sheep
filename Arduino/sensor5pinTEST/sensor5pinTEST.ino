#define ECHOPIN 12
#define TRIGPIN 13
//#define ECHOPIN1 12
//#define TRIGPIN1 13
//#define ECHOPIN2 2
//#define TRIGPIN2 3

void setup(){
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
 // pinMode(ECHOPIN1, INPUT);
 // pinMode(TRIGPIN1, OUTPUT);
 // pinMode(ECHOPIN2, INPUT);
 // pinMode(TRIGPIN2, OUTPUT);
}
void loop(){
  digitalWrite(TRIGPIN, LOW);
 // digitalWrite(TRIGPIN1, LOW);
 // digitalWrite(TRIGPIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
//  digitalWrite(TRIGPIN1, HIGH);
 // digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
//  digitalWrite(TRIGPIN1, LOW);
//  digitalWrite(TRIGPIN2, LOW);


  float distance = pulseIn(ECHOPIN, HIGH);
 // float distance1 = pulseIn(ECHOPIN1, HIGH);
 // float distance2 = pulseIn(ECHOPIN2, HIGH);
  distance= distance/58;
  Serial.print(distance);
 // Serial.print("------");
 // Serial.print(distance1);
 // Serial.print("------");
 // Serial.print(distance2);
 // Serial.print("------");
  Serial.println(" cm");
  delay(200);
}

