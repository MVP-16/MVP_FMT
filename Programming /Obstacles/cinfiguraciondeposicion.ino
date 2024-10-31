#include <Pixy2.h>
#include <SPI.h>

Pixy2 pixy;

void setup() {
  Serial.begin(115200);
  pixy.init();
}

void loop() {
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) { // Si hay bloques detectados
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      int xPos = pixy.ccc.blocks[i].m_x; // Posición X del bloque
      int yPos = pixy.ccc.blocks[i].m_y; // Posición Y del bloque
      Serial.print("Bloque ");
      Serial.print(i);
      Serial.print(" - X: ");
      Serial.print(xPos);
      Serial.print(" Y: ");
      Serial.println(yPos);
    }
  }
  delay(500); // Espera para evitar mensajes demasiado rápidos
}
