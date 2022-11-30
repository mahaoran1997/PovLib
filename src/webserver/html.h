#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WiFiServer {
  

};

class TemplateHtml {
private:
    int button_num;
    String* texts;
    const char* ssid;
    const char* passwd;
    int current_pattern_num;
    int* output_pattern_addr;
    ESP8266WebServer server;
public:
    TemplateHtml(int _button_num, String* _texts, const char* _ssid, const char* _passwd, int* _output_pattern_addr):button_num(_button_num), texts(_texts), ssid(_ssid), passwd(_passwd), current_pattern_num(0), output_pattern_addr(_output_pattern_addr), server(80) {
        WiFi.softAP(ssid, passwd);
        delay(300);
        server.on("/", this->handle_OnConnect);
        server.on("/button", this->handle_buttons);
        server.onNotFound(this->handle_NotFound);
        server.begin();
        Serial.println("HTTP server started");
    }
    
    void handle_OnConnect();
    void handle_buttons();
    void handle_NotFound();

    String SendHTML(uint8_t pattern_num);

};