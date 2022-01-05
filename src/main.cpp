
/*Serial.println(millis());
Serial.println(ESP.getChipId());
Serial.println(ESP.getCpuFreqMHz());
Serial.println(ESP.getCycleCount());
Serial.println(ESP.getFlashChipId());
Serial.println(ESP.getFlashChipMode());
Serial.println(ESP.getFlashChipRealSize());
Serial.println(ESP.getFlashChipSize());
Serial.println(ESP.getFlashChipSizeByChipId());
Serial.println(ESP.getFlashChipSpeed());
Serial.println(ESP.getFlashChipVendorId());
Serial.println(ESP.getFullVersion());
delay(5000);
*/

/*
  Rui Santos
  Complete project details
   - Arduino IDE: https://RandomNerdTutorials.com/esp8266-nodemcu-ota-over-the-air-arduino/
   - VS Code: https://RandomNerdTutorials.com/esp8266-nodemcu-ota-over-the-air-vs-code/
     
  This sketch shows a Basic example from the AsyncElegantOTA library: ESP8266_Async_Demo
  https://github.com/ayushsharma82/AsyncElegantOTA
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

const char* ssid = "unifi";
const char* password = "3N3FXAI4RP";

AsyncWebServer server(80);

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP8266.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

/*
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
Serial.println("Firmware updated");
*/


}

void loop(void) {
}