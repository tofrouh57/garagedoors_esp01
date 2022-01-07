server presents pages:
 - main with hyperlink to subpages
 - config page for network, MQTT server and topics to publish and subscribe
 - control page to display buttons to send pulses
 - info page with log data
 - firmware update page 


 program logic for preparation of web pages:
 - server.on("/", handleRootDefault)

     defines the function to be called when a client accesses the root page
 - void handleRootDefault(AsyncWebServerRequest *request){    request->send(200, "text/html", handleRoot());
        --> forwards the request to the function to prepare the HTML content and send the page to the client
 - String handleRoot()  { ......        return ptr; }
        -->  creates the HTML string 










backup:
sliders
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  <h4>Output - GPIO 5</h4>
  <label class="switch">
    	<input type="checkbox" onchange="toggleCheckbox(this)" id="5"  checked><span class="slider"></span></label>

  <h4>Output - GPIO 5</h4>
  <label class="switch">
    	<input type="checkbox" onchange="toggleCheckbox(this)" id="5"><span class="slider"></span></label>

        
        
        
        
        
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>