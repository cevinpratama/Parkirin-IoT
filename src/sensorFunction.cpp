#include "sensorFunction.h"
#include "config.h" 

extern int slot;
extern bool alurMasuk;
extern bool alurKeluar;

long duration;
int distance;

String statusping(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.0343 / 2;
  
  if (distance > 0 && distance < 5) { 
    return "Aktif";
  } else {
    return "Nonaktif";
  }
}

String statuspir(int pin){
  int statusSensor = digitalRead(pin);
  if(statusSensor == LOW){ 
    return "Aktif";
  } else {
    return "Nonaktif";
  }
}

void gerbangMasuk(String s1, String s2){
  if(s1 == "Aktif" && s2 == "Nonaktif" && !alurKeluar){
    alurMasuk = true;
    Serial.println("Terdeteksi di Pintu Masuk...");
  }

  if (alurMasuk && s2 == "Aktif"){
    slot -= 1;
    Serial.println("Mobil Masuk! Slot + 1");
    Serial.println("Menunggu area bersih...");

   
    while(statuspir(pir1) == "Aktif") { delay(100); }
    while(statusping(TRIG1, ECHO1) == "Aktif") { delay(100); }

    delay(1000); 
    alurMasuk = false; 
    Serial.println("Area Bersih. Siap deteksi baru.");
  }
}

void gerbangKeluar(String s1, String s2){
  if(s2 == "Aktif" && s1 == "Nonaktif" && !alurMasuk){
    alurKeluar = true;
    Serial.println("Terdeteksi di Pintu Keluar...");
  }

  if (alurKeluar && s1 == "Aktif"){
    slot += 1;
    Serial.println("Mobil Keluar! Slot - 1");
    Serial.println("Menunggu area bersih...");

    while(statusping(TRIG1, ECHO1) == "Aktif") { delay(100); }
    while(statuspir(pir1) == "Aktif") { delay(100); }

    delay(1000);
    alurKeluar = false;
    Serial.println("Area Bersih. Siap deteksi baru.");
  }
}