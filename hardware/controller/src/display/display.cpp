#include "display.hpp"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){
  Serial.begin(9600);

  // Inicia la pantalla LCD
  lcd.begin(16, 2);  //16 columnas y 2 filas
  lcd.print("Esperando...");

  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    //Leer el carácter recibido 
    char receivedChar = Serial.read();

    lcd.clear();
    lcd.print(receivedChar);  //mostrar caracter

    delay(500);
  }
}

