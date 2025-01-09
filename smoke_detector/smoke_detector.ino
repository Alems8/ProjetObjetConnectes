// #include <SoftwareSerial.h>
// #include <Wire.h>
// #include "Seeed_MCP9808.h"

// // Communication setup
// SoftwareSerial nucleoSerial(2, 3); // RX, TX (connected to Nucleo)
// MCP9808 tempSensor;

// // Pins and thresholds
// const int gasSensorPin = A0;
// const int ledPinKitchen = 11;
// const int ledPinLiving = 12;
// const int buzzerPin = 10;
// const int gasThreshold = 500;
// int tempThreshold = 25; // User-configurable

// void setup() {
//   nucleoSerial.begin(9600); // Communication with Nucleo
//   Serial.begin(9600);       // Debugging
  
//   pinMode(ledPinKitchen, OUTPUT);
//   pinMode(ledPinLiving, OUTPUT);
//   pinMode(buzzerPin, OUTPUT);

//   if (tempSensor.init()) { 
//     Serial.println("Could not find a valid MCP9808 sensor!");
//     while (1);
//   }
  
//   Serial.println("Arduino ready!!!");
// }

// void loop() {
//   // Gas and temperature checks
//   gasCheck();
//   readTemp();

//   // Handle commands from Nucleo
//   if (nucleoSerial.available()) {
//     String message = nucleoSerial.readStringUntil('\n');
//     if (message.startsWith("#") && message.endsWith("#")) {
//       message = message.substring(1, message.length() - 1); // Strip delimiters
//       handleCommand(message);
//     } else {
//       Serial.println("Garbage data received");
//     }
//   }

//   delay(100);
// }

// void gasCheck() {
//   int gasValue = analogRead(gasSensorPin);
//   Serial.println("Gas value: " + String(gasValue));

//   if (gasValue > gasThreshold) {
//     digitalWrite(ledPinKitchen, HIGH);
//     digitalWrite(buzzerPin, HIGH);
//     Serial.println("Smoke detected!");
//     nucleoSerial.println("#ALERT_SMOKE#");
//   } else {
//     digitalWrite(ledPinKitchen, LOW);
//     digitalWrite(buzzerPin, LOW);
//   }
// }

// void readTemp() {
//   float temp = 0;
//   tempSensor.get_temp(&temp);
//   Serial.println("Temperature: " + String(temp) + " C");

//   if (temp > tempThreshold) {
//     digitalWrite(ledPinLiving, HIGH);
//     Serial.println("High temperature detected!");
//     nucleoSerial.println("#ALERT_TEMP#");
//   } else {
//     digitalWrite(ledPinLiving, LOW);
//   }
// }

// void handleCommand(String command) {
//   Serial.println("Command received: " + command);

//   if (command == "SET_TEMP_THRESHOLD") {
//     // Example: Threshold set by the user
//     tempThreshold = 30; // Placeholder, you can parse values if needed
//     Serial.println("Temperature threshold updated to " + String(tempThreshold) + " C");
//     nucleoSerial.println("#TEMP_THRESHOLD_SET#");
//   } else if (command == "LOCK_DOOR") {
//     Serial.println("Lock door command received.");
//     digitalWrite(ledPinKitchen, LOW); // Example action
//     nucleoSerial.println("#DOOR_LOCKED#");
//   } else if (command == "UNLOCK_DOOR") {
//     Serial.println("Unlock door command received.");
//     digitalWrite(ledPinKitchen, HIGH); // Example action
//     nucleoSerial.println("#DOOR_UNLOCKED#");
//   } else {
//     Serial.println("Unknown command: " + command);
//   }
// }

#include <SoftwareSerial.h>
SoftwareSerial nucleoSerial(2, 3); // RX, TX

void setup() {
  nucleoSerial.begin(9600); // Match Nucleo's baud rate
  Serial.begin(9600);
  Serial.println("Arduino ready!!!");
}

void loop() {
  if (nucleoSerial.available()) {
    //Serial.println("hello!!");
    Serial.write(nucleoSerial.read());
    //String message = nucleoSerial.read(StringUntil('\n'));
    //Serial.println(String(message));
    const int ledPinKitchen = 11;
    pinMode(ledPinKitchen, OUTPUT);
    digitalWrite(ledPinKitchen, HIGH);
  }
}
