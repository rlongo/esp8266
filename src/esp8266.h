#ifndef _ESP8266_H
#define  _ESP8266_H

#include "Arduino.h" // For platformio

// Prints debug messages when set to true
#define DEBUG true

// Key pins for the class
#define ESP8266_TX_PIN 11
#define ESP8266_RX_PIN 12

// Baud rate. One of: 115200 or 9600 (mine is 115200)
#define BAUD_ESP8266 115200

// How long to wait for any network transaction before giving up
#define NETWORK_TIMEOUT_LONG  12000
#define NETWORK_TIMEOUT_SHORT 2500

/*
  Attempts to send a given AT command to the ESP8266
    command:: the command, without '\r\n' (we append that)
    timeout:: how long to wait before giving up on the communication
    RETURNS:: the response
*/
String sendATCommand(String command, const int timeout);

/*
  Attempts to connect to wifi using magic
  ssid:: network's ssid
  pwd:: password corresponding to the ssid
  RETURNS:: true if succeeded
*/
bool connectWifi(String ssid, String pwd);

#endif
