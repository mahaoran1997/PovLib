// Load Wi-Fi library, Fast-LED Library and Custom OTA Library
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#include "webserver/html.h"
// ------------------------------------------------------------------------------------------------------------------------------------------------
// #include "OTA.h"
// ------------------------------------------------------------------------------------------------------------------------------------------------

#define LED_PIN     2 // LED is connected to the IO-0 of the ESP8266-01
#define NUM_LEDS    11 // We have 8 LEDs in the strip
#define BRIGHTNESS  50 // set the brightness for the LEDs
#define LED_TYPE    WS2812 // We are using WS2812B LEDs
#define COLOR_ORDER GRB // Colour order of the LEDs
#define UPDATES_PER_SECOND 100 // FPS

// ------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------

CRGB leds[NUM_LEDS]; // Create LED array for manipulation
CRGBPalette16 currentPalette; // set color palet type
TBlendType    currentBlending;// set blend mode



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


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  our_html = new TemplateHtml(3, texts, ssid, password, &current_pattern);

}

 
void loop() {
  if (current_pattern == 1) {
    //first_light();
    //demo_reel100();
    for (int i = 0; i < 8; i++)
      leds[i] = CRGB::Red;
    FastLED.show();
    delay(5);

    for (int i = 0; i < 8; i++)
      leds[i] = CRGB::Green;
    FastLED.show();
    delay(5);

    for (int i = 0; i < 8; i++)
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

// ------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------

void animation()
{
  EVERY_N_MILLISECONDS( 20) {
    pacifica_loop();
    FastLED.show();
  }
}


#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


CRGBPalette16 pacifica_palette_1 =
{ 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
  0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50
};
CRGBPalette16 pacifica_palette_2 =
{ 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
  0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F
};
CRGBPalette16 pacifica_palette_3 =
{ 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33,
  0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF
};
