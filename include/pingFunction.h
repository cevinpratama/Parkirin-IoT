#include <Arduino.h> 
long duration;
int distance;


String status(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.0343 / 2;
  if (distance < 5)
  {
    return "aktif";
  } else {
    return "Nonaktif";
  }
  
}