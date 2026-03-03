#include<SoftwareSerial.h>
SoftwareSerial s(13,2); // RX TX

int waterlevel = 0;
int level_10 = 3;
int level_20 = 4;
int level_30 = 5;
int level_40 = 6;
int level_50 = 7;
int led1=8;
int led2=9;
int led3=10;
int led4=11;
int led5=12;

void setup()
{ 
  s.begin(9600);
  Serial.begin(19200);
  pinMode(level_10, INPUT);
  pinMode(level_20, INPUT);
  pinMode(level_30, INPUT);
  pinMode(level_40, INPUT);
  pinMode(level_50, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop()
{  
  int L10 = digitalRead(level_10);
  int L20 = digitalRead(level_20);
  int L30 = digitalRead(level_30);
  int L40 = digitalRead(level_40);
  int L50 = digitalRead(level_50);

 Serial.print(" "+String(L10));
 Serial.print(" "+String(L20));
 Serial.print(" "+String(L30));
 Serial.print(" "+String(L40));
 Serial.println(" "+String(L50));
 
  if (L10 == 1)
  {
    waterlevel = 1;
    if (L20 == HIGH)
    {
      waterlevel = 2;
      if (L30 == HIGH)
      {
        waterlevel = 3;
        if (L40 == HIGH)
        {
          waterlevel = 4;
          if (L50 == HIGH)
          {
            waterlevel = 5;
          }
        }
      }
    }
  }
  else
  {
    waterlevel = 0;
  }
  if(waterlevel == 0)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
  }
  else if(waterlevel == 1)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
  }
   else if(waterlevel == 2)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
  }
  else if(waterlevel == 3)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
  }
   else if(waterlevel == 4)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    digitalWrite(led5,LOW);
  }
  else if(waterlevel == 5)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    digitalWrite(led5,HIGH);
  }
  
  if(s.available() > 0)
  {
    //char c = s.read();
    s.write(waterlevel);
    Serial.print("-->");
  }
  ///////////////////////////////////
  Serial.println("Level = "+String(waterlevel)+"\n");
  delay(1000*2);
}
