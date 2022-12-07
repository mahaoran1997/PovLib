# POVLib: A Customizable Easy-to-use Library for Persistent Vision Display

## Group Members

Haoran Ma, Yu Bai


## Introduction

POVLib is a lightweight, customizablem, and easy-to-use persistent vision display library. Programmers can easily integrate this library to their code and create beautiful patterns they want. POVLib also includes a simple html-based web server library to help programmers create a webpage using a few lines of code to interact with the real users of the POV display.

## Motivation

Light effect plays an important role in attracting people’s attention in many places. Car manufacturers focus on ambient lighting inside the vehicle. Gaming hardware companies include light effects for their computers and keyboards. Even speakers are equipped with lights to attract customers. By utilizing the persistence of vision effect, rotating LEDs can form a 2D display for texts and light patterns. This gadget can be used as a clock, ambient lighting, and many other applications. 

However, visualizing different patterns by rotating LEDs currently requires programmers to take care of every low-level detail such as timing and synchronization when programming on real hardwares. For example, they need to explicitly control the on and off time for every LED light, and there could be thousands of LED lights on one display. Programs could be extremely long in such cases. POVLib -- a persistent vision display library can help users easily create beautiful patterns with only a few lines of code.

## Challenges
There are two main challenges we may encounter.

The first challenge is how to design an easy-to-use library interface for programmers, while still preserving flexibility. There is tradeoff between them. Clearly just providing several available patterns to programmers is the easiest way. But then there is no flexibility. And if we make it too flexible, then it has no difference between using our library and the original way to just manipulate the hardware itself.

Secondly, how to let our device communicate with our board? After research, we found one way is to 
use ESP8266 NodeMCU as an Access Point, which allows users to directly connect the board via Wi-Fi, so the board does not needed to be connected with a router. Then, we can design the user interface and set up the data transmission in HTML. 

## Related Work
The paper *Persistance of Vision Control Using Arduino* by Robinson, Ghansyam, and Vishwa introduced us a Piranha LED POV project that was controled by an Andrioid device<sup>[1]</sup>. Users could send a message of commend with their device to the microcontroller to change the display pattern. The paper accomplished a new way of interacting with the users by providing a touchscreen<sup>[2]</sup>. The Raspberry Pi took the touchpad as input and tranformed the drawing to the POV display. Debashis also built a POV display using WS2812 Neopixel and ESP8266, and users were able to control the display pattern on any device via Wi-Fi<sup>[3]</sup>. However, the weakness of each approach is noticeable like the obsolete LEDs and the complexity to design display patterns. 

## Novelty & Rationale
In our approach, we plan to replace the old LEDs with the Neopixel RGBs to provide more colors and to easily adjust the brightness. A new interaction is also accomplished, which let users to DIY the display pattern on their own devices. Moreover, we created a library named POVLib to help users and programmers create remarkable patterns with only a few lines of code.  

## Source Code Repo

You can find all our source code and 3D printer models [here](https://github.com/mahaoran1997/PovLib).
A step-by-step guide to build a POV display can be found in [section 1](https://www.haoranma.info/vision.github.io/test/guide.html) of this documentation.

## References
[1] Paul, Robinson P., et al. "Persistence of Vision control using Arduino." International Journal of Intelligent Systems and Applications (IJISA), IJISA 6.1 (2013).

[2] Patel, Aditya, et al. “Persistence Of Vision Display- A Review.” IOSR Journal of Electrical and Electronics Engineering, vol. 10, no. 4, 2015, pp. 36–40., https://doi.org/10.9790/1676-10433640 . 

[3] Das, Debashis. “How Not to Build a POV Display Using WS2812B Neopixel Leds and ESP8266.” CIRCUIT DIGEST, 21 Apr. 2022, https://circuitdigest.com/microcontroller-projects/build-pov-display-using-ws2812b-neopixel-led-and-esp8266. 

<!-- [2] Dhruv, Akshay, et al. "Wireless Remote Controlled POV Display." International Journal of Computer Applications 115.7 (2015).

[3] Kolsur, Anoop, Sandeep Awale, and Nagraj Ullagaddi. "POV: Persistence of Vision." -->

## The license

The theme is available as open source under the terms of the MIT License



