// Load Wi-Fi library, Fast-LED Library and Custom OTA Library
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#include <html.h>
#include <pov.h>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

#define LED_PIN     13 // LED is connected to the IO-0 of the ESP8266-01
#define NUM_LEDS    11 // We have 8 LEDs in the strip
#define BRIGHTNESS  50 // set the brightness for the LEDs
#define UPDATES_PER_SECOND 100 // FPS
#define NUM_INTERVALS 12
char* LED_TYPE = "WS2812"; // We are using WS2812B LEDs
char* COLOR_ORDER = "GRB"; // Colour order of the LEDs

const char* wifi_ssid = "whoareyoubaby";
const char* wifi_password = "12345678";
int current_pattern = 0;
String texts[6] = {String(""), String("Color Pattern"), String("Clock Pattern"), String("Circle Pattern"), String("Shape Pattern"), String("Text Pattern")};

char text_s[20];
unsigned long currentTime = millis();
TemplateHtml our_html;
POVLib* pov;


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  TemplateHtml::initialize(5, texts, wifi_ssid, wifi_password, &current_pattern, text_s);
  pov = new POVLib(LED_PIN, NUM_LEDS, BRIGHTNESS, 500, NUM_INTERVALS, LED_TYPE, COLOR_ORDER);

}

void loop() {
  TemplateHtml::handle_client();
  if (current_pattern == 1) {
    for (int i = 0; i < NUM_LEDS; i++)
      pov->set_led(i, CRGB::Red);
    FastLED.show();
    delay(2000);
    for (int i = 0; i < NUM_LEDS; i++)
      pov->set_led(i, CRGB::White);
    FastLED.show();
    delay(2000);
    for (int i = 0; i < NUM_LEDS; i++)
      pov->set_led(i, CRGB::Green);
    FastLED.show();
    delay(2000);
  } 
  else if (current_pattern == 2){
    myclock();
  }
  else if (current_pattern == 3){
    show_shape();
  }
  else if (current_pattern == 4) {
    show_spin();
  }
  else if (current_pattern == 5) {
    show_texts(text_s);
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
  EVERY_N_SECONDS(10) {
    time_t rawtime;
    const time_t now = time(&rawtime) ;
    const tm calendar_time = *localtime(addressof(now)) ;
    int hour = calendar_time.tm_hour % 12;
    int min = calendar_time.tm_min;
    int sec = calendar_time.tm_sec;
    hour = 3;
    min = 0;
    pov->reset();
    Serial.println("After Reset");
    for(int i = 0; i < NUM_INTERVALS; i ++) {
      pov->draw_dot(i, NUM_LEDS - 1);
    }

    pov->draw_line(hour, 0, 3);
    pov->draw_line(min/5, 0, 5);
    // pov->draw_line(sec, 0, 7);
    Serial.println("After line");
  }
  pov->run_loop_body();
}

void show_shape() {
  static int i = 0;
  EVERY_N_MILLISECONDS(1000) {

    i = (i + 1) % NUM_LEDS;
    pov->reset();
    pov->draw_curve(0, 6, i);
  }
  pov->run_loop_body();
  delayMicroseconds(10);
}


void show_texts(char* s) {
  EVERY_N_SECONDS(10) {
    pov->set_texts(s);
  }
  pov->show_texts();
}


unsigned int povcolors[4] = {CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Yellow};
void show_spin() {
  EVERY_N_SECONDS(10) {
    for (int i = 0; i < NUM_INTERVALS; i += 3) {
      for (int j = 0; j < 3; j ++) {
        pov->draw_curve(i, (i + 3) % NUM_INTERVALS, j, povcolors[i/3]);
      }
      pov->draw_curve((i + 1) % NUM_INTERVALS, (i + 4)%NUM_INTERVALS, 3, povcolors[i/3]);
      pov->draw_curve((i + 2) % NUM_INTERVALS, (i + 5)%NUM_INTERVALS, 4, povcolors[i/3]);
      pov->draw_curve((i + 2) % NUM_INTERVALS, (i + 5)%NUM_INTERVALS, 5, povcolors[i/3]);
      pov->draw_curve((i + 2) % NUM_INTERVALS, (i + 5)%NUM_INTERVALS, 6, povcolors[i/3]);
      pov->draw_curve((i + 1) % NUM_INTERVALS, (i + 4)%NUM_INTERVALS, 7, povcolors[i/3]);
      for (int j = 8; j < 11; j ++) {
        pov->draw_curve(i, (i + 3) % NUM_INTERVALS, j, povcolors[i/3]);
      }
    }
  }
  pov->run_loop_body();
}
