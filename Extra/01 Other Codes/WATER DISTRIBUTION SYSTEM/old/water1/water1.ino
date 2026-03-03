int ws = 3;
int LED = 13;

void setup()
{
  pinMode(ws, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(ws);

  if (sensorValue == 1)
  {
    Serial.print(sensorValue);
    Serial.println(" LED ON");
    digitalWrite(LED, HIGH);
    delay(200);
  }
  else
  {
    Serial.print(sensorValue);
    digitalWrite(LED, LOW);
    Serial.println(" LED OFF");
    delay(200);
  }
}
