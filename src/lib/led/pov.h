#include <FastLED.h>



class POVLib {
    int led_pin;
    int num_leds;
    int brightness;
    int rounds_per_sec;
    int intervals;
    int ms_per_interval;
    int current_interval;
    char* led_type;
    char* color_order;
    int** v; // 0 represents black, 1 represents point, 2 represents 


    CRGB* leds; // Create LED array for manipulation
    CRGBPalette16 currentPalette;
    TBlendType    currentBlending;

public:
    POVLib(int _led_pin, int _num_leds, int _brightness, int _rounds_per_sec, int _intervals, char* _led_type, char* _color_order):
      led_pin(_led_pin), num_leds(_num_leds), brightness(_brightness), rounds_per_sec(_rounds_per_sec),
      intervals(_intervals), led_type(_led_type), color_order(_color_order), leds(NULL), current_interval(0) {
        leds = new CRGB[num_leds];
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
        FastLED.setBrightness(BRIGHTNESS);
        ms_per_interval = 1000/rounds_per_sec/intervals; // Must be integer!
        currentPalette = RainbowColors_p;
        currentBlending = LINEARBLEND;

        v = new (int*)[intervals];
        for (int i = 0; i < intervals; i ++) {
            v[i] = new int[num_leds];
        }
    }
    void run_loop_body() {
        EVERY_N_MILLISECONDS(ms_per_interval) {

        }
    }

    void draw_curve() {


    }

    void draw_dot() {

    }

    void draw_line() {

    }

}