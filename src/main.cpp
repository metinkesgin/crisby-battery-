//KÜTÜPHANELERİMİZİ TANIMLIYORUZ
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PCD8544.h>
#include "battery.h"

//PİL YUVASININ PROTUNUZ TANIMLIYORUZ
#define BATTERYBED A0

//LCD EKRANIMIZI TANIMLIYORUZ
Adafruit_PCD8544 lcd= Adafruit_PCD8544(D4,D3,D2,D1,D0);

//ÇOK FAZLA YAPTIĞIMIZ İŞLERİ FONKSİYONLAŞTIRIP İŞİMİZİ KOLAYLAŞTIRIYORUZ
void clearscreen();
float mat();

//VERİLERİMİZİ TANIMLIYORUZ
struct veriler
{
int j=0;
float vin = 0.0;
};
veriler veri;

//PİL RESİMLERİNİ DİZİNE ATIYORUZ
uint8_t *batterys[]= {battery0,battery1,battery2,battery3,battery4,battery5,battery6};

//NODEMCU BAŞLADIĞINDA BİR SEFER ÇALIŞACAK KODLAR
void setup() {
  lcd.begin();
  lcd.setContrast(60);
  clearscreen();
  delay(500);
}

//NODEMCU BAŞLADIĞINDA SÜREKLİ ÇALIŞACAK KODLAR
void loop() {
  clearscreen();
  lcd.print(mat());
  lcd.drawBitmap(0,0,batterys[veri.j],84,30,BLACK);
  lcd.display();
  delay(500);
}

//LCD EKRANI TEMİZLEMEK İÇİN KULLANILAN FONKSİYON
void clearscreen(){
  lcd.clearDisplay();
  lcd.setCursor(18,33);
  lcd.setTextSize(2);
  lcd.setTextColor(BLACK);
}

// ANALOG PİNDEN ALDIĞIMIZ DEĞERİ VOLTA ÇEVİRİP HANGİ BİTMAPİN GÖSTERİLECEĞİNİ AYARLAYAN FONKSİYON
float mat(){
  veri.vin = ((3.3*analogRead(BATTERYBED))/1024) * 0.90909090909;
  
  delay(50);
  
  if (veri.vin <1.00) veri.j = 0;
  if (veri.vin <1.071 && veri.vin >=1.00) veri.j = 1;
  if (veri.vin <1.142 && veri.vin >=1.071) veri.j = 2;
  if (veri.vin <1.213 && veri.vin >=1.142) veri.j = 3;
  if (veri.vin <1.284 && veri.vin >=1.213) veri.j = 4;
  if (veri.vin <1.355 && veri.vin >=1.284) veri.j = 5;
  if (veri.vin <1.650 && veri.vin >=1.355) veri.j = 6; 

  return veri.vin;
}