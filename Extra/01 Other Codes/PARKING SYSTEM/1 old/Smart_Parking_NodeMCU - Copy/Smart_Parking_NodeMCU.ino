#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include<SoftwareSerial.h>
#include<Servo.h>
 
SoftwareSerial s(3,1);

Servo motor;
int angle=0;

FirebaseData fbdo;
#define FIREBASE_HOST "smart-city-2883e.firebaseio.com"                   
#define FIREBASE_AUTH "KLPO7nSFcTmK7VHck8gbCZPBa7E9wlTaElDxKPf3"       
#define WIFI_SSID "Shahin Foundation"                                              
#define WIFI_PASSWORD "shahin.foundation  "

const int trigpin0=D0;    // For Entry Purpose
const int echopin0=D1;    // For Entry Purpose
const int trigpin1=D2;    // Slot1
const int echopin1=D3;    // Slot1
const int trigpin2=D5;    // Slot2
const int echopin2=D6;    // Slot2
const int trigpin3=D7;    // Slot3
const int echopin3=D8;    // Slot3

long duration0,duration1,duration2,duration3;
int distance0,distance1,distance2,distance3;
int slot1=0,slot2=0,slot3=0,slots=0;
int val1,val2,val3,p_status;

void setup()
{
  Serial.begin(19200);  
  //s.begin(9600);//Serial Begin
  
  motor.attach(D4); //Servo Motor

  // Pin Mode
  pinMode(trigpin0,OUTPUT);
  pinMode(echopin0,INPUT);
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);
  pinMode(trigpin2,OUTPUT);
  pinMode(echopin2,INPUT);
  pinMode(trigpin3,OUTPUT);
  pinMode(echopin3,INPUT);

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

  //Distance 1
  digitalWrite(trigpin1,LOW);  
  delay(2);
  digitalWrite(trigpin1,HIGH);
  delay(10);
  digitalWrite(trigpin1,LOW);
  duration1=pulseIn(echopin1,HIGH);
  distance1=duration1*0.034/2;

  //Distance 2
  digitalWrite(trigpin2,LOW);  
  delay(2);
  digitalWrite(trigpin2,HIGH);
  delay(10);
  digitalWrite(trigpin2,LOW);
  duration2=pulseIn(echopin2,HIGH);
  distance2=duration2*0.034/2;

  //Distance 3
  digitalWrite(trigpin3,LOW);  
  delay(2);
  digitalWrite(trigpin3,HIGH);
  delay(10);
  digitalWrite(trigpin3,LOW);
  duration3=pulseIn(echopin3,HIGH);
  distance3=duration3*0.034/2;

  Serial.println(String(distance0)+"\t"+(distance1)+"\t"+(distance2)+"\t"+(distance3));
  
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
  
  //slot2
  if(distance2<=5 && distance2>=1)
  {
    Firebase.setInt(fbdo,"S2",1);
    slot2=1;
  }
  else
  {
     Firebase.setInt(fbdo,"S2",0);
    slot2=0;
  }
  
  //slot3
  if(distance3<=5 && distance3>=1)
  {
    Firebase.setInt(fbdo,"S3",1);
    slot3=1;
  }
  else
  {
     Firebase.setInt(fbdo,"S3",0);
    slot3=0;
  }

  slots=slot1*100+slot2*10+slot3;
  Serial.println("Slots = "+String(slots));
  //s.write(slots); 
  //delay(1000);
  
  //--------------->Motor Controlling
  if(distance0<=5 && distance0 >= 1 && slots!=111)
  {
    Serial.println("\t\t\t\t\t Welcome");
    
    for(angle=105;angle>=0;angle-=5)      //opening gate
    {
    motor.write(angle);
    delay(5);
    }
    delay(5000);
    for(angle=0;angle<105;angle+=5)    //closing gate
    {
    motor.write(angle);
    delay(5);
    }
    
  }
  //else
  else if(distance0<=5 && distance0 >=1 && slots==111) 
  {
    Serial.println("\t\t\t\t\tFull");
  } 
  else
  {
    Serial.println("\t\t\t\tAvailable Slots = "+String(3-(slot1+slot2+slot3)));
  }
  
  delay(500);
}
