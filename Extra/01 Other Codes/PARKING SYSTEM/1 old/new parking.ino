------------> 
----------------->Arduino parking code👇🏻
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int data; //Initialized variable to store recieved data
int slot1,slot2,slot3;

void setup() 
{
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() 
{
  data = Serial.read(); //Read the serial data and store it
  Serial.println(data);
  delay(1000);
  slot3=data%10;
  data=data/10;
  slot2=data%10;
  data=data/10;
  slot1=data;
  if(slot1==1 && slot2==1 && slot3==1)
  {
    lcd.print("Sorry!");
    lcd.setCursor(0, 1);
    lcd.print("Slots Full !");
  }
  else
  {
    lcd.print("WELCOME !");
    lcd.setCursor(0, 1);
    lcd.print("Slots Available!");
  }
}

---------------------------------------------------------------------

---------------------------------------------------------------------


------------------->Nodemcu parking code👇🏻
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
#define WIFI_SSID "vivo 1610"                                              
#define WIFI_PASSWORD "Rb@8347874257"

const int trigpin=D0;   //slot1
const int echopin=D1;   //slot1
const int trigpin1=D2;   //slot2
const int echopin1=D3;    //slot2
const int trigpin2=D5;   //slot3
const int echopin2=D6;    //slot3
const int trigpin3=D7;   //For entry purpose
const int echopin3=D8;    //For entry purpose
   
long duration,duration1,duration2,duration3;
int distance,distance1,distance2,distance3;
int slot1,slot2,slot3,slots;
int val1,val2,val3,p_status;

void setup() {
  //Serial S Begin at 9600 Baud
  s.begin(9600);
  motor.attach(D4);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);
  pinMode(trigpin2,OUTPUT);
  pinMode(echopin2,INPUT);
  pinMode(trigpin3,OUTPUT);
  pinMode(echopin3,INPUT);
    
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
   
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setInt(fbdo,"S1",0);
  Firebase.setInt(fbdo,"S2",0);
  Firebase.setInt(fbdo,"S3",0); 
}
void loop() {
  Firebase.getInt(fbdo,"S1"); 
  val1=fbdo.intData();
  Firebase.getInt(fbdo,"S2"); 
  val2=fbdo.intData();
  Firebase.getInt(fbdo,"S3"); 
  val3=fbdo.intData();

  if(val1==1 && val2==1 && val3==1){
    p_status=1;
  }else{
    p_status=0;
  }
  //---------------> gate
  digitalWrite(trigpin3,LOW);
  delay(2);
  digitalWrite(trigpin3,HIGH);
  delay(10);
  digitalWrite(trigpin3,LOW);

  duration3=pulseIn(echopin3,HIGH);
  distance3=duration3*0.034/2;

  if(distance3<=5 && p_status==0){
    for(angle=105;angle>=0;angle-=5){
    motor.write(angle);
    delay(5);
  }
  delay(3000);
  }else{
    for(angle=0;angle<105;angle+=5){
    motor.write(angle);
    delay(5);
  }
  }
  //--------------> slot1
  digitalWrite(trigpin,LOW);
  delay(2);
  digitalWrite(trigpin,HIGH);
  delay(10);
  digitalWrite(trigpin,LOW);

  duration=pulseIn(echopin,HIGH);
  distance=duration*0.034/2;

  //--------------> slot2
  digitalWrite(trigpin1,LOW);
  delay(2);
  digitalWrite(trigpin1,HIGH);
  delay(10);
  digitalWrite(trigpin1,LOW);

  duration1=pulseIn(echopin1,HIGH);
  distance1=duration1*0.034/2;

  //--------------> slot3
  digitalWrite(trigpin2,LOW);
  delay(2);
  digitalWrite(trigpin2,HIGH);
  delay(10);
  digitalWrite(trigpin2,LOW);

  duration2=pulseIn(echopin2,HIGH);
  distance2=duration2*0.034/2;

  if(distance<=5){
    Firebase.setInt(fbdo,"S1",1);
    slot1=1;
  }else{
     Firebase.setInt(fbdo,"S1",0);
    slot1=0;
  }
  
  if(distance1<=5){
    Firebase.setInt(fbdo,"S2",1);
    slot2=1;
  }else{
    Firebase.setInt(fbdo,"S2",0);
    slot2=0;
  }
  
  if(distance2<=5){
    Firebase.setInt(fbdo,"S3",1);
    slot3=1;
  }else{
    Firebase.setInt(fbdo,"S3",0);
    slot3=0;
  }
  
  slots=slot1*100+slot2*10+slot3;
  s.write(slots);
  delay(1000);
}