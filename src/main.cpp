// mengimport library dan file yang di butuhkan
#include <Arduino.h> 
#include <ESP8266WiFi.h> 
#include <Firebase_ESP_Client.h> 
#include <addons/TokenHelper.h> 
#include "secrets.h" 
#include "pingFunction.h"

const int TRIG_PIN = D5;
const int ECHO_PIN = D6; 



void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  
  String sensor1 = status(TRIG_PIN,ECHO_PIN);
  // Tampilkan hasil
  Serial.print("Status Sensor: ");
  Serial.println(sensor1);

  delay(500);
}


