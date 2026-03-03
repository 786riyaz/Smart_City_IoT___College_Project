int motor = 13;
int level_10 = 8;
int level_30 = 9;
int level_50 = 10;
int level_70 = 11;
int level_90 = 12;
int previous=0;
int current=0;

void setup() {
  pinMode(level_10, INPUT);
  pinMode(level_30, INPUT);
  pinMode(level_50, INPUT);
  pinMode(level_70,INPUT);
  pinMode(level_90, INPUT);

  Serial.begin(9600);
  Serial.println("Program Start");
}

void loop() {
  int L10 = digitalRead(level_10);
  int L30 = digitalRead(level_30);
  int L50 = digitalRead(level_50);
  int L70 = digitalRead(level_70);
  int L90 = digitalRead(level_90);
  /*
  Serial.print(L10);
  Serial.print(" ");
  Serial.print(L30);
  Serial.print(" ");
  Serial.print(L50);
  Serial.print(" ");
  Serial.print(L70);
  Serial.print(" ");
  Serial.print(L90);
  Serial.println("");
  */
  //L 10 30 50 70 90
  if (L90==LOW && L70==LOW && L50==LOW && L30==LOW && L10==LOW) 
  {
    current=90;
    if(previous!=current){
    Serial.println("TANK LEVEL = 90% \t Motor OFF");
    digitalWrite(motor,LOW);
    previous=current;}
  }
  else if (L90==HIGH && L70==LOW && L50==LOW && L30==LOW && L10==LOW) 
  {
    current=70;
    if(previous!=current){
    Serial.println("TANK LEVEL = 70%");
    previous=current;}
  }
  else if (L90==HIGH && L70==HIGH && L50==LOW && L30==LOW && L10==LOW) 
  {
    current=50;
    if(previous!=current){
    Serial.println("TANK LEVEL = 50%");
    previous=current;}
  }
  else if (L90==HIGH && L70==HIGH && L50==HIGH && L30==LOW && L10==LOW) 
  {
    current=30;
    if(previous!=current){
    Serial.println("TANK LEVEL = 30%");
    previous=current;}
  }
  else if (L90==HIGH && L70==HIGH && L50==HIGH && L30==HIGH && L10==LOW) 
  {
    current=10;
    if(previous!=current){
    Serial.println("TANK LEVEL = 10% \t Motor ON");
    digitalWrite(motor,HIGH);
    previous=current;}
  }
  else if(L90==HIGH && L70==HIGH && L50==HIGH && L30==HIGH && L10==HIGH)
  {
    current=0;
    if(previous!=current){
    Serial.println("TANK IS EMPTY \t\t Motor ON");
    digitalWrite(motor,HIGH);
    previous=current;}
  }
  //else
  //{Serial.println("Previous Level");}
  
  delay(500);
}
