#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

// JSUMO
#define JSUMO_1 36
#define JSUMO_2 34
#define JSUMO_3 39

// LINHA
#define LINHA 32

// DISTANCIA
#define SDA_PIN 21
#define SCL_PIN 22

VL53L0X sensor;

void setup() {
  Serial.begin(115200);
  delay(1000);

  analogReadResolution(12);

  pinMode(LINHA, INPUT_PULLUP);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!sensor.init()) {
    Serial.println("Erro VL53L0X");
    while (1);
  }

  sensor.startContinuous();

  Serial.println("Teste sensores");
}

void loop() {

  int js1 = analogRead(JSUMO_1);
  int js2 = analogRead(JSUMO_2);
  int js3 = analogRead(JSUMO_3);

  int linha = digitalRead(LINHA);

  uint16_t distancia = sensor.readRangeContinuousMillimeters();

  Serial.print("J1: ");
  Serial.print(js1);

  Serial.print(" | J2: ");
  Serial.print(js2);

  Serial.print(" | J3: ");
  Serial.print(js3);

  Serial.print(" | LINHA: ");
  Serial.print(linha == LOW ? "DETECTADA" : "OK");

  Serial.print(" | DIST: ");
  Serial.print(distancia);
  Serial.println(" mm");

  delay(100);
}