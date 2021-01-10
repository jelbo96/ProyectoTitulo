#define RED 5

void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  digitalWrite(RED,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RED,HIGH);
  delay(1000);
  digitalWrite(RED,LOW);
  delay(1000);
}
