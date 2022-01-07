#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "htmlPages.h"
#include <FS.h>

const char *ssid = "unifi";
const char *password = "3N3FXAI4RP";

AsyncWebServer server(80);




void setup(void)
{
  Serial.begin(115200);
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

void loop(void)
{
}
