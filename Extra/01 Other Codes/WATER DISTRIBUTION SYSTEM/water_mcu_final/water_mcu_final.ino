#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include<SoftwareSerial.h>
SoftwareSerial s(D6,D5); // RX TX
#define FIREBASE_HOST "smart-city-2883e.firebaseio.com"                   
#define FIREBASE_AUTH "KLPO7nSFcTmK7VHck8gbCZPBa7E9wlTaElDxKPf3"       
#define WIFI_SSID "OPPO A5"                                              
#define WIFI_PASSWORD "12345678"
#define led D4
#define motor D8

//int val1,val2;
int data = 10000;
int waterlevel=10000;

void setup() 
{
  s.begin(9600);
  Serial.begin(19200);
  pinMode(led,OUTPUT);
  pinMode(motor,OUTPUT);
  
  //making connection ----------------------------------
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("Connecting...");
  while(WiFi.status()!=WL_CONNECTED)
  {
      Serial.print(".");
      delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
 
  //connecting to firebase----------------------------- 
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("water_level/level",0);
  Firebase.setInt("water_level/moto_status",0);
}

void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() 
{
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
	  
  s.write("s");
  if(s.available() >= 0)
  {
    data = s.read();
    if(data>=0)
    {
      waterlevel=data;
      Firebase.setInt("water_level/level",waterlevel);
      Serial.println(data); 
      Serial.println(); 
    }
    
    if(waterlevel<1)
    {
      Firebase.setInt("water_level/moto_status",1);
      digitalWrite(motor,HIGH);
      digitalWrite(led,LOW);
      delay(5);
    }
    if(waterlevel>4)
    {
      Firebase.setInt("water_level/moto_status",0);
      digitalWrite(motor,LOW);
      digitalWrite(led,HIGH);
      delay(5);
    }
  }
}
