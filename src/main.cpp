#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>
#include <addons/TokenHelper.h>
#include <PCF8574.h>
#include <Servo.h>
#include "sensorFunction.h" 
#include "config.h" 
#include "secrets.h"

FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);
PCF8574 pcf(PCF_ADDR); 
Servo gateServo;

int slot = 5; 
int slotSebelumnya = -1; 
unsigned long lastSendTime = 0;
const int sendInterval = 2000;

bool alurMasuk = false;
bool alurKeluar = false;

String lastStatusS3 = "";
String lastStatusS4 = "";
String lastStatusS5 = "";
String lastStatusS6 = "";
String lastStatusS7 = "";

void sendStatus(String path, String currentValue, String lastValue){
  if (currentValue != lastValue) {
       
       String statusText;
       if (currentValue == "Aktif") { 
           statusText = "Terisi";
       } else {
           statusText = "Kosong";
       }

       Serial.print("Update " + path + ": " + statusText + "... ");

       if (Firebase.RTDB.setString(&fbdo, "/parkirin/" + path, statusText)) 
       {
          Serial.println("BERHASIL");
          lastValue = currentValue; 
       }
       else
       {
          Serial.print("GAGAL: ");
          Serial.println(fbdo.errorReason());
       }
   }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan WiFi");

  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Parking");
  lcd.setCursor(0,1);
  lcd.print("Init Hardware...");

  gateServo.attach(servoPin); 
  gateServo.write(0);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.signer.test_mode = true;
  fbdo.setBSSLBufferSize(1024, 1024);
  config.token_status_callback = tokenStatusCallback; 

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  if (!pcf.begin()) {
    Serial.println("GAGAL: PCF8574 tidak ditemukan atau kabel kendor!");
    Serial.println("Cek kabel SDA/SCL dan Power (3.3V/5V).");
    while (1); 
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Siap Digunakan");
  delay(1000);
}

void loop()
{
   
   String sensor3 = statuspir(pir3); 
   String sensor4 = statuspir(pir4); 
   String sensor5 = statuspir(pir5); 
   String sensor6 = statuspir(pir6); 
   String sensor7 = statuspir(pir7); 

    if (Firebase.ready()) {

     String sensor1 = statuspir(pir1); 
     String sensor2 = statuspir(pir2); 

     bool statusAwalMasuk = alurMasuk;
     bool statusAwalKeluar = alurKeluar;

     gerbangMasuk(sensor1, sensor2);
     if (statusAwalMasuk || alurMasuk) { delay(50); return; }

     gerbangKeluar(sensor1, sensor2);
     if (statusAwalKeluar || alurKeluar) { delay(50); return; }

     
     if (slot != slotSebelumnya && (millis() - lastSendTime > sendInterval)) 
     {
        Serial.print("Perubahan terdeteksi! Mengirim Slot: ");
        Serial.println(slot);

        if (Firebase.RTDB.setInt(&fbdo, "/parkirin/jumlah_slot", slot)) 
        {
           Serial.println("Kirim data BERHASIL!");
           slotSebelumnya = slot; 
           lastSendTime = millis();
        }
        else
        {
           Serial.print("Gagal: ");
           Serial.println(fbdo.errorReason());
        }
        lcd.setCursor(0, 0);
        lcd.print("Smart Parking   ");
        lcd.setCursor(0, 1);
        lcd.print("Slot Kosong: ");
        lcd.print(slot);
        lcd.print(" ");
     }
      sendStatus("slot_1",sensor3, lastStatusS3);
      sendStatus("slot_2",sensor4, lastStatusS4);
      sendStatus("slot_3",sensor5, lastStatusS5);
      sendStatus("slot_4",sensor6, lastStatusS6);
      sendStatus("slot_5",sensor7, lastStatusS7);

      
  } 
  else 
  {
     static unsigned long lastPrint = 0;
     if (millis() - lastPrint > 1000) {
        Serial.println("Menunggu Firebase siap...");
        lastPrint = millis();
     }
  }
  
  delay(100); 
  
}

