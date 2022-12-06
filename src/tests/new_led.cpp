// Load Wi-Fi library, Fast-LED Library and Custom OTA Library
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#include "webserver/html.h"
#include "lib/led/pov.h"
// ------------------------------------------------------------------------------------------------------------------------------------------------
// #include "OTA.h"
// ------------------------------------------------------------------------------------------------------------------------------------------------

#define LED_PIN     13 // LED is connected to the IO-0 of the ESP8266-01
#define NUM_LEDS    11 // We have 8 LEDs in the strip
#define BRIGHTNESS  50 // set the brightness for the LEDs
#define UPDATES_PER_SECOND 100 // FPS

char* LED_TYPE = "WS2812" // We are using WS2812B LEDs

char* COLOR_ORDER = "GRB" // Colour order of the LEDs


const char* ssid = "whoareyoubaby";
const char* password = "12345678";
int current_pattern;
String texts[4] = [String(""), String("Pattern 1"), String("Pattern 2"), String("Pattern 3")];


unsigned long currentTime = millis();

// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

TemplateHtml* our_html;

POVLib* pov;


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  our_html = new TemplateHtml(3, texts, ssid, password, &current_pattern);
  pov = new POVLib(LED_PIN, NUM_LEDS, BRIGHTNESS, 500, 12, LED_TYPE, COLOR_ORDER);

}

 
void loop() {
  if (current_pattern == 1) {
    //first_light();
    //demo_reel100();
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Red;
    FastLED.show();
    delay(5);

    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Green;
    FastLED.show();
    delay(5);

    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::White;
    FastLED.show();
    delay(5);
  } 
  else if (current_pattern == 2){
    myclock();
  }
  else if (current_pattern == 3){
    show_shape();
  }
  else
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(2);
    }
  }
}

void clock() {
  delayMicrosecond(1000);
}

void show_shape() {
  static int i = 0;
  i = (i + 1) % NUM_LEDS;
  EVERY_N_MILLISECONDS(1000) {
    pov.reset();
    pov.draw_curve(0, 0, i);
  }
  pov.run_loop_body();
  delayMicrosecond(10);
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))