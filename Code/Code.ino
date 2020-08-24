#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h> 
#include <StreamString.h>

#include <EEPROM.h>

int switch_status_1;
int switch_status_2;
int switch_status_3;
int switch_status_4;
int switch_status_5;
int switch_status_6;
int switch_status_7;
int switch_status_8;

int switch_address_1 = 0;
int switch_address_2 = 4;
int switch_address_3 = 8;
int switch_address_4 = 12;
int switch_address_5 = 16;
int switch_address_6 = 20;
int switch_address_7 = 24;
int switch_address_8 = 28;

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "535a5fc4-e6c7-47e1-b53f-49f614298fad" // Your API Key is displayed on sinric.com dashboard
#define MySSID "X-men trainee" // Change to your Wifi network SSID
#define MyWifiPassword "Qwertyuiop69" // Change to your Wifi network password

#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 

#define a D1
#define b D2
#define c D3
#define d D4
#define e D5
#define f D6
#define g D7
#define h D8

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

void setPowerStateOnServer(String deviceId, String value);
void setTargetTemperatureOnServer(String deviceId, String value, String scale);

// deviceId is the ID assgined to your smart-home-device in sinric.com dashboard. Copy it from dashboard and paste it here

void turnOn(String deviceId) {
 if (deviceId == "5c2e71f3e520ad6f0117147d") // Device ID of first device
   {  
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(a,LOW);
     Serial.println("Switch 1 ON");
          // Serial.print("Value : ");
           //Serial.println(a);
      EEPROM_Write(1, switch_address_1 );
     
   }
   if (deviceId == "5c2e7202e520ad6f0117147f") // Device ID of second device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(b,LOW);
     Serial.println("Switch 2 ON");
           //Serial.print("Value : ");
           //Serial.println(b);
     EEPROM_Write(1, switch_address_2 );
  }
   if (deviceId == "5c2e720fe520ad6f01171481") // Device ID of third device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(c,LOW);
     Serial.println("Switch 3 ON");
            //Serial.print("Value : ");
            //Serial.println(c);
     EEPROM_Write(1, switch_address_3 );
  }
   if (deviceId == "5c2e721ee520ad6f01171483") // Device ID of fourth device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(d,LOW);
     Serial.println("Switch 4 ON");
            //Serial.print("Value : ");
            //Serial.println(d);
     EEPROM_Write(1, switch_address_4 );
       
  }
   if (deviceId == "5c2e722de520ad6f01171485") // Device ID of fifth device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(e,LOW);
     Serial.println("Switch 5 ON");
            //Serial.print("Value : ");
            //Serial.println(e);
     EEPROM_Write(1, switch_address_5 );
  }
   if (deviceId == "5c2e7239e520ad6f01171487") // Device ID of sixth device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(f,LOW);
     Serial.println("Switch 6 ON");
            //Serial.print("Value : ");
            //Serial.println(f);
     EEPROM_Write(1, switch_address_6 );
  }
   if (deviceId == "5c2e7247e520ad6f01171489") // Device ID of seventh device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(g,LOW);
     Serial.println("Switch 7 ON");
            //Serial.print("Value : ");
            //Serial.println(g);
    EEPROM_Write(1, switch_address_7 );
  }
   if (deviceId == "5c2e7252e520ad6f0117148b") // Device ID of eighth device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(h,LOW);
     Serial.println("Switch 8 ON");
            //Serial.print("Value : ");
            //Serial.println(h);
     EEPROM_Write(1, switch_address_8 );
  }
  else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);    
  }     
}

void turnOff(String deviceId) {
   if (deviceId == "5c2e71f3e520ad6f0117147d") // Device ID of first device
   {  
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(a,HIGH);
     Serial.println("Switch 1 OFF");
            //Serial.print("Value : ");
            //Serial.println(a);
     EEPROM_Write(0, switch_address_1 );
   }
   if (deviceId == "5c2e7202e520ad6f0117147f") // Device ID of second device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(b,HIGH);
     Serial.println("Switch 2 OFF");
            //Serial.print("Value : ");
            //Serial.println(b);
     EEPROM_Write(0, switch_address_2 );
  }
   if (deviceId == "5c2e720fe520ad6f01171481") // Device ID of third device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(c,HIGH);
     Serial.println("Switch 3 OFF");
            //Serial.print("Value : ");
            //Serial.println(c);
     EEPROM_Write(0, switch_address_3 );
  }
   if (deviceId == "5c2e721ee520ad6f01171483") // Device ID of fourth device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(d,HIGH);
     Serial.println("Switch 4 OFF");
            //Serial.print("Value : ");
            //Serial.println(d);
     EEPROM_Write(0, switch_address_4 );
  }
   if (deviceId == "5c2e722de520ad6f01171485") // Device ID of fifth device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(e,HIGH);
     Serial.println("Switch 5 OFF");
            //Serial.print("Value : ");
            //Serial.println(e);
     EEPROM_Write(0, switch_address_5 );
  }
   if (deviceId == "5c2e7239e520ad6f01171487") // Device ID of sixth device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(f,HIGH);
     Serial.println("Switch 6 OFF");
            //Serial.print("Value : ");
            //Serial.println(f);
     EEPROM_Write(0, switch_address_6 );
  }
   if (deviceId == "5c2e7247e520ad6f01171489") // Device ID of seventh device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(g,HIGH);
     Serial.println("Switch 7 OFF");
            //Serial.print("Value : ");
            //Serial.println(g);
     EEPROM_Write(0, switch_address_7 );
  }
  if (deviceId == "5c2e7252e520ad6f0117148b") // Device ID of eighth device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(h,HIGH);
     Serial.println("Switch 8 OFF");
            //Serial.print("Value : ");
            //Serial.println(h);
     EEPROM_Write(0, switch_address_8 );
  }
  else {
     Serial.print("Turn off for unknown device id: ");
     Serial.println(deviceId);    
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      isConnected = false;    
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
      isConnected = true;
      Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
      Serial.printf("Waiting for commands from sinric.com ...\n");        
      }
      break;
    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);
        // Example payloads

        // For Switch or Light device types
        // {"deviceId": xxxx, "action": "setPowerState", value: "ON"} // https://developer.amazon.com/docs/device-apis/alexa-powercontroller.html

        // For Light device type
        // Look at the light example in github
          
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload); 
        String deviceId = json ["deviceId"];     
        String action = json ["action"];
        
        if(action == "setPowerState") { // Switch or Light
            String value = json ["value"];
            if(value == "ON") {
                turnOn(deviceId);
            } else {
                turnOff(deviceId);
            }
        }
        else if (action == "SetTargetTemperature") {
            String deviceId = json ["deviceId"];     
            String action = json ["action"];
            String value = json ["value"];
        }
        else if (action == "test") {
            Serial.println("[WSc] received test command from sinric.com");
        }
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);

  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(h,OUTPUT);
  
  Switch_Status();
  
  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);  

  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if(WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // server address, port and URL
  webSocket.begin("iot.sinric.com", 80, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  
  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
}

void loop() {
  webSocket.loop();
  
  if(isConnected) {
      uint64_t now = millis();
      
      // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
      }
  }   
}

// If you are going to use a push button to on/off the switch manually, use this function to update the status on the server
// so it will reflect on Alexa app.
// eg: setPowerStateOnServer("deviceid", "ON")

// Call ONLY If status changed. DO NOT CALL THIS IN loop() and overload the server. 

void setPowerStateOnServer(String deviceId, String value) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["deviceId"] = deviceId;
  root["action"] = "setPowerState";
  root["value"] = value;
  StreamString databuf;
  root.printTo(databuf);
  
  webSocket.sendTXT(databuf);
}

//eg: setPowerStateOnServer("deviceid", "CELSIUS", "25.0")

// Call ONLY If status changed. DO NOT CALL THIS IN loop() and overload the server. 

void setTargetTemperatureOnServer(String deviceId, String value, String scale) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["action"] = "SetTargetTemperature";
  root["deviceId"] = deviceId;
  
  JsonObject& valueObj = root.createNestedObject("value");
  JsonObject& targetSetpoint = valueObj.createNestedObject("targetSetpoint");
  targetSetpoint["value"] = value;
  targetSetpoint["scale"] = scale;
   
  StreamString databuf;
  root.printTo(databuf);
  
  webSocket.sendTXT(databuf);
}
void EEPROM_Write(int pin_status, int switch_address)
{
  int a=pin_status;
  int eeAddress = switch_address;
  EEPROM.put(eeAddress, a);
  eeAddress += sizeof(int);

  EEPROM.put(eeAddress, a);
  Serial.println("Written");
  EEPROM.commit();
}

int EEPROM_Read(int address)
{
  int status_x;
  int eeAddress = address;
  EEPROM.get(eeAddress, status_x);
  EEPROM.commit();
  return status_x;
}
void Switch_Status()
{

 switch_status_1 = EEPROM_Read(switch_address_1);
 Serial.print("Switch Status: ");
 Serial.println(switch_status_1);
   
 switch_status_2 = EEPROM_Read(switch_address_2);
 Serial.print("Switch Status: ");
 Serial.println(switch_status_2);

 switch_status_3 = EEPROM_Read(switch_address_3);
 Serial.print("Switch Status: ");
 Serial.println(switch_status_3);

 switch_status_4 = EEPROM_Read(switch_address_4);
 Serial.print("Switch Status: ");
 Serial.println(switch_status_4);

 switch_status_5 = EEPROM_Read(switch_address_5);
 Serial.print("Switch Status: ");
 Serial.println(switch_status_5);

 switch_status_6 = EEPROM_Read(switch_address_6);
 Serial.print("Switch Status: ");
 Serial.println(switch_status_6);

 switch_status_7 = EEPROM_Read(switch_address_7);
 Serial.print("Switch Status: ");
 Serial.println(switch_status_7);

 switch_status_8 = EEPROM_Read(switch_address_8);
 Serial.print("Switch Status: ");
 Serial.println(switch_status_8);

 if(switch_status_1==1)
 {
  digitalWrite(a, LOW);
  Serial.println("Switch 1 is ON");
 } 
 else if(switch_status_1==0)
 {
   digitalWrite(a, HIGH);
   Serial.println("Switch 1 is OFF");
 }

 if(switch_status_2==1)
 {
  digitalWrite(b, LOW);
  Serial.println("Switch 2 is ON");
 } 
 else if(switch_status_2==0)
 {
   digitalWrite(b, HIGH);
   Serial.println("Switch 2 is OFF");
 }

 if(switch_status_3==1)
 {
  digitalWrite(c, LOW);
  Serial.println("Switch 3 is ON");
 } 
 else if(switch_status_3==0)
 {
   digitalWrite(c, HIGH);
   Serial.println("Switch 3 is OFF");
 }

 if(switch_status_4==1)
 {
  digitalWrite(d, LOW);
  Serial.println("Switch 4 is ON");
 } 
 else if(switch_status_4==0)
 {
   digitalWrite(d, HIGH);
   Serial.println("Switch 4 is OFF");
 }

 if(switch_status_5==1)
 {
  digitalWrite(e, LOW);
  Serial.println("Switch 5 is ON");
 } 
 else if(switch_status_5==0)
 {
   digitalWrite(e, HIGH);
   Serial.println("Switch 5 is OFF");
 }


 if(switch_status_6==1)
 {
  digitalWrite(f, LOW);
  Serial.println("Switch 6 is ON");
 } 
 else if(switch_status_6==0)
 {
   digitalWrite(f, HIGH);
   Serial.println("Switch 6 is OFF");
 }

 if(switch_status_7==1)
 {
  digitalWrite(g, LOW);
  Serial.println("Switch 7 is ON");
 } 
 else if(switch_status_7==0)
 {
   digitalWrite(g, HIGH);
   Serial.println("Switch 7 is OFF");
 }

 if(switch_status_8==1)
 {
  digitalWrite(h, LOW);
  Serial.println("Switch 8 is ON");
 } 
 else if(switch_status_8==0)
 {
   digitalWrite(h, HIGH);
   Serial.println("Switch 8 is OFF");
 }
  
}
