#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include<SoftwareSerial.h>
#include<Servo.h>
 
//SoftwareSerial s(3,1);
SoftwareSerial s(D1,D0); // RX TX

Servo motor;
int angle=0;

FirebaseData fbdo;
#define FIREBASE_HOST "smart-city-2883e.firebaseio.com"                   
#define FIREBASE_AUTH "KLPO7nSFcTmK7VHck8gbCZPBa7E9wlTaElDxKPf3"       
#define WIFI_SSID "Shahin Foundation"                                              
#define WIFI_PASSWORD "shahin.foundation"

//const int trigpin0=D0;    // For Entry Purpose
//const int echopin0=D1;    // For Entry Purpose
const int trigpin1=D2;    // Slot1
const int echopin1=D3;    // Slot1
long duration0,duration1,duration2,duration3;
int distance0,distance1,distance2,distance3;
int slot1=0,slot2=0,slot3=0,slots=0,data = 10000;;
int val1,val2,val3,p_status;

void setup()
{
  s.begin(9600);
  Serial.begin(19200);  
  
  motor.attach(D4); //Servo Motor

  // Pin Mode
  //pinMode(trigpin0,OUTPUT);
  //pinMode(echopin0,INPUT);
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);
  
  // Wifi Connection Starting
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setInt(fbdo,"S1",0);
  Firebase.setInt(fbdo,"S2",0);
  Firebase.setInt(fbdo,"S3",0); 
  
}

void loop() 
{  /*
  //Distance 0
  digitalWrite(trigpin0,LOW);  
  delay(2);
  digitalWrite(trigpin0,HIGH);
  delay(10);
  digitalWrite(trigpin0,LOW);
  duration0=pulseIn(echopin0,HIGH);
  distance0=duration0*0.034/2;
*/
  //Distance 1
  digitalWrite(trigpin1,LOW);  
  delay(2);
  digitalWrite(trigpin1,HIGH);
  delay(10);
  digitalWrite(trigpin1,LOW);
  duration1=pulseIn(echopin1,HIGH);
  distance1=duration1*0.034/2;


  Serial.println(String(distance1));//+"\t"+(distance1)+"\t"+(distance2)+"\t"+(distance3));
  
  //------------------------------------------------> Processing and uploading data

  //slot1
  if(distance1<=5 && distance1>=1)
  {
    Firebase.setInt(fbdo,"S1",1);
    slot1=1;
  }
  else
  {
     Firebase.setInt(fbdo,"S1",0);
     slot1=0;
  }
  
  slots=slot1;//*100+slot2*10+slot3;
  if(s.available() > 0) 
  {
    s.write(slots);
    Serial.print("-->  ");
    delay(1000);
  }
  
  Serial.println("Slots = "+String(slots));
}
