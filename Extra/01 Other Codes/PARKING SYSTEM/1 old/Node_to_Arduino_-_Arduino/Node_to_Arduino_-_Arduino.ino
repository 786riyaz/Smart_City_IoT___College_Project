#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<Servo.h>
#include<SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27,16,2); // SDA=A4 SCL=A5
SoftwareSerial s(13,12);       // RX=D0 TX=D1
int data,avail;
int slots = 1000,slot1=5,slot2=5,slot3=5;
long duration0;
int distance0;

Servo motor;
int angle=0;

const int trigpin0=2;    // For Entry Purpose
const int echopin0=3;    // For Entry Purpose
const int greenled=5;    // GREEN LED
const int redled=6;      // RED LED
const int slot1led=9;      //Slot 1 LED
const int slot2led=8;      //Slot 2 LED
const int slot3led=7;      //Slot 3 LED

void setup()
{ 
  s.begin(9600);
  Serial.begin(19200);
  Serial.println("Start");

  //SERVO
  motor.attach(4); //Servo Motor
  motor.write(0);
  
  // Pin Mode
  pinMode(trigpin0,OUTPUT);
  pinMode(echopin0,INPUT);
  pinMode(greenled,OUTPUT);
  pinMode(redled,OUTPUT); 
  pinMode(slot1led,OUTPUT); 
  pinMode(slot2led,OUTPUT); 
  pinMode(slot3led,OUTPUT); 


  //LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  INITIALIZING  ");
  lcd.setCursor(0,1);
  lcd.print("     SYSTEM     ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   SMART CITY   ");
  lcd.setCursor(0,1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  //lcd.clear();
}

void loop()
{  
  s.write("s");
  if(s.available() >= 0)
  {
    data = s.read();
    if(data>=0)
    {
      slots=data;
      slot3=data%10;
      data=data/10;
      slot2=data%10;
      data=data/10;
      slot1=data;
      Serial.println("Slots = "+String(slot1*100+slot2*10+slot3)); 
      avail=3-(slot1+slot2+slot3);
      //delay(1000);
      //slots=111;      //testing
      //Serial.println("Slots = "+String(slots));

      if(slot1==1)
      {
        digitalWrite(slot1led,HIGH);
        //Serial.println("slot 1");
      }
      if(slot1==0)
      {
        digitalWrite(slot1led,LOW);
      }
      if(slot2==1)
      {
        digitalWrite(slot2led,HIGH);
      }
      if(slot2==0)
      {
        digitalWrite(slot2led,LOW);
      }
      if(slot3==1)
      {
        digitalWrite(slot3led,HIGH);
      }
      if(slot3==0)
      {
        digitalWrite(slot3led,LOW);
      }
      
    }
  }
  
  //---------------->taking distance
  digitalWrite(trigpin0,LOW);  
  delay(2);
  digitalWrite(trigpin0,HIGH);
  delay(10);
  digitalWrite(trigpin0,LOW);
  duration0=pulseIn(echopin0,HIGH);
  distance0=duration0*0.034/2;
  Serial.println("Distance = "+String(distance0));

  //--------------------> MOTOR CONTROLLING
  if(distance0<=5 && distance0>=1 && slots!=111)
  {
    Serial.println("\t\t\t\t Welcome"); 
    digitalWrite(greenled,HIGH);
    digitalWrite(redled,LOW);
    
    /*
    for(angle=0;angle<105;angle+=5)    //closing gate
    {
      motor.write(angle);
      delay(5);
    }*/
    //opening gate
    motor.write(105);
    delay(2000);
    /*
    for(angle=105;angle>=0;angle-=5)      //opening gate
    {
      motor.write(angle);
      delay(5);
    }*/
   
    delay(1000);
    }
  else if(distance0>5)
  {
       motor.write(0);
       digitalWrite(greenled,LOW);
       digitalWrite(redled,LOW);
  }
  else if(distance0<=5 && distance0>=1 && slots==111)
  {
    Serial.println("\t\t Full \t\t No Free Slot Available");
    digitalWrite(redled,HIGH);
  }
  else
  {
    Serial.println(" Available Slots = "+String(avail));
    Serial.println("RARE CONDITION");
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" PARKING SYSTEM ");
  //lcd.print("DETAILS OF SLOTS");
  lcd.setCursor(0,1);
  lcd.print(" FREE SLOTS = "+String(avail)+" ");

  ///----------------------END
  delay(500);
  Serial.println();
}
