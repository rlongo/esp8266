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
#define WEBSITE_NAME "www.google.com" // The server (public domain name, or IP)
#define WEBSITE_PORT "80" // Port
#define WEBSITE_HOST_NAME "google.com" // Equivalent to google.com from my understanding
#define API_GET "/"

/*
  By design, on every TCP connection, we alway kill the connection whenever we
  do a simple API request... stupid, so construct this string object once and
  then we can just shove it out to the user every time in the future when we
  want to create a connection
*/
String pingWebsiteCommand;

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
  // So that we start in a known state
  sendATCommand("AT+RST", NETWORK_TIMEOUT_SHORT);

  // Connect to the access point
  digitalWrite(LED_NETWORK_IO, HIGH);
  sendATCommand("AT+CWMODE=3", NETWORK_TIMEOUT_SHORT);
  isConnected = connectWifi(NETWORK_SSID, NETWORK_PASSWORD);
  digitalWrite(LED_NETWORK_IO, LOW);

  // Configure the device for single connection
  sendATCommand("AT+CIPMUX=0", NETWORK_TIMEOUT_SHORT); // Single connection

  // Initiate a connection to something over wifi
  pingWebsiteCommand = "AT+CIPSTART=\"TCP\",\""; // Setup conneection using TCP
  pingWebsiteCommand += WEBSITE_NAME;
  pingWebsiteCommand += "\",";
  pingWebsiteCommand += WEBSITE_PORT;


  // Display connection status - do at end so user knows whether
  // they have permission to proceed or not...
  if (isConnected) {
    digitalWrite(LED_GOOD_CONNECTION, HIGH);
  } else {
    digitalWrite(LED_BAD_CONNECTION, HIGH);
  }

}

// Main loop function
void loop() {

  pingButtonState = digitalRead(BUTTON_PING_WESITE);

  if (isConnected && pingButtonState == HIGH)
  {
    // Step 1: connect to a TCP host
    digitalWrite(LED_NETWORK_IO, HIGH); // Start NetworkIO
    String response = sendATCommand(pingWebsiteCommand, NETWORK_TIMEOUT_SHORT);

    // Step 2: Construct a command and send it off
    if (didResponseSucceed(response))
    {
      // Actual command
      String apiCommand = getHttpSessionCommand(HTTP_GET, API_GET, WEBSITE_HOST_NAME);

      // The packet header, it is the size of the command
      String tcpPacket = "AT+CIPSEND=" + String(apiCommand.length());

      digitalWrite(LED_NETWORK_IO, HIGH);
      sendATCommand(tcpPacket, NETWORK_TIMEOUT_SHORT);
      sendATCommand(apiCommand, NETWORK_TIMEOUT_SHORT);
      digitalWrite(LED_NETWORK_IO, LOW);
    }
    digitalWrite(LED_NETWORK_IO, LOW); // End NetworkIO
  }

}
