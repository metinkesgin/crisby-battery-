#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PCD8544.h>
#include <stdlib.h>
#include "battery.h"

#define BATTERYBED A0

Adafruit_PCD8544 lcd= Adafruit_PCD8544(D4,D3,D2,D1,D0);

void clearscreen();
float mat();

int j=0;
float vout = 0.0;
float vin = 0.0;

float R1 = 1000.0; // 1K ohm direnç
float R2 = 10000.0; // 10K ohm direnç
uint8_t *batterys[]= {battery0,battery1,battery2,battery3,battery4,battery5,battery6};

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.setContrast(60);
  clearscreen();
  delay(500);
}

void loop() {
  clearscreen();
  lcd.print(mat());
  lcd.drawBitmap(0,0,batterys[j],84,30,BLACK);
  Serial.println(j);
  lcd.display();
  delay(500);
}


void clearscreen(){
  lcd.clearDisplay();
  lcd.setCursor(18,33);
  lcd.setTextSize(2);
  lcd.setTextColor(BLACK);
}

float mat(){

  int gerilim = analogRead(BATTERYBED);
  vin = ((3.3*gerilim)/1024) * 0.90909090909;

  if (vin <0.22) j = 0;
  if (vin <0.44 && vin >=0.22) j = 1;
  if (vin <0.66 && vin >=0.44) j = 2;
  if (vin <0.88 && vin >=0.66) j = 3;
  if (vin <1.10 && vin >=0.88) j = 4;
  if (vin <1.32 && vin >=1.10) j = 5;
  if (vin <1.65 && vin >=1.32) j = 6; 

  return vin;
}