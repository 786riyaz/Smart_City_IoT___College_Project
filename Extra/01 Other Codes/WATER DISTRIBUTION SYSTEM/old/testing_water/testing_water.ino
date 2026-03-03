

void setup() {
  // put your setup code here, to run once:
  pinMode(12,INPUT);
  pinMode(11,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(8,INPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  Serial.println("Program Start");
}

void loop() {
  // put your main code here, to run repeatedly
  
  int P12=digitalRead(12);
  int P11=digitalRead(11);
  int P10=digitalRead(10);
  int P9=digitalRead(9);
  int P8=digitalRead(8);

  Serial.print(P12);
  Serial.print(P11);
  Serial.print(P10);
  Serial.print(P9);
  Serial.print(P8);
  Serial.println();
  delay(200);
}
