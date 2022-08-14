// frequency meter 
//https://github.com/ObukhovAV/frequency-meter-ESP8266

#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>

#define LED 2 // GPIO2
#define input_ttl 4 // GPIO4

uint32 tm;
uint32 tm_dlt;
int inp_ttl;
int frc;

const char* ssid = "***"; //Enter SSID
const char* password = "***"; //Enter Password

ESP8266WebServer server(80);
String webPage = "";

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  //pinMode(input_ttl, INPUT);
  pinMode(input_ttl, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  
    delay(200);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED,LOW);
  }
  digitalWrite(LED, HIGH);
Serial.println(WiFi.localIP());
digitalWrite(LED, HIGH);
server.on("/", [](){  server.send(200, "text/html", webPage);});
server.begin();
}

void loop() {
 while (inp_ttl == 1)    
    inp_ttl = digitalRead(input_ttl);
 while (inp_ttl == 0)    
   inp_ttl = digitalRead(input_ttl);
  digitalWrite(LED,LOW);
tm = micros();

for(int i=0; i<100; i++)
{
  while (inp_ttl == 1)    
    inp_ttl = digitalRead(input_ttl);
  while (inp_ttl == 0)    
   inp_ttl = digitalRead(input_ttl); 
}
tm_dlt =  micros() - tm;
 frc = 100000000/tm_dlt;
 digitalWrite(LED, HIGH);
  delay(500);
  webPage = "<meta http-equiv='Refresh' content='1' /><h1> ESP8266 frequency meter </h1><p>fr = "+String(frc)+" Hz</p>";
server.handleClient();
 }
