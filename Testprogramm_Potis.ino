#include <LiquidCrystal.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

// Potis zur Sensorsimulation
const int potTempPin  = A0;  // Poti 1 → simuliert Temperatur 
const int potHumPin   = A1;  // Poti 2 → simuliert Luftfeuchte 
const int potLightPin = A2;  // Poti 3 → simuliert Lichtintensität 

// LED-Pins
const int ledGruen      = A3;
const int ledGelb       = A4;
const int ledRot        = A5;

void setup() {
  lcd.begin(16, 2);
  lcd.print("System Start...");
  delay(2000);
  lcd.clear();

  pinMode(ledGruen, OUTPUT);
  pinMode(ledGelb, OUTPUT);
  pinMode(ledRot, OUTPUT);
}

void loop() {
  // Potis einlesen (0…1023)
  int rawT = analogRead(potTempPin);
  int rawH = analogRead(potHumPin);
  int rawL = analogRead(potLightPin);

  // in reale Werte umrechnen
  float temp     = map(rawT, 0, 1023, 0, 50);   // 0–50 °C
  float hum      = map(rawH, 0, 1023, 20, 90);  // 20–90 %
  int   lichtWert = map(rawL, 0, 1023, 4, 450);  // 4–450 lx

  //LCD-Anzeige
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(temp,1) + "oC "); lcd.print("H:" + String(hum,0) + "%");
  lcd.setCursor(0, 1);
  lcd.print("L:" + String(lichtWert) + "lx");

  // LED-Statuslogik
  bool kritisch  = false;
  bool grenzwert = false;

  if      (temp     > 17.0)  kritisch = true;
  else if (temp     > 10.0)  grenzwert = true;

  if      (hum      > 40.0)  kritisch = true;
  else if (hum      > 30.0)  grenzwert = true;

  if      (lichtWert > 100)   kritisch = true;
  else if (lichtWert > 70)    grenzwert = true;

  digitalWrite(ledGruen, (!kritisch && !grenzwert));
  digitalWrite(ledGelb,  (grenzwert && !kritisch));
  digitalWrite(ledRot,   kritisch);

  delay(1000);
}