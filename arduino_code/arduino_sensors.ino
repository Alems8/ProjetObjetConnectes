// Imports of necessary libraries

#include <Wire.h>
#include "Seeed_MCP9808.h"
#include <SoftwareSerial.h>
#include "Ultrasonic.h"
#ifdef USE_TINYUSB
#include <Adafruit_TinyUSB.h>
#endif

// Declaration of sensors
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
  // Initialization of serial monitor and bluetooth to communicate with the app
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  // Setup of leds and the buzzer as output
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

  // Verification of the correct initialization for the temperature sensor
  if (tempSensor.init()) {
    Serial.println("Could not find a valid MCP9808 sensor!");
    while (1);
  }

  Serial.println("Arduino ready. Monitoring sensors...");
}

void loop() {
  // Call of the functions to read the value from the gas and temperature sensors
  gasCheck();
  readTemp();

  // This function is rensponsible to check if someone is at the door but at the moment the sensor is not active
  //checkEntrance();

  // Manual Command Handling, mainly used during testing of the commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("SET_TEMP ")) {
      int newThreshold = command.substring(9).toInt();
      tempThreshold = newThreshold;
      Serial.println("Temperature threshold set to " + String(tempThreshold) + " C.");
    } 
    else {
      Serial.println("Unknown command: " + command);
    }
  }

  // Handling of the commands coming from the bluetooth interface.
  // 1 and 2 are used to turn on and off respectively the kitchen led. 
  // LED is used to turn on the RGB leds to the color specified after the keyword "LED"
  // T is used to set the new threshold temperature
  if(bluetoothSerial.available()){
    String command = bluetoothSerial.readStringUntil('\n');
    command.trim();
    if(command.startsWith("1")){
      
      setKitchenLED(command);
    }
    else if(command.startsWith("2")){
      
      setKitchenLED(command);
    }
    else if (command.startsWith("LED")){
      setMultiLED(command);
    }

    else if(command.startsWith("T ")){
      Serial.write(bluetoothSerial.read());
      int newThreshold = command.substring(9).toInt();
      tempThreshold = newThreshold;
      Serial.println("Temperature threshold set to " + String(tempThreshold) + " C.");
    }
  }
  
  // To avoid overchecking the sensors
  delay(500);
}

void gasCheck() {
  /*Function to read the gas value from the sensor. If the value is higher that a certain threshold
  a led is turned on and a buzzer emits a sound.
  The function already integrate the possibility to send the gas value to the mobile app once the feature will be implemented. */

  int gasValue = analogRead(gasSensorPin);
  Serial.println("Gas value: " + String(gasValue));
  bluetoothSerial.print("Gas " + String(gasValue));
  bluetoothSerial.println("");

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
  /* Function to read the temperature value from the sensor. It checks if the new value is
  lower than the threshold set, it "turns on" the radiator, which is represented by a LED.
  The function already integrate the possibility to send the gas value to the mobile app once the feature will be implemented. */
  float temp = 0;
  tempSensor.get_temp(&temp);
  Serial.println("Temperature: " + String(temp) + " C");
  bluetoothSerial.print("Temperature " + String(temp));
  bluetoothSerial.println("");
  if (temp < tempThreshold) {
    analogWrite(tempLed, 255);
    Serial.println("Low temperature detected!");
  } else {
    analogWrite(tempLed, 0);
  }
}

void checkEntrance(){
  /* Function that uses the ultrasonic sensor to measure the distance from an obstacle in front of the sensor.
  For our implementation it is meant to be placed in front of the door so that if someone approaches the door,
  ie, the distance from the sensor is lower than 15cm it will turn on a LED to provide some light to open the door.
  Momentarily not used since the sensor was not included in this version of the model. */
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

void setKitchenLED(String command){
  /* Function used to turn on/off the kitchen LED based on the command received
  If the command is a 1 the LED is turned on. The opposite otherwise. */
  int ledNumber = command.toInt();
  Serial.println("number: " + String(ledNumber));
  if(ledNumber==1){
    analogWrite(kitchenLed, 255);
  }
  else{
    analogWrite(kitchenLed, 0);
  }
}


void setMultiLED(String command) {
  /* Function to extract the RGB values from a command and set all the RGB LEDs of the house to the extracted value */
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

  analogWrite(redPinKitchen, red);
  analogWrite(greenPinKitchen, green);
  analogWrite(bluePinKitchen, blue);

  analogWrite(redPinEntrance, red);
  analogWrite(greenPinEntrance, green);
  analogWrite(bluePinEntrance, blue);

  Serial.println("LED set to R:" + String(red) + " G:" + String(green) + " B:" + String(blue));
}
