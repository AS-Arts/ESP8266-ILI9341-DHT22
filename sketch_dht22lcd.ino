#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <time.h>

#define TFT_CS 4 //  D2 = GPIO 4
#define TFT_RST 0 // D3 = GPIO 0
#define TFT_DC 2 //  D4 = GPIO 2
#define DHTPIN 5 //  D1 = GPIO 5
#define DHTTYPE DHT22 

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
DHT dht(DHTPIN, DHTTYPE,12);
WiFiClient espClient; 


const char* wifi_ssid = "YOUR-WIFI-NAME";
const char* wifi_password = "YOUR-WIFI-PASSWORD";

 
void setup() {
  Serial.begin(9600);
  
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  
  dht.begin();   
  WiFi.begin(wifi_ssid, wifi_password);
  
  configTime(1 * 3600, 0, "0.de.pool.ntp.org", "ptbtime1.ptb.de"); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
   
  delay(1000);
}
 
 
void loop() {                 

  float pfTemp = dht.readTemperature();
  float pfHum = dht.readHumidity();  
  float a = 17.67;
  float b = 243.5;
  float alpha = (a * pfTemp)/(b + pfTemp) + log(pfHum/100);
  float pfDew = (b * alpha)/(a - alpha);
  
  tft.setCursor(0, 20);
  
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  tft.setTextSize(4); 
  tft.print(pfTemp);
  tft.println("C");

  tft.setTextColor(ILI9341_BLUE); tft.setTextSize(2);
  tft.println("Temperature\n");
  


  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  tft.setTextSize(4);
  tft.print(pfHum);
  tft.println("%");

  tft.setTextColor(ILI9341_BLUE); tft.setTextSize(2);
  tft.println("Humidity\n");



  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  tft.setTextSize(4);
  tft.print(pfDew);
  tft.println("C");

  tft.setTextColor(ILI9341_BLUE); tft.setTextSize(2);
  tft.println("Dewpoint\n");

  

  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  tft.setTextSize(2);
  time_t now = time(nullptr);
  String time = String(ctime(&now));
  time.trim();
  char time_value[20];
  time.substring(0,19).toCharArray(time_value, 20); 
  tft.println(time_value);

 delay(1000);
  
}
 



 
 
