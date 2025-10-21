#ifndef communication_with_esp_h
#define communication_with_esp_h

#include <Arduino.h>

String inputString = "";
bool stringComplete = false;
String incomingData = "";
bool newDataAvailable = false;

void handleModeSwitch();
void parseInput(String data);
void printState();

#endif
