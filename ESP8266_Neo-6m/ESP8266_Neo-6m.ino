#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
TinyGPSPlus gps;            // The TinyGPS++ object
SoftwareSerial ss(12, 14);  // The serial connection to the GPS device
float latitude, longitude;
int year, month, date, hour, minute, second;
String date_str, time_str, lat_str, lng_str;
int pm;

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("JustDoElectronic");
}


void loop() {
  while (ss.available() > 0)    //while data is available
    if (gps.encode(ss.read()))  //read gps data
    {
      if (gps.location.isValid())  //check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude, 6);  // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude, 6);  //longitude location is stored in a string
        Serial.print(gps.location.lat());
        Serial.print(",");
        Serial.println(gps.location.lng());
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  GPS Location ");
        lcd.setCursor(2, 1);
        lcd.print(gps.location.lat());
        lcd.print(",");
        lcd.print(gps.location.lng());
        delay(2000);
      }
      if (gps.date.isValid())  //check whether gps date is valid
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
        Serial.print(gps.date.day());
        Serial.print("/");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.println(gps.date.year());
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  DD/MM/YEAR");
        lcd.setCursor(2, 1);
        lcd.print(gps.date.day());
        lcd.print("/");
        lcd.print(gps.date.month());
        lcd.print("/");
        lcd.print(gps.date.year());
        delay(2000);
      }
      if (gps.time.isValid())  //check whether gps time is valid
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
      }
    }
}