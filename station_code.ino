#include "Wire.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 20, 4); 
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define LDR A1
unsigned int value;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(LDR, INPUT);
}

void loop() {
  value = analogRead(LDR);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.setCursor(0, 0);
    lcd.print("Capteur DHT erreur");
    delay(2000);
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidite : "));
  Serial.print(h);
  Serial.print(F("% Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("Lumiere: "));
  Serial.println(value);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Meteo actuelle");
  lcd.setCursor(0, 1);
  lcd.print("Temp.: ");
  lcd.print(t);
  lcd.print(" C");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Meteo actuelle");
  lcd.setCursor(0, 1);
  lcd.print("Humidite: ");
  lcd.print(h);
  lcd.print("%");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Meteo actuelle");
  lcd.setCursor(0, 1);
  lcd.print("Lumiere : ");
  int lightPercent = map(value, 500, 0, 0, 100);
  lcd.print(lightPercent);
  lcd.print("%");
  delay(1000);   
}