int data; //Initialized variable to store recieved data
int slot1,slot2,slot3;

void setup() 
{
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
}

void loop() 
{
  data = Serial.read(); //Read the serial data and store it
  Serial.println((data));
  delay(1000);
  
}
