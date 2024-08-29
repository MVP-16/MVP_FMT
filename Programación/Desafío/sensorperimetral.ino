int  S02 = 22; 
int  S12 = 23;
int  S22 = 24;
int  S32 = 25; 
int  out2 = 26;

int Rojo () {
  digitalWrite(S22, LOW);
  digitalWrite(S32, LOW);
  int rojo = pulseIn(out2, LOW); 
  return rojo; 
}

//lectura de numeros color azul 
int Azul () {
  digitalWrite(S22, LOW);
  digitalWrite(S32, HIGH);
  int azul = pulseIn(out2, LOW); 
  return azul; 

}

//lectura de numeros color verde 
int Verde () {
  digitalWrite(S22, HIGH);
  digitalWrite(S32, HIGH);
  int verde = pulseIn(out2, LOW); 
  return verde; 

}

void setup(){
//sensor de color 
  pinMode(S02, OUTPUT);
  pinMode(S12, OUTPUT);
  pinMode(S22, OUTPUT);
  pinMode(S32, OUTPUT);
  pinMode(out2, INPUT);

   //Va trabajar al 20%
  digitalWrite(S02, HIGH);
  digitalWrite(S12, LOW);

  Serial.begin(9600);
}
void loop(){
 int R = Rojo ();
 delay(50);
 int A = Azul (); 
 delay(50);
 int V = Verde (); 
 delay(50);

Serial.print(" Rojo "+ String(R));
Serial.print(" Azul "+ String(A));
Serial.println(" Verde  "+ String(V));

}