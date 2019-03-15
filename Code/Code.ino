#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h> 
#include <StreamString.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "Your Api Key Here" // Your API Key is displayed on sinric.com dashboard
#define MySSID "Your Wifi SSID here" // Change to your Wifi network SSID
#define MyWifiPassword "Your Wifi password here" // Change to your Wifi network password

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
   }
   if (deviceId == "5c2e7202e520ad6f0117147f") // Device ID of second device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(b,LOW);
     Serial.println("Switch 2 ON");
           //Serial.print("Value : ");
           //Serial.println(b);
  }
   if (deviceId == "5c2e720fe520ad6f01171481") // Device ID of third device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(c,LOW);
     Serial.println("Switch 3 ON");
            //Serial.print("Value : ");
            //Serial.println(c);
  }
   if (deviceId == "5c2e721ee520ad6f01171483") // Device ID of fourth device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(d,LOW);
     Serial.println("Switch 4 ON");
            //Serial.print("Value : ");
            //Serial.println(d);
  }
   if (deviceId == "5c2e722de520ad6f01171485") // Device ID of fifth device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(e,LOW);
     Serial.println("Switch 5 ON");
            //Serial.print("Value : ");
            //Serial.println(e);
  }
   if (deviceId == "5c2e7239e520ad6f01171487") // Device ID of sixth device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(f,LOW);
     Serial.println("Switch 6 ON");
            //Serial.print("Value : ");
            //Serial.println(f);
  }
   if (deviceId == "5c2e7247e520ad6f01171489") // Device ID of seventh device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(g,LOW);
     Serial.println("Switch 7 ON");
            //Serial.print("Value : ");
            //Serial.println(g);
  }
   if (deviceId == "5c2e7252e520ad6f0117148b") // Device ID of eighth device
   { 
     Serial.print("Turn on Device ID: ");
     Serial.println(deviceId);
     digitalWrite(h,LOW);
     Serial.println("Switch 8 ON");
            //Serial.print("Value : ");
            //Serial.println(h);
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
   }
   if (deviceId == "5c2e7202e520ad6f0117147f") // Device ID of second device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(b,HIGH);
     Serial.println("Switch 2 OFF");
            //Serial.print("Value : ");
            //Serial.println(b);
  }
   if (deviceId == "5c2e720fe520ad6f01171481") // Device ID of third device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(c,HIGH);
     Serial.println("Switch 3 OFF");
            //Serial.print("Value : ");
            //Serial.println(c);
  }
   if (deviceId == "5c2e721ee520ad6f01171483") // Device ID of fourth device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(d,HIGH);
     Serial.println("Switch 4 OFF");
            //Serial.print("Value : ");
            //Serial.println(d);
  }
   if (deviceId == "5c2e722de520ad6f01171485") // Device ID of fifth device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(e,HIGH);
     Serial.println("Switch 5 OFF");
            //Serial.print("Value : ");
            //Serial.println(e);
  }
   if (deviceId == "5c2e7239e520ad6f01171487") // Device ID of sixth device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(f,HIGH);
     Serial.println("Switch 6 OFF");
            //Serial.print("Value : ");
            //Serial.println(f);
  }
   if (deviceId == "5c2e7247e520ad6f01171489") // Device ID of seventh device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(g,HIGH);
     Serial.println("Switch 7 OFF");
            //Serial.print("Value : ");
            //Serial.println(g);
  }
  if (deviceId == "5c2e7252e520ad6f0117148b") // Device ID of eighth device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(h,HIGH);
     Serial.println("Switch 8 OFF");
            //Serial.print("Value : ");
            //Serial.println(h);
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
  Serial.begin(115200);

  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(h,OUTPUT);
  
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(h,HIGH);
  
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
