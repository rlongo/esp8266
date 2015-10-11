#include "esp8266.h"

bool didResponseSucceed(String response)
{
  char *connectionSucceededResponseString = "OK\r\n";
  return response.endsWith(connectionSucceededResponseString);
}

String sendATCommand(String command, const int timeout)
{

  // What was received from the command
  String response = "";

  // For fun
  if (DEBUG) {
    Serial.println("SENDING: " + command);
  }

  // Transmit the command
  Serial3.println(command);

  // Wait for a response
  long start_time = millis();

  while ((millis() - start_time) < timeout) {

    // Read out the buffer
    while (Serial3.available()) {
        char c = Serial3.read();
        response += c;
    }
  }

  // Print the message whenever appropriate
  if (DEBUG) {
    Serial.print(response.length() > 0
    	? response
    	: "No response received");
    Serial.println("");
  }

  return response;
}

bool connectWifi(String ssid, String pwd)
{
  // Send the connection request
  String cmd = "AT+CWJAP=\"" + ssid + "\",\"" + pwd + "\"";
  String response = sendATCommand(cmd, NETWORK_TIMEOUT_LONG);

  // Validate that we connected
  bool didConnectionSucceed = didResponseSucceed(response);

  if (DEBUG)
  {
    Serial.println( didConnectionSucceed
      ? "WiFi connection successful"
      : "Failed to connect to WiFi!");
  }
  return didConnectionSucceed;
}
