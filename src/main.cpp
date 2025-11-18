// mengimport library dan file yang di butuhkan
#include <Arduino.h> 
#include <ESP8266WiFi.h> 
#include <Firebase_ESP_Client.h> 
#include <addons/TokenHelper.h> 
#include "secrets.h" 
#include "sensorFunction.h"
#include "config.h"


FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

int slot = 0; 
bool alurMasuk = false;
bool alurKeluar = false;

void setup() {

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL; 
  config.signer.test_mode = true;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(pir1, INPUT);

}

void loop() {
  String sensor1 = statusping(TRIG1,ECHO1);
  String sensor2 = statuspir(pir1);

  bool statusAwalMasuk = alurMasuk;
  bool statusAwalKeluar = alurKeluar;
 
  gerbangMasuk(sensor1, sensor2);

  if (statusAwalMasuk || alurMasuk) {
      delay(50);
      return; 
  }
  
  gerbangKeluar(sensor1,sensor2);

  if (statusAwalKeluar || alurKeluar) {
      delay(50);
      return; 
  }
  
  Serial.print("Jumlah Slot: ");
  Serial.println(slot);

  if (Firebase.ready()) { 
    if (Firebase.RTDB.setString(&fbdo, "/Jumlah slot:", slot)) {
      Serial.println("Kirim data BERHASIL!");
    } else {
      Serial.print("Gagal: ");
      Serial.println(fbdo.errorReason());
    }
  } else {
    Serial.println("Firebase belum siap...");
  }

  delay(100);
}




