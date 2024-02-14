#include<SoftwareSerial.h>

intsrdata;
intprdata;
intpump_status;
SoftwareSerialesp8266(3, 4);
#define SSID "adi"
#define PASS "123456678789"

String sendAT(String command, constint timeout) {
  String response = "";
  esp8266.print(command);
  longint time = millis();
  while ((time + timeout) > millis()) {
    while (esp8266.available()) {
      char c = esp8266.read();
      response += c;
    }
  }
  Serial.print(response);
  return response;
}
void setup() {
  // put your setup codae here, to run once:
  Serial.begin(9600);
  esp8266.begin(9600);
  sendAT("AT+RST\r\n", 2000);
  sendAT("AT\r\n", 1000);
  sendAT("AT+CWMODE=1\r\n", 1000);
  sendAT("AT+CWJAP=\"adi\",\"123456678789\"\r\n", 2000);
  while (!esp8266.find("OK")) {
    //Check until you find OK
  }
  sendAT("AT+CIFSR\r\n", 1000);
  sendAT("AT+CIPMUX=0\r\n", 1000);
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  srdata = analogRead(A0);
  prdata = map(srdata, 0, 1023, 100, 0);
  Serial.print("Sensor Data");
  Serial.print(prdata);
  String sensor_value = String(prdata);
  if (prdata < 50) {
    digitalWrite(8, LOW);
    pump_status = 100;
  } else {
    digitalWrite(8, HIGH);
    pump_status = 0;
  }
  String pump = String(pump_status);
  updateTS(sensor_value, pump);
  delay(2000);
}
voidupdateTS(String T, String P) {
  Serial.print("");
  sendAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n", 1000);
  delay(2000);
  String cmdlen;
  String cmd = "GET /update?key=1SXLYYHBH920LFW9&field1=" + T + "&field2=" + P + "\r\n";
  cmdlen = cmd.length();
  sendAT("AT+CIPSEND=" + cmdlen + "\r\n", 2000);
  esp8266.print(cmd);
  Serial.println("");
  sendAT("AT+CIPCLOSE\r\n", 2000);
  Serial.println("");
  delay(15000);
}