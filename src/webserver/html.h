#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


class TemplateHtml {
private:
    static int button_num;
    static String* texts;
    static const char* ssid;
    static const char* passwd;
    static int current_pattern_num;
    static int* output_pattern_addr;
    static ESP8266WebServer server;
public:

    static void handle_OnConnect();
    static void handle_buttons();
    static void handle_NotFound();
    static void handle_client();

    static void initialize(int _button_num, String* _texts, const char* _ssid, const char* _passwd, int* _output_pattern_addr){
        button_num = _button_num;
        texts = _texts;
        ssid = _ssid;
        passwd = _passwd;
        current_pattern_num = 0;
        output_pattern_addr = _output_pattern_addr;
        WiFi.softAP(ssid, passwd);
        delay(300);
        server.on("/", TemplateHtml::handle_OnConnect);
        server.on("/pattern", TemplateHtml::handle_buttons);
        server.onNotFound(TemplateHtml::handle_NotFound);
        server.begin();
        Serial.println("HTTP server started");
    }
    

    static String SendHTML(uint8_t pattern_num);
};
