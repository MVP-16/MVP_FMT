#include <Servo.h>
#include <Pixy2.h>
#include <stdio.h>

Pixy2 pixy;

Servo Aservo;

//pines de los sensores ultrasonicos
int Trig = 25;
int Echo = 26;
int Trig2 = 28;
int Echo2 = 27;
int Trig3 = 34;
int Echo3 = 35;

//configuracion de los sensores ultrasonicos
int leerDistancia(int Trig, int Echo) {
  long duracion;
  long distancia;
  //lanza el pulso
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  //recibe el pulso
  duracion = pulseIn(Echo, HIGH);
  //mide en tiempo y centimetros exactos en que estan los objetos
  duracion = duracion / 2;
  //mide el tiempo que tarda en ir y venir el pulso de la medicion
  distancia = duracion / 29;
  //regresa la informacion para que se pueda utilizar en otra parte del codigo
  return distancia;
}

//pines del puente H
int ENA = 5;
int IN1 = 7;
int IN2 = 6;
int ENB = 3;
int IN4 = 2;
int IN3 = 4;

int moverMotores() {
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");

  Aservo.attach(8);
  // we must initialize the pixy object
  pixy.init();
  // Getting the RGB pixel values requires the 'video' program
  pixy.changeProg("video");

  Serial.begin(9600);

  //sensor ultrasonico
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig3, OUTPUT);
  pinMode(Echo3, INPUT);

  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{ 
  uint8_t r, g, b; 
  
  // get RGB value at center of frame
  if (pixy.video.getRGB(pixy.frameWidth/2, pixy.frameHeight/2, &r, &g, &b)==0)
  {
    Serial.print("red:");
    Serial.print(r);
    Serial.print(" green:");
    Serial.print(g);
    Serial.print(" blue:");
    Serial.println(b);
    delay(200);
  }

  long distancia1, distancia2, distancia3;
  long duracion1, duracion2, duracion3;
  //primer ultrasonico
  distancia1 = leerDistancia(Trig, Echo);
  Serial.print("sensor 1: ");
  Serial.print(distancia1);
  Serial.println(" cm");
  //segundo ultrasonico
  distancia2 = leerDistancia(Trig2, Echo2);
  Serial.print("sensor 2: ");
  Serial.print(distancia2);
  Serial.println(" cm");
  //tercer ultrasonico
  distancia3 = leerDistancia(Trig3, Echo3);
  Serial.print("sensor 3: ");
  Serial.print(distancia3);
  Serial.println(" cm");

  if( r = 255 & g < 115 & b < 62){
    Aservo.write(160);
  }
  else if(g = 255 & r < 85 & b < 109){
    Aservo.write(90);
  }
  else{
    Aservo.write(120);
  }

  
  if (distancia2 < 30 ) {
    moverMotores();
    Aservo.write(155);
  } else if (distancia3 < 30 ) {
    moverMotores();
    Aservo.write(115);
    }
    else if(distancia1 < 60 ){
    moverMotores();
    Aservo.write(110);
    }
    else {
      moverMotores();
      Aservo.write(135);
    }

}

