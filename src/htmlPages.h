#include <ESPAsyncWebServer.h>




void writeFile(fs::FS &fs, const char *path, const char *message);
String readFile(fs::FS &fs, const char *path);

void handleRootDefault(AsyncWebServerRequest *request);
String handleRoot();
void handleConfigDefault(AsyncWebServerRequest *request);
String handleConfig();
void handleControlDefault(AsyncWebServerRequest *request);
String handleConfig();

void notFound(AsyncWebServerRequest *request);
void handleResetDefault(AsyncWebServerRequest *request);
