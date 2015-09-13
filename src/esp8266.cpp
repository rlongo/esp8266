#include "esp8266.h"

String sendATCommand(SoftwareSerial esp8266, String command, const int timeout) {

  // What was received from the command
  String response = "";

  // For fun
  if (DEBUG) {
    Serial.print("SENDING: " + command);
    Serial.println("");
  }

  // Transmit the command
  esp8266.println(command);

  // Wait for a response
  long start_time = millis();

  while ((millis() - start_time) < timeout) {

    // Read out the buffer
    while (esp8266.available()) {
        response += esp8266.readString();
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
