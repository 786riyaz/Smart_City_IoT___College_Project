int PIRsensor = 8;
int LED = 13;

void setup()
{
  pinMode(PIRsensor, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = digitalRead(PIRsensor);

  if (sensorValue == 1)
  {
    Serial.print("\t"+sensorValue);
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
