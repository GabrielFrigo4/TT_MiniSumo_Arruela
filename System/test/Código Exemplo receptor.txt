#include <Arduino.h>

#define SENSOR 5

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(SENSOR, INPUT_PULLUP); // importante
    Serial.println("Teste GPIO5");
}

void loop() {
    int valor = digitalRead(SENSOR);

    Serial.print("Valor: ");
    Serial.println(valor);

    delay(200);
}