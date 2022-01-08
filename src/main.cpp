#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#ifndef HTMLPAGES_H
#define HTMLPAGES_H
#include "htmlPages.h"
#endif

#include <FS.h>
#include <PubSubClient.h>

const char *ssid = "unifi";
const char *password = "3N3FXAI4RP";

// ESP8266
// #define GPIO_MY 16
// #define GPIO_TOF 4

// ESP01
#define GPIO_MY 0
#define GPIO_TOF 2

// extern bool pulseTof = false;
// extern bool pulseMy = false;
// extern int _tv;
int pulseTof = 0;
int pulseMy=0;


int _pulseTof = 0;
int _pulseMy = 0;

AsyncWebServer server(80);

const char *mqtt_server = "192.168.0.55";
// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient xespClient;
PubSubClient MQTTclient(xespClient);

void callback(String topic, byte *message, unsigned int length)
{
  Serial.print("MQTT Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  int _gpio;
  if ((topic == "garage/myriam") && (messageTemp == "pulse"))
  {
    Serial.println("send pulse for garage Myriam ");
    MQTTclient.publish("ESPLog/garage/pulse", "gotPulse");
        Serial.println("_pulseTof set to 1");
      pulseMy = 1;
  }

  if ((topic == "garage/christophe") && (messageTemp == "pulse"))
  {
    Serial.println("send pulse for garage christophe ");
    MQTTclient.publish("ESPLog/garage/pulse", "gotPulse");
    Serial.println("_pulseTof set to 1");
    pulseTof = 1;
  }
}

void reconnect()
{
  while (!MQTTclient.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (MQTTclient.connect("ESP8266Client"))
    {
      Serial.println("connected");
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      MQTTclient.subscribe("garage/myriam");
      MQTTclient.subscribe("garage/christophe");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void initPins()
{
  pinMode(GPIO_MY, OUTPUT);
  pinMode(GPIO_TOF, OUTPUT);
  digitalWrite(GPIO_MY, HIGH);
  digitalWrite(GPIO_TOF, HIGH);
}


wl_status_t initWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  return WiFi.status();
}


void setup(void)
{
  Serial.begin(115200);

  initPins();
  wl_status_t _wifiState = initWifi();
 // initMQTT();

  MQTTclient.setServer(mqtt_server, 1883);
  MQTTclient.setCallback(callback);

  server.onNotFound(notFound);

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  server.on("/reset", handleResetDefault);
  server.on("/config", handleConfigDefault);
  server.on("/control", handleControlDefault);
  server.on("/", handleRootDefault);

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

unsigned long pulseLength = 1000;
unsigned long millisTof = 0;
unsigned long millisMy = 0;

void loop(void)
{
  if (!MQTTclient.connected())
  {
    reconnect();
  }
  if (!MQTTclient.loop())
    MQTTclient.connect("ESP8266Client");


  if (pulseTof == 1)
  {
    Serial.println("_pulseTof set to 2");
    digitalWrite(GPIO_TOF, LOW);
    millisTof = millis();
    pulseTof = 2;
  }
  if ((pulseTof == 2) && (millis() > millisTof + pulseLength))
  {
    digitalWrite(GPIO_TOF, HIGH);
    Serial.println("_pulseTof set to 0");
    pulseTof = 0;
  }



  if (pulseMy == 1)
  {
    Serial.println("_pulseMy set to 2");
    digitalWrite(GPIO_MY, LOW);
    millisMy = millis();
    pulseMy = 2;
  }
  if ((pulseMy == 2) && (millis() > millisMy + pulseLength))
  {
    digitalWrite(GPIO_MY, HIGH);
    Serial.println("_pulseMy set to 0");
    pulseMy = 0;
  }

}
