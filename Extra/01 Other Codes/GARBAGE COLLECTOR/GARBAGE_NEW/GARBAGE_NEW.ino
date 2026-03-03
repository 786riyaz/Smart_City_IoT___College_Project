const int trigpin = 14;
const int echopin = 12;
const int led = D4;
long duration;
int distancein, distanceinch;

void setup()
{
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  digitalWrite(trigpin, LOW);
  delay(2);
  digitalWrite(trigpin, HIGH);
  delay(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);
  distancein = duration * 0.034 / 2;
  distanceinch = duration * 0.0133 / 2;
  
  if (distancein < 5) {
    Serial.println("Garbage Full!");
    digitalWrite(led, HIGH);
  }
  else if (distancein > 5) {
    digitalWrite(led, LOW); 

  }


}
