#include <Servo.h>
#include <ESP8266WiFi.h>
Servo servo1;
WiFiServer server(80);
const int ANGLE_HI = 75;
const int ANGLE_LO = 10;
const int DELAYS = 250;
bool servo_run;
int count = 0;
bool automated = true;

void setup() {
  servo1.attach(5);
  servo1.write(90);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("Team Fred", "10110111");
  server.begin();
  Serial.begin(115200);
  IPAddress HTTPS_ServerIP = WiFi.softAPIP();
  Serial.println();
  Serial.print("Server IP is: ");
  Serial.println(HTTPS_ServerIP);
  servo_run = false;
}

void loop() {
  WiFiClient client = server.available();
  if(client){automated = false;};
  if(automated && count < 10){
    count++;
    Serial.println(count);
  }
  else if(automated && count == 10){
    servo_run = true;
  }
  
  
  if (servo_run) { 
    
  
    servo1.write(ANGLE_HI);
    delay(DELAYS << 1);
    servo1.write(ANGLE_LO);
    delay(DELAYS);
  
  }
  
  String request = client.readString();
  Serial.println(request);
  if (request.indexOf("/GO") != -1) {
    servo_run = true;
    Serial.println("GOING!!");
  }
  else if (request.indexOf("/STOP") != -1) {
    servo_run = false;
    Serial.println("STOPPED");
  }
  else if (request.indexOf("/DBL") != -1) {
    Serial.println("DOUBLE");
    dbl();
  }
  else if (request.indexOf("/HI") != -1) {
    servo_run = false;
    Serial.println("Set HI");
    servo1.write(ANGLE_HI);
  }
  else if (request.indexOf("/LO") != -1) {
    servo_run = false;
    Serial.println("Set LO");
    servo1.write(ANGLE_LO);
  }

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Servo HI\"";
  s += " onclick=\"location.href='192.168.4.1/HI'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Servo LO\"";
  s += " onclick=\"location.href='192.168.4.1/LO'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Servo Double\"";
  s += " onclick=\"location.href='192.168.4.1/DBL'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Servo On\"";
  s += " onclick=\"location.href='192.168.4.1/GO'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Servo Off\"";
  s += " onclick=\"location.href='192.168.4.1/STOP'\">";
  s += "</html>\n";
  client.flush();
  client.print(s);

}

void dbl(){
  for(int i = 0; i < 10; i++){
    servo1.write(ANGLE_HI);
    delay(DELAYS);
    servo1.write(ANGLE_LO);
    delay((DELAYS) << 1);
  }
}



