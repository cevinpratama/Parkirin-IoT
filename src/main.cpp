// mengimport library dan file yang di butuhkan
#include <Arduino.h> 
#include <ESP8266WiFi.h> 
#include <Firebase_ESP_Client.h> 
#include <addons/TokenHelper.h> 
#include "secrets.h" 
#include "sensorFunction.h"
#include "config.h"

int slot = 0; 
bool alurMasuk = false;
bool alurKeluar = false;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(pir1, INPUT);
}

void loop() {
  String sensor1 = statusping(TRIG1,ECHO1);
  String sensor2 = statuspir(pir1);
 
  gerbangMasuk(sensor1, sensor2);
  gerbangKeluar(sensor1,sensor2);
  
  Serial.print("Jumlah Slot: ");
  Serial.println(slot);

  delay(100);
}




