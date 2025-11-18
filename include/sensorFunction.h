#ifndef SENSORFUNCTION_H
#define SENSORFUNCTION_H

#include <Arduino.h>

String statusping(int trig, int echo);
String statuspir(int pin);
void gerbangMasuk(String s1, String s2);
void gerbangKeluar(String s1, String s2);

#endif