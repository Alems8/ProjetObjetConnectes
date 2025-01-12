#include <Wire.h>
#include "Seeed_MCP9808.h"
#include <SoftwareSerial.h>
#include "Ultrasonic.h"
#ifdef USE_TINYUSB
#include <Adafruit_TinyUSB.h>
#endif

MCP9808 tempSensor;
Ultrasonic ultrasonic(0);
SoftwareSerial bluetoothSerial(2,3);

// Pins and thresholds
const int gasSensorPin = A0;
const int gazLed = A1;
const int kitchenLed = A2;
const int tempLed = A3;
const int ledExternal = 1;
const int redPinLiving = 4;
const int greenPinLiving = 5;
const int bluePinLiving = 6;
const int redPinKitchen = 7;
const int greenPinKitchen = 8;
const int bluePinKitchen = 9;
const int buzzerPin = 10;
const int redPinEntrance = 13;
const int greenPinEntrance = 12;
const int bluePinEntrance = 11;
int tempThreshold = 25; 
const int gasThreshold = 500;

void setup() {
  Serial.begin(9600);

  pinMode(gazLed, OUTPUT);
  pinMode(kitchenLed, OUTPUT);
  pinMode(tempLed, OUTPUT);
  pinMode(ledExternal, OUTPUT);

  pinMode(redPinLiving, OUTPUT);
  pinMode(greenPinLiving, OUTPUT);
  pinMode(bluePinLiving, OUTPUT);

  pinMode(redPinKitchen, OUTPUT);
  pinMode(greenPinKitchen, OUTPUT);
  pinMode(bluePinKitchen, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(redPinEntrance, OUTPUT);
  pinMode(greenPinEntrance, OUTPUT);
  pinMode(bluePinEntrance, OUTPUT);

  if (tempSensor.init()) {
    Serial.println("Could not find a valid MCP9808 sensor!");
    while (1);
  }

  Serial.println("Arduino ready. Monitoring sensors...");
}

void loop() {
  gasCheck();
  readTemp();
  checkEntrance();

  //Manual Command Handling
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("SET_TEMP ")) {
      int newThreshold = command.substring(9).toInt();
      tempThreshold = newThreshold;
      Serial.println("Temperature threshold set to " + String(tempThreshold) + " C.");
    } 
    else if (command.startsWith("SET_LED_KITCHEN")) {
      setKitchenLED(command);
    }
    else if(command.startsWith("SET_LED_LIVING")) {
      setLivingLED(command);
    }
    else if(command.startsWith("SET_LED_ENTRANCE")) {
      setEntranceLED(command);
    }
    else {
      Serial.println("Unknown command: " + command);
    }
  }

  delay(500);
}

void gasCheck() {
  int gasValue = analogRead(gasSensorPin);
  Serial.println("Gas value: " + String(gasValue));

  if (gasValue > gasThreshold) {
    analogWrite(gazLed, 255);
    tone(buzzerPin, 1000);
    Serial.println("Smoke detected!");
  } else {
    analogWrite(gazLed, 0);
    noTone(buzzerPin);
  }
}

void readTemp() {
  float temp = 0;
  tempSensor.get_temp(&temp);
  Serial.println("Temperature: " + String(temp) + " C");

  if (temp < tempThreshold) {
    analogWrite(tempLed, 255);
    Serial.println("Low temperature detected!");
  } else {
    analogWrite(tempLed, 0);
  }
}

void checkEntrance(){
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    if (RangeInCentimeters<=15){
      digitalWrite(ledExternal, HIGH);
    }
    else{
      digitalWrite(ledExternal,LOW);
    }
    Serial.print(RangeInCentimeters);//0~400cm
    Serial.println(" cm");
}

void setKitchenLED(String command) {
  // Extract the RGB part of the command
  int startIndex = command.indexOf(' ') + 1;
  String rgbValues = command.substring(startIndex);

  // Split the RGB values
  int commaIndex1 = rgbValues.indexOf(',');
  int commaIndex2 = rgbValues.indexOf(',', commaIndex1 + 1);

  int red = rgbValues.substring(0, commaIndex1).toInt();
  int green = rgbValues.substring(commaIndex1 + 1, commaIndex2).toInt();
  int blue = rgbValues.substring(commaIndex2 + 1).toInt();

  // Set the LED colors
  analogWrite(redPinKitchen, red);
  analogWrite(greenPinKitchen, green);
  analogWrite(bluePinKitchen, blue);

  Serial.println("Kitchen LED set to R:" + String(red) + " G:" + String(green) + " B:" + String(blue));
}

void setLivingLED(String command) {
  // Extract the RGB part of the command
  int startIndex = command.indexOf(' ') + 1;
  String rgbValues = command.substring(startIndex);

  // Split the RGB values
  int commaIndex1 = rgbValues.indexOf(',');
  int commaIndex2 = rgbValues.indexOf(',', commaIndex1 + 1);

  int red = rgbValues.substring(0, commaIndex1).toInt();
  int green = rgbValues.substring(commaIndex1 + 1, commaIndex2).toInt();
  int blue = rgbValues.substring(commaIndex2 + 1).toInt();

  // Set the LED colors
  analogWrite(redPinLiving, red);
  analogWrite(greenPinLiving, green);
  analogWrite(bluePinLiving, blue);

  Serial.println("Living LED set to R:" + String(red) + " G:" + String(green) + " B:" + String(blue));
}

void setEntranceLED(String command) {
  // Extract the RGB part of the command
  int startIndex = command.indexOf(' ') + 1;
  String rgbValues = command.substring(startIndex);

  // Split the RGB values
  int commaIndex1 = rgbValues.indexOf(',');
  int commaIndex2 = rgbValues.indexOf(',', commaIndex1 + 1);

  int red = rgbValues.substring(0, commaIndex1).toInt();
  int green = rgbValues.substring(commaIndex1 + 1, commaIndex2).toInt();
  int blue = rgbValues.substring(commaIndex2 + 1).toInt();

  // Set the LED colors
  analogWrite(redPinEntrance, red);
  analogWrite(greenPinEntrance, green);
  analogWrite(bluePinEntrance, blue);

  Serial.println("Entrance LED set to R:" + String(red) + " G:" + String(green) + " B:" + String(blue));
}
