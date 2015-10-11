/****************************************************************************
  The is the main Arduino program consisting of the loop and setup functions.
*****************************************************************************/

#include "Arduino.h" // For platformio
#include "esp8266.h"
#include "network_config.h"

// IO Devices
#define LED_GOOD_CONNECTION 7
#define LED_BAD_CONNECTION 6
#define LED_NETWORK_IO 5

#define BUTTON_PING_WESITE 4

// Whether or not we are connected to the internet
int isConnected = 0;

// Whether or not to ping the desired website
int pingButtonState = 0;

// Connection details
#define WEBSITE_PUBLIC_IP "192.168.1.8" // RoR server
#define WEBSITE_PORT "5000" // Port
#define API_GET_SCHOOLS "api/2.0/schools" // API Mount point for getting a list of schools

// Main setup function
void setup() {

  // Initialize the two Serial ports
  Serial.begin(BAUD_ESP8266);
  Serial3.begin(BAUD_ESP8266);

  // Setup the IOs
  pinMode(LED_GOOD_CONNECTION, OUTPUT);
  pinMode(LED_BAD_CONNECTION, OUTPUT);
  pinMode(LED_NETWORK_IO, OUTPUT);
  pinMode(BUTTON_PING_WESITE, INPUT);

  // First, let's flush out all the settings/ setup on the module
  sendATCommand("AT+RST", NETWORK_TIMEOUT_SHORT);

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

  // Configure the device for single connection
  sendATCommand("AT+CIPMUX=0", NETWORK_TIMEOUT_SHORT); // Single connection

  // Initiate a connection to something over wifi
  String pingWebsiteCommand = "AT+CIPSTART=\"TCP\",\""; // Setup conneection using TCP
  pingWebsiteCommand += WEBSITE_PUBLIC_IP;
  pingWebsiteCommand += "\",";
  pingWebsiteCommand += WEBSITE_PORT;

  digitalWrite(LED_NETWORK_IO, HIGH); // Start NetworkIO
  String response = sendATCommand(pingWebsiteCommand, NETWORK_TIMEOUT_SHORT);
  if (!didResponseSucceed(response)) {
    digitalWrite(LED_BAD_CONNECTION, HIGH);
    digitalWrite(LED_GOOD_CONNECTION, LOW);
    isConnected = false;
  }
  digitalWrite(LED_NETWORK_IO, LOW); // End NetworkIO
}

// Main loop function
void loop() {


}
