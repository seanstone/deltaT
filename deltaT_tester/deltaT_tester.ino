void setup()
{
  Serial.begin(9600); 
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  reset();
  delay(2000);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  delay(1000);
}

void reset()
{
  digitalWrite(8, HIGH);
  delayMicroseconds(500);
  digitalWrite(9, HIGH);
}

