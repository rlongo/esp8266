/****************************************************************************
  The is the main Arduino program consisting of the loop and setup functions.
*****************************************************************************/

#include "Arduino.h" // For platformio
#include "esp8266.h"
#include "network_config.h"

// LEDs
#define LED_GOOD_CONNECTION 7
#define LED_BAD_CONNECTION 6
#define LED_NETWORK_IO 5

// Whether or not we are connected Yto the internet
int isConnected = 0;

// Main setup function
void setup() {

  // Initialize the two, use the same baud rate
  Serial.begin(BAUD_ESP8266);
  Serial3.begin(BAUD_ESP8266);

  // Setup the LEDs
  pinMode(LED_GOOD_CONNECTION, OUTPUT);
  pinMode(LED_BAD_CONNECTION, OUTPUT);
  pinMode(LED_NETWORK_IO, OUTPUT);

  // Connect to the access point
  digitalWrite(LED_NETWORK_IO, HIGH);
  sendATCommand("AT+CWMODE=3", NETWORK_TIMEOUT_SHORT);
  isConnected = connectWifi(NETWORK_SSID, NETWORK_PASSWORD);

  // Display connection status
  if (isConnected) {
    digitalWrite(LED_GOOD_CONNECTION, HIGH);
  } else {
    digitalWrite(LED_BAD_CONNECTION, HIGH);
  }
  digitalWrite(LED_NETWORK_IO, LOW);

}

// Main loop function
void loop() {

}
