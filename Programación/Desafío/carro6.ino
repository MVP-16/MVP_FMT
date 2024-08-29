 #include <Servo.h>

//Pines del sensor de color 
int S0 = 14;
int S1 = 15;
int S2 = 16;
int S3 = 17;
int Out = 18;

//Condiguracion para colores 

//lectura de numeros color rojo 
int Rojo () {
  digitalWrite(S2, LOW);
  digitalWrite(S2, LOW);
  int rojo = pulseIn(Out, LOW); 
  return rojo; 
}

//lectura de numeros color azul 
int Azul () {
  digitalWrite(S2, LOW);
  digitalWrite(S2, HIGH);
  int azul = pulseIn(Out, LOW); 
  return azul; 

}

//lectura de numeros color verde 
int Verde () {
  digitalWrite(S2, HIGH);
  digitalWrite(S2, HIGH);
  int verde = pulseIn(Out, LOW); 
  return verde; 

}

//pines del pueste h
int ENA = 5;
int IN1 = 7;
int IN2 = 6;
int ENB = 3;
int IN3 = 4;
int IN4 = 2; 

Servo tservo;

//Pines del sensor ultrasonico 
int  trig = 9;
int  echo = 10;
int time;
int distance;

Servo Aservo; 

void setup(){
//sensor de color 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(Out, INPUT);

   //Va trabajar al 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

//Puente H 
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

//servosonico 
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
 
  
  tservo.attach(8);
  Aservo.attach(11);
  Serial.begin(9600);

}

void loop() {
  //servosonico 
  digitalWrite(trig, HIGH);
  delayMicroseconds(25);
  digitalWrite(trig, LOW);
  time=pulseIn(echo, HIGH);
  distance=time/58.2; 
  delay(20); 
  digitalWrite(trig, LOW);
  Serial.println(time);
  delay(200);
  //Sensor de color 
 int R = Rojo ();
 delay(50);
 int A = Azul (); 
 delay(50);
 int V = Verde (); 
 delay(50);

Serial.print(" Rojo "+ String(R));
Serial.print(" Azul "+ String(A));
Serial.println(" Verde  "+ String(V));

  //Avanzar 
  if(distance <= 100 ) {
  analogWrite(ENA,103);
  analogWrite(ENB,100);
  tservo.write(95);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  }
  //girara a la derecha 
  if(distance <= 99) {
  analogWrite(ENA,88);
  analogWrite(ENB,85);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Aservo.write(0);
  }
  
 
  if( distance <= 80) {
   tservo.write(65);
   Aservo.write(85);
   analogWrite(ENA,78);
   analogWrite(ENB,75);   
   digitalWrite(IN1, HIGH);
   digitalWrite(IN2, LOW);
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);
   
  }
  
  if ( R > A && A < V && R < 174 && A >= 54) {

  tservo.write(65);
  analogWrite(ENA,50);
  analogWrite(ENB, 50);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.print(" blanco ");
  
  }

}
