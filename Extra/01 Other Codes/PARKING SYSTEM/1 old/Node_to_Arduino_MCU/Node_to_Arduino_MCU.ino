#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include<SoftwareSerial.h>
 
SoftwareSerial s(3,1);

FirebaseData fbdo;
#define FIREBASE_HOST "smart-city-2883e.firebaseio.com"                   
#define FIREBASE_AUTH "KLPO7nSFcTmK7VHck8gbCZPBa7E9wlTaElDxKPf3"       
#define WIFI_SSID "Shahin Foundation"                                              
#define WIFI_PASSWORD "shahin.foundation"

const int trigpin0=D0;    // For Entry Purpose
const int echopin0=D1;    // For Entry Purpose

long duration0,duration1,duration2,duration3;
int distance0,distance1,distance2,distance3;
int slot1=0,slot2=0,slot3=0,slots=0;
int val1,val2,val3,p_status;

void setup()
{
  //Serial.begin(19200);  
  
  s.begin(9600);//Serial Begin
  Serial.println("Start");
  
  // Pin Mode
  pinMode(trigpin0,OUTPUT);
  pinMode(echopin0,INPUT);

  // Wifi Connection Starting
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setInt(fbdo,"S1",0);
  Firebase.setInt(fbdo,"S2",0);
  Firebase.setInt(fbdo,"S3",0); 
}

void loop() 
{  
  //Distance 0
  digitalWrite(trigpin0,LOW);  
  delay(2);
  digitalWrite(trigpin0,HIGH);
  delay(10);
  digitalWrite(trigpin0,LOW);
  duration0=pulseIn(echopin0,HIGH);
  distance0=duration0*0.034/2;

  Serial.println(String(distance0));//+"\t"+(distance1)+"\t"+(distance2)+"\t"+(distance3));

  if(distance0<=10)
  {
  Firebase.setInt(fbdo,"S1",distance0);
  }
  else
  {
     Firebase.setInt(fbdo,"S1",distance0);
  }
  //s.write(distance0); 
  delay(1000);
  delay(500);
}
