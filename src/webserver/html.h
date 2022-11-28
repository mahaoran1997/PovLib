#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WiFiServer {
  

};


class TemplateHtml {
private:
    int button_num;
    String* suffices;
    String* texts;
    String ssid;
    String passwd;
    int current_pattern_num;
    ESP8266WebServer server;
public:
    TemplateHtml(int _button_num, String* _suffices, String* _texts, _ssid, _passwd):button_num(_button_num), suffices(_suffices), texts(_texts), ssid(_ssid), passwd(_passwd), current_pattern_num(0), server(80) {
        WiFi.softAP(ssid, password);
        delay(300);
        server.on("/", this.handle_OnConnect);
        server.on("/button", this.handle_buttons);
        server.onNotFound(this.handle_NotFound);
    }
    
    void handle_OnConnect();
    void handle_buttons();
    void handle_NotFound();

    String SendHTML(uint8_t pattern_num);

};