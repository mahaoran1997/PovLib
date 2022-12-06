// Load Wi-Fi library, Fast-LED Library and Custom OTA Library
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

#include <sstream>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;


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


class POVLib {
    int led_pin;
    int num_leds;
    int brightness;
    int rounds_per_min;
    int intervals;
    int ms_per_interval;
    int current_interval;
    int us_small_dot;
    char* led_type;
    char* color_order;
    // int** v; // 0 represents black, 1 represents point, 2 represents continue // interval id; led id
    int v[100][30];


    CRGB* leds; // Create LED array for manipulation
    CRGBPalette16 currentPalette;
    TBlendType    currentBlending;

public:
    POVLib(int _led_pin, int _num_leds, int _brightness, int _rounds_per_min, int _intervals, char* _led_type, char* _color_order):
      led_pin(_led_pin), num_leds(_num_leds), brightness(_brightness), rounds_per_min(_rounds_per_min),
      intervals(_intervals), led_type(_led_type), color_order(_color_order), leds(NULL), current_interval(0) {
        leds = new CRGB[num_leds];
        FastLED.addLeds<WS2812, 13, GRB>(leds, num_leds).setCorrection( TypicalLEDStrip );
        FastLED.setBrightness(brightness);
        ms_per_interval = 60000/rounds_per_min/intervals; // Must be integer!
        us_small_dot = ms_per_interval * 100;
        currentPalette = RainbowColors_p;
        currentBlending = LINEARBLEND;

        Serial.println("intervals: ");
        Serial.println(intervals);
        Serial.println("num_leds ");
        Serial.println(num_leds);

        // v = new int*[intervals];
        // for (int i = 0; i < intervals; i ++) {
        //     v[i] = new int[num_leds];
        // }
    }
    void run_loop_body() {
        EVERY_N_MILLISECONDS(ms_per_interval) {
            current_interval = (current_interval + 1) % intervals;
            for(int i = 0; i < num_leds; i ++) {
                if (v[current_interval][i] >= 1) {
                    leds[i] = CRGB::White;
                }
                else {
                    leds[i] = CRGB::Black;
                }
            }
            FastLED.show();
            delayMicroseconds(1);
            bool has_white = 0;
            for(int i = 0; i < num_leds; i ++) {
                if (v[current_interval][i] >= 2) {
                    leds[i] = CRGB::White;
                }
                else {
                    leds[i] = CRGB::Black;
                }
            }
            FastLED.show();
            delayMicroseconds(1);
        }
        delayMicroseconds(us_small_dot);
    }

    // From inner to outer: 0,1,2,3,...
    void draw_curve(int interval_st, int interval_ed, int led_id) {
        if (interval_st == interval_ed) {

            Serial.println("Before set v");
            for(int i = 0; i < intervals; i ++) {
                Serial.println(i);
                Serial.println(led_id);
                Serial.println((long long)v);
                Serial.println((long long)(v[i]));
                v[i][led_id] = 2;
                Serial.println("done");
            }
            Serial.println("After set v");
        }
        else {
            for(int i = interval_st; i != interval_ed; i = (i + 1) % intervals) {
                v[i][led_id] = 2;
            }
        }
        return;
    }

    void draw_dot(int interval_id, int led_id) {
        v[interval_id][led_id] = 1;
    }


    void draw_line(int interval_id, int led_st, int led_ed) {
        
        for(int i = led_st; i <= led_ed; i ++) {
            v[interval_id][i] = 1;
        }
        return;
    }

    void reset() {
        // memset(v, 0, intervals * num_leds * sizeof(int));
        memset(v, 0, 100 * 30 * 4);
    }

    void set_led(int led_id, unsigned int color) {
      leds[led_id] = color;
    }
};



#define LED_PIN     13 // LED is connected to the IO-0 of the ESP8266-01
#define NUM_LEDS    11 // We have 8 LEDs in the strip
#define BRIGHTNESS  50 // set the brightness for the LEDs
#define UPDATES_PER_SECOND 100 // FPS

char* LED_TYPE = "WS2812"; // We are using WS2812B LEDs

char* COLOR_ORDER = "GRB"; // Colour order of the LEDs


const char* wifi_ssid = "whoareyoubaby";
const char* wifi_password = "12345678";
int current_pattern = 0;
String texts[4] = {String(""), String("Pattern 1"), String("Pattern 2"), String("Pattern 3")};


unsigned long currentTime = millis();

// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

TemplateHtml our_html;

POVLib* pov;


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  TemplateHtml::initialize(3, texts, wifi_ssid, wifi_password, &current_pattern);
  pov = new POVLib(LED_PIN, NUM_LEDS, BRIGHTNESS, 500, 60, LED_TYPE, COLOR_ORDER);

}

 
void loop() {
  TemplateHtml::handle_client();
  if (current_pattern == 1) {
    //first_light();
    //demo_reel100();
    for (int i = 0; i < NUM_LEDS; i++)
      pov->set_led(i, CRGB::Red);
    FastLED.show();
    delay(5000);

    for (int i = 0; i < NUM_LEDS; i++)
      pov->set_led(i, CRGB::White);
    FastLED.show();
    delay(5000);

    for (int i = 0; i < NUM_LEDS; i++)
      pov->set_led(i, CRGB::Green);
    FastLED.show();
    delay(5000);
  } 
  else if (current_pattern == 2){
    myclock();
  }
  else if (current_pattern == 3){
    show_shape();
  }
  else
  {
    for (int i = 0; i < NUM_LEDS; i++) {
      pov->set_led(i, CRGB::Black);
    }
    FastLED.show();
    delay(2);
  }
}

void myclock() {
  EVERY_N_MILLISECONDS(1000) {
    const time_t now = time(nullptr) ;
    const tm calendar_time = *localtime(addressof(now)) ;
    int hour = calendar_time.tm_hour % 12;
    int min = calendar_time.tm_min;
    int sec = calendar_time.tm_sec;

    Serial.println("hour:");
    Serial.println(hour);
    Serial.println("min:");
    Serial.println(min);
    Serial.println("sec:");
    Serial.println(sec);

    pov->reset();
    Serial.println("After Reset");
    for(int i = 0; i < 12; i ++) {
      pov->draw_dot(i * 5, NUM_LEDS - 1);
    }

    pov->draw_line(hour * 5, 0, 2);
    pov->draw_line(min, 0, 4);
    pov->draw_line(sec, 0, 5);
    Serial.println("After line");
  }
  pov->run_loop_body();
}

void show_shape() {
  static int i = 0;
  EVERY_N_MILLISECONDS(1000) {

    i = (i + 1) % NUM_LEDS;
    Serial.println("Second:");
    Serial.println(i);

    pov->reset();


    Serial.println("After Reset");
    pov->draw_curve(0, 0, i);

    Serial.println("After Curve");
  }
  pov->run_loop_body();
  delayMicroseconds(10);
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))