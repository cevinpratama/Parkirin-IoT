#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include "secrets.h"
#include "sensorFunction.h"
#include "config.h"

LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);
PCF8574 pcf(PCF_ADDR); 
Servo gateServo;

FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

int slot = 5; 
bool alurMasuk = false;
bool alurKeluar = false;


void setup() {
  Serial.begin(115200);
  Serial.println("\nSystem Booting...");

  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Parking");
  lcd.setCursor(0,1);
  lcd.print("Init Hardware...");

  if (!pcf.begin()) {
    Serial.println("GAGAL: PCF8574 tidak terdeteksi!");
    lcd.setCursor(0,1);
    lcd.print("Sensor Error!  ");
    while(1);
  }
  Serial.println("OK: PCF8574 Connected");

  gateServo.attach(servoPin);
  gateServo.write(0); 

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Siap Digunakan");
  delay(1000);

}

void loop() {
   String sensor1 = statuspir(pir1);
   String sensor2 = statuspir(pir2);
   String sensor3 = statuspir(pir3);
   String sensor4 = statuspir(pir4);
   String sensor5 = statuspir(pir5);
   String sensor6 = statuspir(pir6);
   String sensor7 = statuspir(pir7);

   Serial.println("Sensor 1 = "+ sensor1);
   Serial.println("Sensor 2 = "+ sensor2);
   Serial.println("Sensor 3 = "+ sensor3);
   Serial.println("Sensor 4 = "+ sensor4);
   Serial.println("Sensor 5 = "+ sensor5);
   Serial.println("Sensor 6 = "+ sensor6);
   Serial.println("Sensor 7 = "+ sensor7);
   Serial.println("=========================");
   Serial.println("=========================");




  delay(3000);
}