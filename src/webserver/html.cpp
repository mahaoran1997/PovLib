#include <cstdlib>
#include <iostream>
#include<webserver/html.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

void TemplateHtml::handle_buttons() {
    if(server.hasArg()) {
        String x = server.arg("button_num");
        current_pattern_num = atoi(x);

    }
    Animation_1 = "Deactivate";
    Animation_3 = "Deactivate";
    Animation_2 = "Activate";
    Serial.println("Pattern2: ON");
    server.send(200, "text/html", SendHTML(2)); 
}

void TemplateHtml::handle_NotFound() {
    server.send(404, "text/plain", "Not found");
}


String SendHTML(uint8_t pattern_num){
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr +="<title>LED Control</title>\n";
    ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    ptr +=".button-on {background-color: #1abc9c;}\n";
    ptr +=".button-on:active {background-color: #16a085;}\n";
    ptr +=".button-off {background-color: #34495e;}\n";
    ptr +=".button-off:active {background-color: #2c3e50;}\n";
    ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    ptr +="</style>\n";
    ptr +="</head>\n";
    ptr +="<body>\n";
    ptr +="<h1>ESP8266 Web Server</h1>\n";
    ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
    
    if(pattern_num==1)
    {ptr +="<p>Pattern 1: </p><a class=\"button button-off\" href=\"/pattern1\">Activate</a>\n";}
    else
    {ptr +="<p>Pattern 1: </p><a class=\"button button-on\" href=\"/pattern1\">Activate</a>\n";}

    if(pattern_num==2)
    {ptr +="<p>Pattern 2: </p><a class=\"button button-off\" href=\"/pattern2\">Activate</a>\n";}
    else
    {ptr +="<p>Pattern 2: </p><a class=\"button button-on\" href=\"/pattern2\">Activate</a>\n";}

    if(pattern_num==3)
    {ptr +="<p>Pattern 3: </p><a class=\"button button-off\" href=\"/pattern3\">Activate</a>\n";}
    else
    {ptr +="<p>Pattern 3: </p><a class=\"button button-on\" href=\"/pattern3\">Activate</a>\n";}

    ptr +="</body>\n";
    ptr +="</html>\n";
    return ptr;
}