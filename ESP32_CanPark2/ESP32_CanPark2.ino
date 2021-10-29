
//#include <WebServer.h>
//#include <DNSServer.h>
#include <WiFi.h>
//#include <"WiFiManager.h">
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <Wire.h>
#include<String.h>

#define address 0x1E //0011110b, I2C 7bit address of HMC5883
const char* ssid = "Buffalo-G-AC73";
const char* password = "f53bfvetanik4";
 
const char* mqtt_server = "broker.mqttdashboard.com";
const int mqttPort = 1883;
const char* mqttUser = "kantan";
const char* mqttPassword = "canpark123";

WiFiClient espClient;
PubSubClient client(espClient);

StaticJsonDocument<256> doc;


void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(2000);
 
    }
  }

  
  //Initialize Serial and I2C communications  Serial.begin(115200);
  Wire.begin();

  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}
void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID or use MAC address
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("tester", "hello world");
      // ... and resubscribe
      client.subscribe("accon");
    }
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop(){


  
  int x,y,z; //triple axis data
  bool state=false;
 /*
  //Tell the HMC5883L where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission(); 
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }

  /*
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);

  if((x>=50000)&&(y>=50000))
  {
    state=true;
  }
  else{
    state=false;
  }
  doc["DeviceID"] = "ESP32";
  doc["Parked"] = state;
  doc["OTP"] = random(100000,999999);

  char buffer[256];
  serializeJson(doc, buffer);
*/
  
  Serial.println("Sending message to MQTT topic..");
  Serial.println(buffer);
 
  if (client.publish("testTopic/CanPark1", buffer) == true) {
    Serial.println("Success sending message");
  } 
  else {
    Serial.println("Error sending message");
  }
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  Serial.println("-------------");
  
  delay(250);
    
}
