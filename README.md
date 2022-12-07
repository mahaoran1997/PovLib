# POVLib: A Customizable Easy-to-use Library for Persistent Vision Display

## Group Members

Haoran Ma, Yu Bai


## 1 Introduction

POVLib is a lightweight, customizablem, and easy-to-use persistent vision display library. Programmers can easily integrate this library to their code and create beautiful patterns they want. POVLib also includes a simple html-based web server library to help programmers create a webpage using a few lines of code to interact with the real users of the POV display.

## 2 Motivation

Light effect plays an important role in attracting people’s attention in many places. Car manufacturers focus on ambient lighting inside the vehicle. Gaming hardware companies include light effects for their computers and keyboards. Even speakers are equipped with lights to attract customers. By utilizing the persistence of vision effect, rotating LEDs can form a 2D display for texts and light patterns. This gadget can be used as a clock, ambient lighting, and many other applications. 

However, visualizing different patterns by rotating LEDs currently requires programmers to take care of every low-level detail such as timing and synchronization when programming on real hardwares. For example, they need to explicitly control the on and off time for every LED light, and there could be thousands of LED lights on one display. Programs could be extremely long in such cases. POVLib -- a persistent vision display library can help users easily create beautiful patterns with only a few lines of code.

## 3 Challenges
There are two main challenges we may encounter.

The first challenge is how to design an easy-to-use library interface for programmers, while still preserving flexibility. There is tradeoff between them. Clearly just providing several available patterns to programmers is the easiest way. But then there is no flexibility. And if we make it too flexible, then it has no difference between using our library and the original way to just manipulate the hardware itself.

Secondly, how to let our device communicate with our board? After research, we found one way is to 
use ESP8266 NodeMCU as an Access Point, which allows users to directly connect the board via Wi-Fi, so the board does not needed to be connected with a router. Then, we can design the user interface and set up the data transmission in HTML. 

## 4 Related Work
The paper *Persistance of Vision Control Using Arduino* by Robinson, Ghansyam, and Vishwa introduced us a Piranha LED POV project that was controled by an Andrioid device<sup>[1]</sup>. Users could send a message of commend with their device to the microcontroller to change the display pattern. The paper accomplished a new way of interacting with the users by providing a touchscreen<sup>[2]</sup>. The Raspberry Pi took the touchpad as input and tranformed the drawing to the POV display. Debashis also built a POV display using WS2812 Neopixel and ESP8266, and users were able to control the display pattern on any device via Wi-Fi<sup>[3]</sup>. However, the weakness of each approach is noticeable like the obsolete LEDs and the complexity to design display patterns. 

## 5 Novelty & Rationale
In our approach, we plan to replace the old LEDs with the Neopixel RGBs to provide more colors and to easily adjust the brightness. A new interaction is also accomplished, which let users to DIY the display pattern on their own devices. Moreover, we created a library named POVLib to help users and programmers create remarkable patterns with only a few lines of code.  

## 6 Source Code Repo

You can find all our source code and 3D printer models [here](https://github.com/mahaoran1997/PovLib).
A step-by-step guide to build a POV display can be found in [section 1](https://www.haoranma.info/vision.github.io/test/guide.html) of this documentation.



## 7 Step-by-step Guide


### 7.1 Hardware Setup
#### 7.1.1 Required Components:
* ESP8266 NodeMCU
* Arduino Uno
* L298N Motor Driver
* WS2812B RGB LEDS
* 12V DC Motor
* 3.7V 400mA Lithium Battery
* 12V Battery (Power the motor)
* 330<span>&#8486;</span> Resistor
* 18cm &#xD7; 10cm PCB Board
* 4mm Rigid Flange
* Screws and Nuts

#### 7.1.2 Circuit Schematics:
The first scheme is ESP8266 circuit, which powers the WS2812 LEDs and uses WiFi to control and switch the light patterns.
<img src="https://www.haoranma.info/vision.github.io/assets/images/NodeMCU Circuit_schem.jpg" alt="ESP8266 Circuit Scheme">

The following picture is the L298N Motor Driver Scheme, which powers the 12V motor and controls the motor's rotational speed. 
<img src="https://www.haoranma.info/vision.github.io/assets/images/Motor Circuit_bb.png" alt="L298N Motor Driver Scheme">

To power and control the motor speed, we need to use the Pulse Width Modulation (PWM), a way to control analog devices with a digital output. In other words, we can output a modulating signal from a digital device (Arduino Uno) to drive an analog device (motor). After setting up the motor driver circuit, we can simply assign the Arduino output pins, and call `analogWrite`.

```C++
int enA = 9;
int in1 = 8;
int in2 = 7;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

}

void loop(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  analogWrite(enA,321);

  delay(2000);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
}
```

#### 7.1.3 3D Printed Models:
- The following two models are 3D printed to contain all the required components, the original STL files can be found <a href="https://github.com/mahaoran1997/vision.github.io/tree/develop/assets/3D%20Models" target="_blank">here</a>.
<table>
<tr><td><center>Model Base</center></td><td> <center>Model Cover</center></td></tr>
<tr><td>
<img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/Model Base.png" alt="Model Base"/></td><td> <img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/Model Cover.png" alt="Model Cover"/></td></tr>
</table>



### 7.2 Software Code

Here we show how to use our POVLib to easily build a POV Display and a web server.

#### 7.2.1 Web Server

To build a simple web server, we need to firstly import the html module of our POVLib. And then declare an object with class `TemplateHtml`. Inside the setup function, we initialize the TemplateHtml object with parameters specified by us.

```C++
#include <html.h>

TemplateHtml our_html;
void setup() {    
  Serial.begin(115200);
  // .....
  TemplateHtml::initialize(5, texts, wifi_ssid, wifi_password, &current_pattern, text_s);
}
```
In the code above, we input 6 parameters into the initialize function. The first parameter is how many patterns we have. The second parameter is a string array. It contains the pattern names. The third and fourth parameters are the ssid and password of wifi server specified by users. The fifth parameter is an integer pointer, it is used to transfer the information of pattern selected by users from html module to our code. The last parameter is a char array and is also used to transfer parameter information from html module to our code (e.g. the input box shown in section 3).

Then at the start of the loop function, we need to call `TemplateHtml::handle_client()`. 
```C++
void loop() {
  TemplateHtml::handle_client();
  // Code to show patterns ...
}
```


#### 7.2.2 Create Patterns

To easily create our patterns using POVLib, we need to firstly import the pov module of our POVLib. And then create an object with class `POVLib`. Inside the setup function, we call the constructor of POVLib.
```C++
#include <pov.h>

POVLib* pov;
void setup() {    
  Serial.begin(115200);
  // .....
  pov = new POVLib(LED_PIN, NUM_LEDS, BRIGHTNESS, SPEED, NUM_INTERVALS, LED_TYPE, COLOR_ORDER);
  pov->reset();
}
```
In the code above, we input 7 parameters into the constructor of POVLib. The first parameter is the pin number of LED. The second parameter is the number of leds we have on the stripe. The third specifies the brightness of LED and the fourth parameter specifies the speed of the motor. The fifth parameter is how many intervals we want to split for a single circle. The last two parameters are the type of our leds and the color order.

So basically the POVLib will create a polar grid graph. There are NUM_LEDS*NUM_INTERVALS points in the graph. And we use (Interval ID, LED ID) to identify each point. The `reset` function just resets every point to black. We can use other interfaces to create patterns we want. A complete interface introduction can be found in [section 2](https://www.haoranma.info/vision.github.io/test/modules.html). Here we show an example: how we created our shape pattern.

```C++
void loop() {
  TemplateHtml::handle_client();
  // ...
  else if (current_pattern == 4) {
    show_shape();
  }
  // Other patterns ...
}

unsigned int povcolors[4] = {CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Yellow};
void show_shape() {
  EVERY_N_SECONDS(1) {
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
```
In the loop function, we check the value of `current_pattern`. If it is 4, then we call `show_shape` to show the pattern we create. In `show_shape`, we firstly draw the pattern. The `draw_curve` function takes four input parametes. The first two specifies the start and end interval IDs of this curve and the third parameter specifies the LED ID of the curve. The last one gives the color of this curve. Actually We can also draw dots and lines using other interfaces. After creating the pattern, we need to call the `run_loop_body` function in POVLib to let our hardwares show the pattern.

### 7.3 Visual Effects

We built a demo system and created five different patterns using our library to show its usability. Our demo system has a web interface, and users can select which pattern to show on our led display through buttons on the webpage. To open the webpage, users firstly need to connect to the wifi channel created by our system and goto `192.168.4.1` in your browser app. The web page is shown below and we can see five different patterns on the website. 

<center>
<figure>
<figcaption align = "center"><b>Demo Web Page</b></figcaption>
<img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/WebPage.PNG" alt="Demo Web Page" width="400"/>
</figure>
</center>



#### 7.3.1 Color Pattern
After we activate the first pattern -- color pattern which is the simplest one in this demo. It changes its color every 5 seconds. The visual effects are shown below:

<table>
<tr><td><center>Color Pattern 1</center></td><td> <center>Color Pattern 2</center></td></tr>
<tr><td>
<img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern1_1.JPG" alt="Color Pattern 1"/></td><td> <img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern1_2.JPG" alt="Color Pattern 2"/></td></tr>
</table>

We used long exposure camera to capture the pattern. Due to the camera sampling frequency is not high enough, though the pattern in the image is missing a corner, it actually fills all round face when we are looking at it through our eyes. This problem also arises in the rest several patterns.

#### 7.3.2 Clock Pattern
After we activate the second pattern -- clock pattern. It shows the current time (hour and minute). The visual effects are shown below:


<table>
<tr><td><center>Clock Pattern 1</center></td><td> <center>Clock Pattern 2</center></td></tr>
<tr><td>
<img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern2_1.JPG" alt="Clock Pattern 1"/></td><td> <img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern2_2.JPG" alt="Clock Pattern 2"/></td></tr>
</table>




#### 7.3.3 Circle Pattern
After we activate the third pattern -- circle pattern. It shows a circle starting from inner side gradually goes to outer side. The visual effects are shown below:

<table>
<tr><td><center>Circle Pattern 1</center></td><td> <center>Circle Pattern 2</center></td><td> <center>Circle Pattern 3</center></td></tr>
<tr><td>
<img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern3_1.JPG" alt="Circle Pattern 1"/></td><td> <img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern3_2.JPG" alt="Circle Pattern 2"/></td><td> <img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern3_3.JPG" alt="Circle Pattern 3"/></td></tr>
</table>


#### 7.3.4 Shape Pattern
After we activate the fourth pattern -- shape pattern. It shows the a complex colorful pattern designed by us using less than 10 lines of code. The visual effects are shown below:

<table>
<tr><td><center>Shape Pattern 1</center></td><td> <center>Shape Pattern 2</center></td></tr>
<tr><td>
<img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern5_1.jpg" alt="Shape Pattern 1"/></td><td> <img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern5_2.JPG" alt="Shape Pattern 2"/></td></tr>
</table>


#### 7.3.5 Text Pattern
After we input the text we want to show into the text box and submit it, it activates the last pattern -- text pattern. It shows the texts specified by us. Example visual effects are shown below (we use "hello" as an example):

<center>
<figure>
<figcaption align = "center">Text Pattern</figcaption>
<img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/pattern4.jpg" alt="Text Pattern" width="500"/>
</figure>
</center>


## 8 Software Modules

There are two modules in our POVLib project: POV Module and HTML Module. We actually seperate them into two libraries because they can used individually without relying on each other. The POV module is to help programmers create patterns while the HTML module is to help programmers easily build a web server. The HTML module can also be used in many other scenarios.

### 8.1 POV Module

The POV module contains a class called `POVLib` which is the same as our project name. There are in total 10 interfaces visible to external programmers.

```C++
class POVLib {
public:
    POVLib(int _led_pin, int _num_leds, int _brightness, int _rounds_per_min, int _intervals, char* _led_type, char* _color_order);
    void run_loop_body();
    void draw_curve(int interval_st, int interval_ed, int led_id, unsigned int color = CRGB::White);
    void draw_dot(int interval_id, int led_id, unsigned int color = CRGB::White);
    void draw_line(int interval_id, int led_st, int led_ed, unsigned int color = CRGB::White);
    void reset();
    void set_led(int led_id, unsigned int color);
    void set_texts(char* s);
    void show_texts();
};
```

- `POVLib(int _led_pin, int _num_leds, int _brightness, int _rounds_per_min, int _intervals, char* _led_type, char* _color_order);`
  - Constructor of POVLib: The first parameter is the pin number of LED. The second parameter is the number of leds we have on the stripe. The third specifies the brightness of LED and the fourth parameter specifies the speed of the motor. The fifth parameter is how many intervals we want to split for a single circle. The last two parameters are the type of our leds and the color order.
- `void run_loop_body();`
  - Function to show patterns. It changes LED values based on time. We need to frequently call this interface in the loop function.
- `void reset();`
  - This function resets all LEDs to black.
- `void draw_curve(int interval_st, int interval_ed, int led_id, unsigned int color = CRGB::White);`
  - We can draw a curve using this interface. The first two parameters specifies the start and end interval IDs of this curve and the third parameter specifies the LED ID of the curve. The last one gives the color of this curve. 
- `void draw_dot(int interval_id, int led_id, unsigned int color = CRGB::White);`
  - This function is used to draw a dot. The first parameter specifies the interval ID and the second parameter specifies the LED ID. The last one gives the color of this dot. 
- `void draw_line(int interval_id, int led_st, int led_ed, unsigned int color = CRGB::White);`
  - We can draw a line using this interface. The first parameter specifies the interval ID. The following two parameters specifies the start and end LED IDs of this line. The last one gives the color. 
- `void set_led(int led_id, unsigned int color);`
  - We can also directly manipulate LEDs through this function. We decide to expose this primitive function to external programmers to preserve flexibility.
- `void set_texts(char* s);`
  - Our POVLib supports showing texts. This interface is used to specify the texts to be shown.
- `void show_texts();`
  - Function to show texts. It changes LED values based on time. We need to frequently call this interface in the loop function.


### 8.2 HTML Module

The interfaces of HTML Module is simple and is already covered in the step-by-step guide. Here we just show the formal interface:

```C++
class TemplateHtml {
public:
    static void initialize(int _button_num, String* _texts, const char* _ssid, const char* _passwd, int* _output_pattern_addr, char* _text_to_display);
    static void handle_client();
};
```


## 9 Integration


### 9.1 Download
Our code is open sourced on github: [link](https://github.com/mahaoran1997/PovLib). You can download all library code and example code from github.

### 9.2 Integration to your system

After downloading the code, open Arduino library folder. In that directory, create two folders: Html and POVLib. Copy corresponding source code files to those two folders. Then restart your Arduino IDE. Click Sketch->Include Library->Html and Sketch->Include Library->POVLib (shown as below). Then you can start coding and creating your own patterns now!

<center>
<figure>
<figcaption align = "center"><b>Include Library</b></figcaption>
<img align="center" src="https://www.haoranma.info/vision.github.io/assets/images/sketch.jpg" alt="integration" width="500"/>
</figure>
</center>

## References
[1] Paul, Robinson P., et al. "Persistence of Vision control using Arduino." International Journal of Intelligent Systems and Applications (IJISA), IJISA 6.1 (2013).

[2] Patel, Aditya, et al. “Persistence Of Vision Display- A Review.” IOSR Journal of Electrical and Electronics Engineering, vol. 10, no. 4, 2015, pp. 36–40., https://doi.org/10.9790/1676-10433640 . 

[3] Das, Debashis. “How Not to Build a POV Display Using WS2812B Neopixel Leds and ESP8266.” CIRCUIT DIGEST, 21 Apr. 2022, https://circuitdigest.com/microcontroller-projects/build-pov-display-using-ws2812b-neopixel-led-and-esp8266. 

<!-- [2] Dhruv, Akshay, et al. "Wireless Remote Controlled POV Display." International Journal of Computer Applications 115.7 (2015).

[3] Kolsur, Anoop, Sandeep Awale, and Nagraj Ullagaddi. "POV: Persistence of Vision." -->

## The license

The theme is available as open source under the terms of the MIT License



