#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
 
#define AWS_IOT_SUBSCRIBE_TOPIC1 "esp32/load1"
#define AWS_IOT_SUBSCRIBE_TOPIC2 "esp32/load2"
#define AWS_IOT_SUBSCRIBE_TOPIC3 "esp32/load3"
#define AWS_IOT_SUBSCRIBE_TOPIC4 "esp32/load4"
 
#define load1 19
#define load2 21
#define load3 22
#define load4 23
 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
 
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
/*##################### Lamp 1 #####################*/
  if ( strstr(topic, "esp32/load1") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay1 = doc["status"];
    int r1 = Relay1.toInt();
    if(r1==1)
    {
      digitalWrite(load1, HIGH);
      Serial.print("load1 is ON");
    }
    else if(r1==0)
    {
      digitalWrite(load1, LOW);
      Serial.print("load1 is OFF");
    }
  }
 
/*##################### Lamp 2 #####################*/
  if ( strstr(topic, "esp32/load2") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay2 = doc["status"];
    int r2 = Relay2.toInt();
    if(r2==1)
    {
      digitalWrite(load2, HIGH);
      Serial.print("load2 is ON");
    }
    else if(r2==0)
    {
      digitalWrite(load2, LOW);
      Serial.print("load2 is OFF");
    }
  }
 
/*##################### Lamp 3 #####################*/
  if ( strstr(topic, "esp32/load3") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay3 = doc["status"];
    int r3 = Relay3.toInt();
    if(r3==1)
    {
      digitalWrite(load3, HIGH);
      Serial.print("load3 is ON");
    }
    else if(r3==0)
    {
      digitalWrite(load3, LOW);
      Serial.print("load3 is OFF");
    }
  }
 
/*##################### Lamp 4 #####################*/
  if ( strstr(topic, "esp32/load4") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay4 = doc["status"];
    int r4 = Relay4.toInt();
    if(r4==1)
    {
      digitalWrite(load4, HIGH);
      Serial.print("load4 is ON");
    }
    else if(r4==0)
    {
      digitalWrite(load4, LOW);
      Serial.print("load4 is OFF");
    }
  }
  Serial.println();
}
 
 
void setup()
{
  Serial.begin(115200);
  
  pinMode (load1, OUTPUT);
  pinMode (load2, OUTPUT);
  pinMode (load3, OUTPUT);
  pinMode (load4, OUTPUT);
 
  digitalWrite(load1, LOW);
  digitalWrite(load2, LOW);
  digitalWrite(load3, LOW);
  digitalWrite(load4, LOW);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC1);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC2);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC3);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC4);
 
  Serial.println("AWS IoT Connected!");
}
 
 
void loop()
{
  client.loop();
  delay(1000);
}
