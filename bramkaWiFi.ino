#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID "Orange-821E"
#define WIFI_PASSWORD ""
#define RELAY 0

void setup() {
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY,HIGH);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
  }
    
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/bramka/action");
}

void loop()
{
  if(Firebase.available())
  {
    FirebaseObject event = Firebase.readEvent();
    if(event.getInt("data") == 1)
    {
        digitalWrite(RELAY,LOW);
        delay(1000);
        digitalWrite(RELAY,HIGH);  
    }  
  }  
}
