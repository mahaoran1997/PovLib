#include <FastLED.h>



const unsigned char font[95][5] = {
    {0x00,0x00,0x00,0x00,0x00},   //   0x20 32
    {0x00,0x00,0x6f,0x00,0x00},   // ! 0x21 33
    {0x00,0x07,0x00,0x07,0x00},   // " 0x22 34
    {0x14,0x7f,0x14,0x7f,0x14},   // # 0x23 35
    {0x00,0x07,0x04,0x1e,0x00},   // $ 0x24 36
    {0x23,0x13,0x08,0x64,0x62},   // % 0x25 37
    {0x36,0x49,0x56,0x20,0x50},   // & 0x26 38
    {0x00,0x00,0x07,0x00,0x00},   // ' 0x27 39
    {0x00,0x1c,0x22,0x41,0x00},   // ( 0x28 40
    {0x00,0x41,0x22,0x1c,0x00},   // ) 0x29 41
    {0x14,0x08,0x3e,0x08,0x14},   // * 0x2a 42
    {0x08,0x08,0x3e,0x08,0x08},   // + 0x2b 43
    {0x00,0x50,0x30,0x00,0x00},   // , 0x2c 44
    {0x08,0x08,0x08,0x08,0x08},   // - 0x2d 45
    {0x00,0x60,0x60,0x00,0x00},   // . 0x2e 46
    {0x20,0x10,0x08,0x04,0x02},   // / 0x2f 47
    {0x3e,0x51,0x49,0x45,0x3e},   // 0 0x30 48
    {0x00,0x42,0x7f,0x40,0x00},   // 1 0x31 49
    {0x42,0x61,0x51,0x49,0x46},   // 2 0x32 50
    {0x21,0x41,0x45,0x4b,0x31},   // 3 0x33 51
    {0x18,0x14,0x12,0x7f,0x10},   // 4 0x34 52
    {0x27,0x45,0x45,0x45,0x39},   // 5 0x35 53
    {0x3c,0x4a,0x49,0x49,0x30},   // 6 0x36 54
    {0x01,0x71,0x09,0x05,0x03},   // 7 0x37 55
    {0x36,0x49,0x49,0x49,0x36},   // 8 0x38 56
    {0x06,0x49,0x49,0x29,0x1e},   // 9 0x39 57
    {0x00,0x36,0x36,0x00,0x00},   // : 0x3a 58
    {0x00,0x56,0x36,0x00,0x00},   // ; 0x3b 59
    {0x08,0x14,0x22,0x41,0x00},   // < 0x3c 60
    {0x14,0x14,0x14,0x14,0x14},   // = 0x3d 61
    {0x00,0x41,0x22,0x14,0x08},   // > 0x3e 62
    {0x02,0x01,0x51,0x09,0x06},   // ? 0x3f 63
    {0x3e,0x41,0x5d,0x49,0x4e},   // @ 0x40 64
    {0x7e,0x09,0x09,0x09,0x7e},   // A 0x41 65
    {0x7f,0x49,0x49,0x49,0x36},   // B 0x42 66
    {0x3e,0x41,0x41,0x41,0x22},   // C 0x43 67
    {0x7f,0x41,0x41,0x41,0x3e},   // D 0x44 68
    {0x7f,0x49,0x49,0x49,0x41},   // E 0x45 69
    {0x7f,0x09,0x09,0x09,0x01},   // F 0x46 70
    {0x3e,0x41,0x49,0x49,0x7a},   // G 0x47 71
    {0x7f,0x08,0x08,0x08,0x7f},   // H 0x48 72
    {0x00,0x41,0x7f,0x41,0x00},   // I 0x49 73
    {0x20,0x40,0x41,0x3f,0x01},   // J 0x4a 74
    {0x7f,0x08,0x14,0x22,0x41},   // K 0x4b 75
    {0x7f,0x40,0x40,0x40,0x40},   // L 0x4c 76
    {0x7f,0x02,0x0c,0x02,0x7f},   // M 0x4d 77
    {0x7f,0x04,0x08,0x10,0x7f},   // N 0x4e 78
    {0x3e,0x41,0x41,0x41,0x3e},   // O 0x4f 79
    {0x7f,0x09,0x09,0x09,0x06},   // P 0x50 80
    {0x3e,0x41,0x51,0x21,0x5e},   // Q 0x51 81
    {0x7f,0x09,0x19,0x29,0x46},   // R 0x52 82
    {0x46,0x49,0x49,0x49,0x31},   // S 0x53 83
    {0x01,0x01,0x7f,0x01,0x01},   // T 0x54 84
    {0x3f,0x40,0x40,0x40,0x3f},   // U 0x55 85
    {0x0f,0x30,0x40,0x30,0x0f},   // V 0x56 86
    {0x3f,0x40,0x30,0x40,0x3f},   // W 0x57 87
    {0x63,0x14,0x08,0x14,0x63},   // X 0x58 88
    {0x07,0x08,0x70,0x08,0x07},   // Y 0x59 89
    {0x61,0x51,0x49,0x45,0x43},   // Z 0x5a 90
    {0x3c,0x4a,0x49,0x29,0x1e},   // [ 0x5b 91
    {0x02,0x04,0x08,0x10,0x20},   // \ 0x5c 92
    {0x00,0x41,0x7f,0x00,0x00},   // ] 0x5d 93
    {0x04,0x02,0x01,0x02,0x04},   // ^ 0x5e 94
    {0x40,0x40,0x40,0x40,0x40},   // _ 0x5f 95
    {0x00,0x00,0x03,0x04,0x00},   // ` 0x60 96
    {0x20,0x54,0x54,0x54,0x78},   // a 0x61 97
    {0x7f,0x48,0x44,0x44,0x38},   // b 0x62 98
    {0x38,0x44,0x44,0x44,0x20},   // c 0x63 99
    {0x38,0x44,0x44,0x48,0x7f},   // d 0x64 100
    {0x38,0x54,0x54,0x54,0x18},   // e 0x65 101
    {0x08,0x7e,0x09,0x01,0x02},   // f 0x66 102
    {0x0c,0x52,0x52,0x52,0x3e},   // g 0x67 103
    {0x7f,0x08,0x04,0x04,0x78},   // h 0x68 104
    {0x00,0x44,0x7d,0x40,0x00},   // i 0x69 105
    {0x20,0x40,0x44,0x3d,0x00},   // j 0x6a 106
    {0x00,0x7f,0x10,0x28,0x44},   // k 0x6b 107
    {0x00,0x41,0x7f,0x40,0x00},   // l 0x6c 108
    {0x7c,0x04,0x18,0x04,0x78},   // m 0x6d 109
    {0x7c,0x08,0x04,0x04,0x78},   // n 0x6e 110
    {0x38,0x44,0x44,0x44,0x38},   // o 0x6f 111
    {0x7c,0x14,0x14,0x14,0x08},   // p 0x70 112
    {0x08,0x14,0x14,0x18,0x7c},   // q 0x71 113
    {0x7c,0x08,0x04,0x04,0x08},   // r 0x72 114
    {0x48,0x54,0x54,0x54,0x20},   // s 0x73 115
    {0x04,0x3f,0x44,0x40,0x20},   // t 0x74 116
    {0x3c,0x40,0x40,0x20,0x7c},   // u 0x75 117
    {0x1c,0x20,0x40,0x20,0x1c},   // v 0x76 118
    {0x3c,0x40,0x30,0x40,0x3c},   // w 0x77 119
    {0x44,0x28,0x10,0x28,0x44},   // x 0x78 120
    {0x0c,0x50,0x50,0x50,0x3c},   // y 0x79 121
    {0x44,0x64,0x54,0x4c,0x44},   // z 0x7a 122
    {0x00,0x08,0x36,0x41,0x41},   // { 0x7b 123
    {0x00,0x00,0x7f,0x00,0x00},   // | 0x7c 124
    {0x41,0x41,0x36,0x08,0x00},   // } 0x7d 125
    {0x04,0x02,0x04,0x08,0x04},   // ~ 0x7e 126
};

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
    int v[50][15];
    unsigned int colors[50][15];

    char* text_str;

    CRGB* leds; // Create LED array for manipulation
    CRGBPalette16 currentPalette;
    TBlendType    currentBlending;

public:
    POVLib(int _led_pin, int _num_leds, int _brightness, int _rounds_per_min, int _intervals, char* _led_type, char* _color_order):
      led_pin(_led_pin), num_leds(_num_leds), brightness(_brightness), rounds_per_min(_rounds_per_min),
      intervals(_intervals), led_type(_led_type), color_order(_color_order), text_str(NULL), leds(NULL), current_interval(0) {
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

        memset(v, 0, 50 * 15 * 4);
        memset(colors, 0, 50 * 15 * 4);
    }
    void run_loop_body() {
        EVERY_N_MILLISECONDS(ms_per_interval) {
            current_interval = (current_interval + 1) % intervals;
            for(int i = 0; i < num_leds; i ++) {
                if (v[current_interval][i] >= 1) {
                    leds[i] = colors[current_interval][i];
                }
                else {
                    leds[i] = CRGB::Black;
                }
            }
            FastLED.show();
            // delayMicroseconds(1);
            // bool has_white = 0;
            for(int i = 0; i < num_leds; i ++) {
                if (v[current_interval][i] >= 2) {
                    leds[i] = colors[current_interval][i];
                }
                else {
                    leds[i] = CRGB::Black;
                }
            }
            FastLED.show();
            // delayMicroseconds(1);
        }
        // delayMicroseconds(us_small_dot);
    }

    // From inner to outer: 0,1,2,3,...
    void draw_curve(int interval_st, int interval_ed, int led_id, unsigned int color = CRGB::White) {
        if (interval_st == interval_ed) {

            Serial.println("Before set v");
            for(int i = 0; i < intervals; i ++) {
                Serial.println(i);
                Serial.println(led_id);
                v[i][led_id] = 2;
                colors[i][led_id] = color;
                Serial.println("done");
            }
            Serial.println("After set v");
        }
        else {
            for(int i = interval_st; i != interval_ed; i = (i + 1) % intervals) {
                Serial.println(i);
                Serial.println(led_id);
                v[i][led_id] = 2;
                colors[i][led_id] = color;
                Serial.println("done");
            }
        }
        return;
    }

    void draw_dot(int interval_id, int led_id, unsigned int color = CRGB::White) {
        v[interval_id][led_id] = 1;
        colors[interval_id][led_id] = color;
    }


    void draw_line(int interval_id, int led_st, int led_ed, unsigned int color = CRGB::White) {
        
        for(int i = led_st; i <= led_ed; i ++) {
            v[interval_id][i] = 1;
            colors[interval_id][i] = color;
        }
        return;
    }

    void reset() {
        // memset(v, 0, intervals * num_leds * sizeof(int));
        memset(v, 0, 50 * 15 * 4);
        memset(colors, 0, 50 * 15 * 4);
    }

    void set_led(int led_id, unsigned int color) {
      leds[led_id] = color;
    }

    void set_texts(char* s) {
      text_str = s;
    }
    void show_texts() {
      EVERY_N_MILLISECONDS(ms_per_interval * intervals) {
        if(text_str == NULL) {
          delay(5);
          return;
        }
        int len = strlen(text_str);
        for(int i = len - 1; i >= 0; i --) {
          char c = text_str[i];
          showLetter(c);
        }
      } 
    }


    void showLetter(char ch)
    {
      if (ch < 32 || ch > 126){
        ch = 32;
      }
      ch -= 32;
      for (int i = 4; i >= 0; i--) {
        char b = font[ch][i];
        for (int j = 0; j < 8; j++) {
          if(b&(1<<j))
            leds[num_leds - j] = CRGB::White;
          else {
            leds[num_leds - j] = CRGB::Black;
          }
        }
        FastLED.show();
        delay(1);
      }
      for (int i = 0; i < num_leds; i++)
        leds[i] = CRGB::Black;
      FastLED.show();
      delay(1);
    
    }
};

