
#include "htmlPages.h"
#include <FS.h>

void writeFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if (!file)
  {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("- file written");
  }
  else
  {
    Serial.println("- write failed");
  }
  file.close();
}
String readFile(fs::FS &fs, const char *path)
{
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if (!file || file.isDirectory())
  {
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while (file.available())
  {
    fileContent += String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

String handleRoot()
{
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  String ptr = R"rawliteral(<!DOCTYPE HTML><html><head>
                 <h1 style = "text-align: center;" > Garage door controller</h1>
                              <p></p>
                              <p></p>
                              <p style = "text-align: center;"><a href = "/control" title = "Control doors"> Control doors</a></p>
                              <p style = "text-align: center;"><a href = "/config"> Network config page</a></p>
                              <p style = "text-align: center;"><a href = "/logs"> View logs</a></p>
                              <p style = "text-align: center;"><a href = "/update"> Update firmware</a></p>
                              <p style = "text-align: center;"><a href = "/reset"> Reset Parameters</a></p>
                              <p></p>
                              <p></p>
                              <p></p>
                              <p></p>
                              <p> Uptime : )rawliteral";

  ptr += hr;
  ptr += ":";
  ptr += min;
  ptr += ":";
  ptr += sec;
  ptr += "</p></html>";
  return ptr;
}
void handleRootDefault(AsyncWebServerRequest *request)
{
  Serial.println(request->methodToString());
  request->send(200, "text/html", handleRoot());
}

String handleConfig()
{
  //  writeFile(SPIFFS, "/mqtt", "1234567");
  //  String yourInputString = readFile(SPIFFS, "/mqtt");

  String ptr = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
<h1>The form method="get" attribute</h1>
<form action="/config" >
  <label for="mqttServer">MQTT Server IP:</label>
  <input type="text" id="mqttServer" name="mqttServer" value=")rawliteral";
  ptr += readFile(SPIFFS, "/mqttServer");
  ptr += R"rawliteral(
  "><br><br>
  <label for="pTopic">Topic to publish:</label>
  <input type="text" id="pTopic" name="pTopic" value=")rawliteral";
  ptr += readFile(SPIFFS, "/pTopic");
  ptr += R"rawliteral(
   "><br><br>
  <label for="sTopic">Topic to subscribe:</label>
  <input type="text" id="sTopic" name="sTopic" value=")rawliteral";
  ptr += readFile(SPIFFS, "/sTopic");
  ptr += R"rawliteral(
  "><br><br>
  <input type="submit" value="Submit">
</form>
<p>Click on the submit button, and the input will be sent to a page on the server called "action_page.php".</p>
<p></p>
<p></p>
<p></p>
<form action="/"><input type="submit" value="Go to Menu" /></form>
</body>
</html>)rawliteral";

  return ptr;
}
void handleConfigDefault(AsyncWebServerRequest *request)
{
  Serial.print("in handleConfigDefault amount params : ");
  Serial.println(request->params());
  if (request->params() > 0)
    { 
       writeFile(SPIFFS, "/mqttServer", request->getParam("mqttServer")->value().c_str());
       writeFile(SPIFFS, "/pTopic", request->getParam("pTopic")->value().c_str());
       writeFile(SPIFFS, "/sTopic", request->getParam("sTopic")->value().c_str());
    }
  request->send(200, "text/html", handleConfig());
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

//When you submit a GET form, the query string is removed from the action and a new one is generated from the data in the form.
//You need to store the data in hidden inputs.

String handleControl()
{
  String ptr = R"rawliteral(
    <!DOCTYPE html>
<html>
<body>
<h1>Control garage doors</h1>
<p></p>
<h3>Myriam's side</h3>

<form action="/control">
     <input type="hidden"
            name="door"
            value="myriam">
     <input type="submit" 
            value="Myriam">
</form>


<p></p>
<p></p>
<h3>Christophe's side</h3>
<form action="/control">
     <input type="hidden"
            name="door"
            value="christophe">
     <input type="submit" 
            value="Christophe">
</form>
<p></p>
<p></p>
<form action="/"><input type="submit" value="Go to Menu" /></form>
</body>
</html>
)rawliteral";

  return ptr;
}

void handleControlDefault(AsyncWebServerRequest *request)
{
  Serial.print("in handleControlDefault amount params : ");
  Serial.println(request->params());
  if (request->params() > 0)
    { 
       if (request->getParam("door")->value() == "christophe") 
       {
         Serial.println("pulse for Chris door");
         // _gpio = GPIO_PIN_TOF 
       }
       if (request->getParam("door")->value() == "myriam") 
       {
         Serial.println("pulse for Myriam door");
         // _gpio = GPIO_PIN_MY
       }

         unsigned long _millis = millis();
         // set _gpio High
        do
        {
        } while (millis() < _millis + 500);
         // set _gpio
    }
  request->send(200, "text/html", handleControl());
}

void handleResetDefault(AsyncWebServerRequest *request)
{
       writeFile(SPIFFS, "/mqttServer", "XXX.XXX.XXX.XXX");
       writeFile(SPIFFS, "/pTopic", "garagedoors/publishTopic/");
       writeFile(SPIFFS, "/sTopic", "garagedoor/subscribeTopic/");
  request->send(200, "text/plain", "parameters reset to default done !!");
}

