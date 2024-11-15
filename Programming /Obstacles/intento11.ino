#include <Pixy2.h>
#include <SPI.h>
#include <Servo.h>

Pixy2 pixy;
Servo Aservo;

//pines de los sensores ultrasonicos
int Trig = 38;
int Echo = 39;
int Trig2 = 28;
int Echo2 = 27;
int Trig3 = 34;
int Echo3 = 35;
int Trig4 = 23;
int Echo4 = 24;
int Trig5 = 18;
int Echo5 = 19;

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

// Pines del puente H
int ENA = 5;
int IN1 = 7;
int IN2 = 6;
int ENB = 3;
int IN4 = 2;
int IN3 = 4;

// Variables globales para las posiciones Y1 y Y2
int Y1 = -1;
int Y2 = -1;

void obtenerY1() {
  pixy.ccc.getBlocks();
  for (int i = 0; i < pixy.ccc.numBlocks; i++) {
    if (pixy.ccc.blocks[i].m_signature == 1) {  // Bloque rojo
      Y1 = pixy.ccc.blocks[i].m_y;              // Posición Y del bloque rojo
      Serial.print(i);
      Serial.print(" Y1: ");
      Serial.println(Y1);
      return;  // Salir después de encontrar el primer bloque rojo
    }
  }
  Y1 = -1;  // Si no se encontró el bloque rojo
}

void obtenerY2() {
  pixy.ccc.getBlocks();
  for (int i = 0; i < pixy.ccc.numBlocks; i++) {
    if (pixy.ccc.blocks[i].m_signature == 2) {  // Bloque verde
      Y2 = pixy.ccc.blocks[i].m_y;              // Posición Y del bloque verde
      Serial.print(i);
      Serial.print(" Y2: ");
      Serial.println(Y2);
      return;  // Salir después de encontrar el primer bloque verde
    }
  }
  Y2 = -1;  // Si no se encontró el bloque verde
}

bool detectarBloqueRojo() {
  pixy.ccc.getBlocks();
  for (int i = 0; i < pixy.ccc.numBlocks; i++) {
    if (pixy.ccc.blocks[i].m_signature == 1) {  // Bloque rojo
      Serial.println("bloque_rojo");
      return true;
    }
  }
  return false;
}

bool detectarBloqueVerde() {
  pixy.ccc.getBlocks();
  for (int i = 0; i < pixy.ccc.numBlocks; i++) {
    if (pixy.ccc.blocks[i].m_signature == 2) {  // Bloque verde
      Serial.println("bloque_verde");
      return true;
    }
  }
  return false;
}

void moverMotores() {
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reducirVelocidad() {
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reducirVelocidadMas() {
  analogWrite(ENA, 80);
  analogWrite(ENB, 80);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void setup() {
  Serial.begin(115200);
  pixy.init();

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //sensor ultrasonico
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig3, OUTPUT);
  pinMode(Echo3, INPUT);
  pinMode(Trig4, OUTPUT);
  pinMode(Echo4, INPUT);
  pinMode(Trig5, OUTPUT);
  pinMode(Echo5, INPUT);

  Aservo.attach(8);
}

void loop() {

  long distancia1, distancia2, distancia3, distancia4, distancia5;
  long duracion1, duracion2, duracion3, duracion4, duracion5;
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
  //cuarto ultrasonico
  distancia4 = leerDistancia(Trig4, Echo4);
  Serial.print("sensor 4: ");
  Serial.print(distancia4);
  Serial.println(" cm");
  //quinto ultrasonico
  distancia5 = leerDistancia(Trig5, Echo5);
  Serial.print("sensor 5: ");
  Serial.print(distancia5);
  Serial.println(" cm");

  obtenerY1();  // Actualiza la posición Y1
  obtenerY2();  // Actualiza la posición Y2
  bool hayBloqueRojo = detectarBloqueRojo();
  bool hayBloqueVerde = detectarBloqueVerde();

  if (!hayBloqueRojo && !hayBloqueVerde) {
    if (distancia1 > 90) {
      moverMotores();
      Aservo.write(135);
      if (distancia2 < 35) {
        reducirVelocidad();
        Aservo.write(155);
      } else if (distancia3 < 35) {
        reducirVelocidad();
        Aservo.write(110);
      } else {
        moverMotores();
        Aservo.write(135);
      }
    } else if (distancia1 < 80) {
      reducirVelocidad();
      if (distancia4 > distancia5) {
        Aservo.write(110);
      } else if (distancia4 < distancia5) {
        Aservo.write(160);
      }
    }
  } else if (hayBloqueRojo && !hayBloqueVerde) {
    if(distancia1 )
    reducirVelocidadMas();
    Aservo.write(155);
    if (distancia3 < 20) {
      Aservo.write(100);
    } else {
      reducirVelocidadMas();
      Aservo.write(155);
    }
  } else if (!hayBloqueRojo && hayBloqueVerde) {
    reducirVelocidadMas();
    Aservo.write(115);

    if (distancia2 < 50) {
      Aservo.write(165);
    } else if (distancia3 < 35) {
      Aservo.write(110);
    } else {
      reducirVelocidadMas();
      Aservo.write(115);
    }
  } else if (hayBloqueRojo && hayBloqueVerde) {
    reducirVelocidadMas();
    if (Y1 > Y2) {
      Aservo.write(150);
    } else if (Y2 > Y1) {
      Aservo.write(110);
    }
  } else {
    moverMotores();
    Aservo.write(135);
  }
  delay(200);
}
