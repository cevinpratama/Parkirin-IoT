// mengimport library dan file yang di butuhkan
#include <Arduino.h> 
#include <ESP8266WiFi.h> 
#include <Firebase_ESP_Client.h> 
#include <addons/TokenHelper.h> 
#include "secrets.h" 
#include "pingFunction.h"
#include "config.h"



void setup() {
  Serial.begin(115200);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
}

void loop() {
  
  String sensor1 = status(TRIG1,ECHO1);

  
  // Tampilkan hasil
  Serial.print("Status Sensor: ");
  Serial.println(sensor1);

  delay(500);
}


