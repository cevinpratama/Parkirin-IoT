#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PCF8574.h>
#include <Servo.h>


#define LCD_ADDR 0x27 
#define PCF_ADDR 0x20 


const int pir1 = 0; 
const int pir2 = 1; 
const int pir3 = 2; 
const int pir4 = 3; 
const int pir5 = 4; 
const int pir6 = 5; 
const int pir7 = 6; 

const int servoPin = D5; 

extern PCF8574 pcf;
extern LiquidCrystal_I2C lcd;
extern Servo gateServo;

#endif