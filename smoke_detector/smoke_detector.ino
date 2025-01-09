#include <Wire.h>
#include "Seeed_MCP9808.h"

MCP9808 tempSensor;

// Pins and thresholds
const int gasSensorPin = A0;
const int ledPinKitchen = 11;
const int ledPinLiving = 12;
const int buzzerPin = 10;
int tempThreshold = 25; 
const int gasThreshold = 500;

void setup() {
  Serial.begin(9600);

  pinMode(ledPinKitchen, OUTPUT);
  pinMode(ledPinLiving, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  if (tempSensor.init()) {
    Serial.println("Could not find a valid MCP9808 sensor!");
    while (1);
  }

  Serial.println("Arduino ready. Monitoring sensors...");
}

void loop() {
  gasCheck();
  readTemp();

  //Manual Command Handling
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("SET_TEMP ")) {
      int newThreshold = command.substring(9).toInt();
      tempThreshold = newThreshold;
      Serial.println("Temperature threshold set to " + String(tempThreshold) + " C.");
    } else {
      Serial.println("Unknown command: " + command);
    }
  }

  delay(500);
}

void gasCheck() {
  int gasValue = analogRead(gasSensorPin);
  Serial.println("Gas value: " + String(gasValue));

  if (gasValue > gasThreshold) {
    digitalWrite(ledPinKitchen, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Smoke detected!");
  } else {
    digitalWrite(ledPinKitchen, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}

void readTemp() {
  float temp = 0;
  tempSensor.get_temp(&temp);
  Serial.println("Temperature: " + String(temp) + " C");

  if (temp < tempThreshold) {
    digitalWrite(ledPinLiving, HIGH);
    Serial.println("Low temperature detected!");
  } else {
    digitalWrite(ledPinLiving, LOW);
  }
}
