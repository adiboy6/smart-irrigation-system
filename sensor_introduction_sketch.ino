#include<SoftwareSerial.h>

intsrdata;
intprdata;
void setup() {
  // put your setup codae here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  srdata = analogRead(A0);
  prdata = map(srdata, 0, 1023, 100, 0);
  Serial.print("Sensor Data");
  Serial.print(prdata);
  delay(2000);
}