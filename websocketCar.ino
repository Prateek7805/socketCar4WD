#include <ESP8266WiFi.h>
#include<WebSocketsServer.h>
#include<ESP8266WebServer.h>
#include<WiFiManager.h>
#include<ESP8266HTTPUpdateServer.h>
#include<EEPROM.h>
#include "index.h"
#include "script.h"
#include "styles.h"

//pins
uint8_t motorPins[4] = {12, 13, 14, 16};
uint8_t ENA = 5;
uint8_t ENB = 4; 
uint8_t readyPin = 2;

//vars
uint16_t SPEED =0; 
bool readyFlag = 0;
byte inputFlag[4]={0,0,0,0};
byte output = 0;
byte wiFiMODE;
//consts
const uint8_t FORWARD = 0x05;
const uint8_t BACKWARD = 0x0A;
const uint8_t LEFT = 0x09;
const uint8_t RIGHT = 0x06;
const char* ssid = "socketCar";
const char* password = "1245678";

//objects
IPAddress apIP(192, 168, 4,1);  
IPAddress gateway(192, 168,12, 7);
IPAddress subnet(255, 255, 255, 0); 
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266HTTPUpdateServer httpUpdater;

void handleOtherFiles(){
  if(checkInFS(server.uri())){
    return;
  }
  server.send(404,"text.plain", "please restart the car"); 
}


bool checkInFS(String path){
  String dataType = "text/plain";
  const char* data;
  if(path.endsWith("/") || path.endsWith(".html")){
    dataType = "text/html";
    data = html;
  }else if(path.endsWith(".css")){
    dataType = "text/css";
    data = css;
  }else if(path.endsWith(".js")){
    dataType = "application/js";
    data = js;
  }else{
    return false;
  }
  server.send_P(200, dataType.c_str(), data);
  return true;
}


void setup() {
  pinMode(motorPins[0], OUTPUT);
  pinMode(motorPins[1], OUTPUT);
  pinMode(motorPins[2], OUTPUT);
  pinMode(motorPins[3], OUTPUT);
  pinMode(readyPin, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  Serial.begin(115200);
  EEPROM.begin(64);
  
  if(EEPROM.read(0) == 84){
    wiFiMODE = EEPROM.read(1);  
  }else{
    EEPROM.write(0, 84);
    EEPROM.write(1, 0);
    EEPROM.commit();
    wiFiMODE = 0;
  }
  
  WiFi.mode( WIFI_OFF );
  WiFi.forceSleepBegin();
  delay(10);
  WiFi.forceSleepWake();
  delay(10);
  if(wiFiMODE == 0){
      WiFiManager wifimanager;
      wifimanager.autoConnect(ssid);
      delay(100);
  }else{
      WiFi.config(apIP, gateway, subnet);
      WiFi.mode(WIFI_AP);
      WiFi.disconnect();
      delay(100);
        //changing softAP config and starting the Start AP
      WiFi.softAPConfig(apIP, gateway, subnet);
      WiFi.softAP(ssid, password);
  }
  
  server.on("/hello", HTTP_GET, [](){
    server.send(200, "text/plain", String(wiFiMODE));});
  server.onNotFound(handleOtherFiles);
  
  server.begin();
  webSocket.begin();
  webSocket.onEvent(socketHandle);
}

void loop() {
  webSocket.loop();
  server.handleClient();
  delay(1);
  if(!readyFlag){
    digitalWrite(readyPin, LOW);
    delay(100);
    digitalWrite(readyPin, HIGH);
    delay(100);
    digitalWrite(readyPin, LOW);
    delay(100);
    digitalWrite(readyPin, HIGH);
    readyFlag = 1;
  }
  wdt_reset();
}

void socketHandle(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    //do all stuff here
    switch(payload[0]){
      case 's':
                inputFlag[0] = 0;
                inputFlag[1] = 0;
                inputFlag[2] = 0;
                inputFlag[3] = 0;
                
                carMotion();
                break;
      case 'f':
                inputFlag[0] = (byte)(payload[1]-48);
                carMotion();
                
                break;
      case 'b': 
                inputFlag[1] = (byte)(payload[1]-48);
                carMotion();
                break;
      case 'r': 
                inputFlag[2] = (byte)(payload[1]-48);
                carMotion();
                break;
      case 'l': 
                inputFlag[3] = (byte)(payload[1]-48);
                carMotion();
                break;
      case 'v':
                SPEED = (uint16_t) strtol((const char *)&payload[1], NULL, 10);
                break;
      case 'W':
                wiFiMODE = (payload[1]-48);
                EEPROM.write(1, wiFiMODE);
                EEPROM.commit();
                ESP.restart();
  }
}
}
void carMotion(){
  delay(1);
  output = 0;
  output |= (inputFlag[0]) ?  FORWARD : 0;
  output |= (inputFlag[1]) ?  BACKWARD : 0;
  output |= (inputFlag[2]) ?  RIGHT : 0;
  output |= (inputFlag[3]) ?  LEFT : 0;
  for(int i=0; i<4; i++){
    digitalWrite(motorPins[i], (output&(1<<i))>>i); 
  } 
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED); 
}
