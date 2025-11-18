#include <Arduino.h> 
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
  if (distance < 5)
  {
    return "Aktif";
  } else {
    return "Nonaktif";
  }
  
}

String statuspir(int pin){
  if(pin == LOW){
    return "Aktif";
  } else {
    return "Nonaktif";
  }
}