#include <cstdlib>
#include <iostream>
#include <sstream>
#include <FastLED.h>
#include <html.h>

using namespace std;

int TemplateHtml::button_num = 0;
String* TemplateHtml::texts = NULL;
const char* TemplateHtml::ssid = NULL;
const char* TemplateHtml::passwd = NULL;
int TemplateHtml::current_pattern_num = 0;
int* TemplateHtml::output_pattern_addr = NULL;
ESP8266WebServer TemplateHtml::server(80);


void TemplateHtml::handle_OnConnect() {
  *output_pattern_addr = 0;
  current_pattern_num = 0;
  Serial.println("All patterns: OFF");
  server.send(200, "text/html", SendHTML(0)); 
}


void TemplateHtml::handle_buttons() {
    if(server.hasArg("button_num")) {
        String x = server.arg("button_num");
        stringstream ss;
        ss << x.c_str();
        ss >> current_pattern_num;
    }
    *output_pattern_addr = current_pattern_num;
    String p = "Pattern ";

    string s;
    stringstream ss;
    ss << current_pattern_num;
    ss >> s;

    p += s.c_str();
    p += ": ON";
    Serial.println(p.c_str());
    server.send(200, "text/html", TemplateHtml::SendHTML(current_pattern_num)); 

    Serial.println("HTML Sent");
}

void TemplateHtml::handle_NotFound() {
    server.send(404, "text/plain", "Not found");
}

void TemplateHtml::handle_client() {
    server.handleClient();
}


String TemplateHtml::SendHTML(uint8_t pattern_num){
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
    

    for (int i = 1; i <= button_num; i ++) {
        string s;
        stringstream ss;
        ss << i;
        ss >> s;

        if(i == current_pattern_num) {
            ptr +="<p>";
            ptr += texts[i];
            ptr += ": </p><a class=\"button button-off\" href=\"/pattern?button_num=";
            ptr += s.c_str();
            ptr += "\">Activate</a>\n";
        }
        else {
            ptr +="<p>";
            ptr += texts[i];
            ptr += ": </p><a class=\"button button-on\" href=\"/pattern?button_num=";
            ptr += s.c_str();
            ptr += "\">Activate</a>\n";
        }

    }
    ptr +="</body>\n";
    ptr +="</html>\n";
    return ptr;
}
