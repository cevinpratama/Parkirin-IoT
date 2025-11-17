// mengimport library dan file yang di butuhkan
#include <Arduino.h> 
#include <ESP8266WiFi.h> 
#include <Firebase_ESP_Client.h> 
#include <addons/TokenHelper.h> 
#include "secrets.h" 

const int TRIG_PIN = D5;
const int ECHO_PIN = D6; 
long duration;
int distance;



void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Baca durasi pulsa Echo
  duration = pulseIn(ECHO_PIN, HIGH);

  // Hitung jarak (cm)
  distance = duration * 0.0343 / 2;

  // Tampilkan hasil
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}

