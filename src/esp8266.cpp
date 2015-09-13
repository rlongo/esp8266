#include "esp8266.h"

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
  String successfulResponseSubstr = "OK\r\n";
  String response = sendATCommand(cmd, NETWORK_TIMEOUT_LONG);

  bool didConnectionSucceed = false;

  // Parse the response for a success
  if (response.length() > successfulResponseSubstr.length())
  {
      response = response.substring(
        response.length() - successfulResponseSubstr.length()
      );

      didConnectionSucceed = 0 == response.compareTo(successfulResponseSubstr);
  }

  if (DEBUG)
  {
    Serial.println( didConnectionSucceed
      ? "WiFi connection successful"
      : "Failed to connect to WiFi!");
  }
  return didConnectionSucceed;
}
