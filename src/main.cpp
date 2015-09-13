/****************************************************************************

  The following code is a basic stub for using the ESP8266 with an Arduino
  board. It uses a software serial connection to facilitate the serial
  communication between the Arduino and ESP8266.

  Pin-Out Guide (Arduino & ESP8266)
  (Refer here: http://forum.arduino.cc/index.php?topic=283043.0)
  Arduino PIN#   |    ESP8266 PIN
   12            |     RX
   11            |     TX
   GND           |     GND
   3.3V          |     VCC, CH_PD, RESET

   Other Pins Used
   7 -> LED (Good connection)
   6 -> LED (Error in connection)
   5 -> Network IO event LED

*****************************************************************************/

#include "Arduino.h" // For platformio
#include "esp8266.h"

// Functional constants
const String SSID = "Xiuhcoatl";
const String PSWD = "trUWrepHacuve2pe";

// LEDs
#define LED_GOOD_CONNECTION 7
#define LED_BAD_CONNECTION 6
#define LED_NETWORK_IO 5

// Whether or not we are connected Yto the internet
int isConnected = 0;

/*
  An object that facilitates the serial communication between arduino and
  the esp8266
*/
SoftwareSerial esp8266(ESP8266_TX_PIN, ESP8266_RX_PIN);

// Main setup function
void setup() {

  // Initialize the two, use the same baud rate
  Serial.begin(9600);
  esp8266.begin(BAUD_ESP8266);

  // Setup the LEDs
  pinMode(LED_GOOD_CONNECTION, OUTPUT);
  pinMode(LED_BAD_CONNECTION, OUTPUT);
  pinMode(LED_NETWORK_IO, OUTPUT);

  // Let's initiate a network connection, see what happens
  digitalWrite(LED_NETWORK_IO, HIGH);

  // Setup access mode
  sendATCommand(esp8266, "AT+CWMODE=3", NETWORK_TIMEOUT_LONG);
  String result = sendATCommand(esp8266, "AT+CWJAP=\"" + SSID + "\",\""
                                    + PSWD + "\"", NETWORK_TIMEOUT_LONG);
  digitalWrite(LED_NETWORK_IO, LOW);

  if (result.length() > 0) {
    isConnected = 1;
    digitalWrite(LED_GOOD_CONNECTION, HIGH);
  } else {
    digitalWrite(LED_BAD_CONNECTION, HIGH);
  }

}

// Main loop function
void loop() {

}
