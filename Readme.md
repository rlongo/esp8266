# ESP8266

The following project uses an Arduino Mega and and ESP8266 to test the ESP's
functionality. It connects to the internet and pings www.google.com.

## Building

To build this project, you must use [platformio](http://docs.platformio.org/en/latest/)

### Missing Files

`network_config.h` With the following contents:
```cpp
#ifndef _NETWORK_CONFIG_H
#define  _NETWORK_CONFIG_H

// Functional constants
const String NETWORK_SSID = "your_ssid";
const String NETWORK_PASSWORD = "your_password";

#endif
```


## Pin Guide

Pin-Out Guide [Arduino & ESP8266 Reference](http://forum.arduino.cc/index.php?topic=283043.0)

| Arduino PIN#   |    ESP8266 PIN |
|----------------|----------------|
|  RX3           |     TX         |
|  TX3           |     RX         |
|  GND           |     GND        |
|  3.3V          |  VCC, CH_PD, RESET |

### Other Pins Used
| Arduino PIN# |    Component |   Function |
|--------------|--------------|------------|
|  7           |     LED      | Good Network Connection |
|  6           |     LED       | Error in network transmission |
|  5           |     LED      | Network IO Occurring |
|  4           |     BUTTON      | Ping the desired website |
