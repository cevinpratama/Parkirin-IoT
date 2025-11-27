// #include "sensorFunction.h"
// #include "config.h"

// extern int slot;
// extern bool alurMasuk;
// extern bool alurKeluar;

// String statuspir(int pin){
//   int val = pcf.read(pin);
  
//   if(val == LOW){ 
//     return "Aktif";
//   } else {
//     return "Nonaktif";
//   }
// }

// void gerbangMasuk(String s1, String s2){
//   if(s1 == "Aktif" && s2 == "Nonaktif" && !alurKeluar){
//     alurMasuk = true;
//     Serial.println("Gerbang Masuk: Terdeteksi...");
    
//     lcd.setCursor(0, 0);
//     lcd.print("Mobil Masuk...  ");
    
//     gateServo.write(150); 
//   }

//   if (alurMasuk && s2 == "Aktif"){
//     slot -= 1;
//     Serial.println("Mobil Masuk! Slot Berkurang.");
//     Serial.println("Menunggu mobil lewat...");

//     unsigned long timeout = millis();
//     while((statuspir(pir2) == "Aktif" || statuspir(pir1) == "Aktif")) { 
//         delay(50);
//         if(millis() - timeout > 10000) break; 
//     }

//     delay(1000); 
//     alurMasuk = false; 
    
//     gateServo.write(0);
    
//     Serial.println("Area Bersih. Palang Tutup.");
//     lcd.setCursor(0, 0);
//     lcd.print("Selamat Datang  ");
//   }
// }

// void gerbangKeluar(String s1, String s2){
//   if(s2 == "Aktif" && s1 == "Nonaktif" && !alurMasuk){
//     alurKeluar = true;
//     Serial.println("Gerbang Keluar: Terdeteksi...");
    
//     lcd.setCursor(0, 0);
//     lcd.print("Mobil Keluar... ");
    
//     gateServo.write(150);
//   }

//   if (alurKeluar && s1 == "Aktif"){
//     slot += 1;
//     Serial.println("Mobil Keluar! Slot Bertambah.");
//     Serial.println("Menunggu mobil lewat...");

//     unsigned long timeout = millis();
//     while((statuspir(pir1) == "Aktif" || statuspir(pir2) == "Aktif")) { 
//         delay(50); 
//         if(millis() - timeout > 10000) break;
//     }

//     delay(1000);
//     alurKeluar = false;
    
//     gateServo.write(0);
    
//     Serial.println("Area Bersih. Palang Tutup.");
//     lcd.setCursor(0, 0);
//     lcd.print("Hati-hati...    ");
//     delay(1500);
//   }
// }