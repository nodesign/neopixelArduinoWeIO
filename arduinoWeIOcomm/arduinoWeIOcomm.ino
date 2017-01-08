///////////////////// NEOPIXEL INIT
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include "colorModel.h"

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      85

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long mem[NUMPIXELS];

///////////////////// NEOPIXEL INIT END

//////////////////////////////////////////////////////////////////////////
//
//   Example 1 : "A R255 G255 B255\n" or "A #FFFFFF\n"
//   A - stands for all leds
//
//   Example 2 : "A L30\n"
//   A - stands for all leds
//   L - stands for brightness level of actual led color
//   With this example you set brightness level for all leds
//
//   Example 3 : "P R255 G255 B255 L9\n" or "H #FFFFFF L99\n"
//   P - stands for specific led number defined by L parameter
//
//
//   It has to start with A or P other data order is not relevant
//   It has to finish with \n to be interpreted correctly
//
//////////////////////////////////////////////////////////////////////////


//struct color memPixels[NUMPIXELS];

char buf[64]; // max size that can be accepted in arduino
int8_t bufindex;


int alphaA = 0;

void setup() {
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.

  //turnONWhiteLights();
  //delay(1000);
  turnOffLights();

  for (int i = 0; i < NUMPIXELS; i++) mem[i] = getColorInt(0, 0, 0);

}

void loop() {


  if (Serial.available()) {
    char c = Serial.read();
    buf[bufindex++] = c;
    if (c == '\n') { // when \n is found, parse it!
      buf[bufindex] = '\0';  //Null terminate the string - Essential for first use of 'buf' and good programming practice
      parseCmd(buf);
      memset(buf, 0, 64);
      bufindex = 0;
    }
    if (bufindex >= 64) {
      bufindex = 0;
    }
  }

  //// TEST PURPOSES
  /*
    if (alphaA < 255) alphaA++; else alphaA = 0;


    for (int i = 0; i < NUMPIXELS; i++) {

      unsigned long ledBrut = mem[i];
      struct color led;

      led.red   = getRed(ledBrut);
      led.green = getGreen(ledBrut);
      led.blue  = getBlue(ledBrut);

      RGBtoHSB(&led);
      led.brightness = normalize(alphaA);
      HSBtoRGB(&led);

      Serial.print(led.red);
      Serial.print("  ");
      Serial.print(led.green);
      Serial.print("  ");
      Serial.println(led.blue);

      pixels.setPixelColor(i, pixels.Color(led.red, led.green, led.blue));

    }
    pixels.show();
    delay(10);
  */


}


void parseCmd(char * cmd)
{
  if (cmd[0] == 'A') { // command all lights
    allLights(cmd);
  }
  else if (cmd[0] == 'P') { // command specific light
    singleLight(cmd);
  } else if (cmd[0] == 'H') {
    singleLightHexColor(cmd);
  }
  Serial.println("OK");
}

void singleLightHexColor(char * cmd)
{
  char * tmp;
  char * str;
  str = strtok_r(cmd, " ", &tmp);
  int selector = 0;
  unsigned long color = 0;
  while (str != NULL) {
    str = strtok_r(0, " ", &tmp);
    if (str[0] == 'L') {
      selector = atoi(str + 1);
    }
    else if (str[0] == '#') {
      color = strtol(str + 1, NULL, 16);
    }
  }

  setLight(selector, getRed(color), getGreen(color), getBlue(color));
  pixels.show(); // This sends the updated pixel color to the hardware.

  /*
    Serial.print(getRed(color));
    Serial.print("  ");
    Serial.print(getGreen(color));
    Serial.print("  ");
    Serial.print(getBlue(color));
    Serial.print("  ");
    Serial.print(color);
    Serial.print("  ");
    Serial.println(selector);
  */
}
void allLights(char * cmd)
{
  char * tmp;
  char * str;
  str = strtok_r(cmd, " ", &tmp);
  int ledR = -1;
  int ledG = -1;
  int ledB = -1;
  int alpha = -1;
  unsigned long color = 0;
  
  while (str != NULL) {
    str = strtok_r(0, " ", &tmp);
    if (str[0] == 'L') {
      alpha = atoi(str + 1);
    }
    else if (str[0] == 'R') {
      ledR = atoi(str + 1);
    }
    else if (str[0] == 'G') {
      ledG = atoi(str + 1);
    }
    else if (str[0] == 'B') {
      ledB = atoi(str + 1);
    } else if (str[0] == '#') {
      color = strtol(str + 1, NULL, 16);
      ledR = getRed(color);
      ledG = getGreen(color);
      ledB = getBlue(color);
    }
  }


  if (alpha != -1) { // set brightness
    for (int i = 0; i < NUMPIXELS; i++) {

      unsigned long ledBrut = mem[i];
      struct color led;

      led.red   = getRed(ledBrut);
      led.green = getGreen(ledBrut);
      led.blue  = getBlue(ledBrut);

      RGBtoHSB(&led);
      led.brightness = normalize(alpha);
      HSBtoRGB(&led);
      /*
            // DEBUG
            Serial.print(led.red);
            Serial.print("  ");
            Serial.print(led.green);
            Serial.print("  ");
            Serial.println(led.blue);
      */
      pixels.setPixelColor(i, pixels.Color(led.red, led.green, led.blue));

    }
    pixels.show();
  } else {
    for (int i = 0; i < NUMPIXELS; i++) {
      setLight(i, ledR, ledG, ledB);
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
  }

  /*
    Serial.print(alpha);
    Serial.print("  ");
    Serial.print(ledR);
    Serial.print("  ");
    Serial.print(ledG);
    Serial.print("  ");
    Serial.println(ledB);
  */
}


void singleLight(char * cmd)
{
  char * tmp;
  char * str;
  str = strtok_r(cmd, " ", &tmp);
  int ledR = 0;
  int ledG = 0;
  int ledB = 0;
  int led = 0;

  while (str != NULL) {
    str = strtok_r(0, " ", &tmp);
    if (str[0] == 'R') {
      ledR = atoi(str + 1);
    }
    else if (str[0] == 'G') {
      ledG = atoi(str + 1);
    }
    else if (str[0] == 'B') {
      ledB = atoi(str + 1);
    }
    else if (str[0] == 'L') { // number of LED to be changed
      led = atoi(str + 1);
    }
  }
  /*
    Serial.print(ledR);
    Serial.print("  ");
    Serial.print(ledG);
    Serial.print("  ");
    Serial.print(ledB);
    Serial.print("  ");
    Serial.println(led);
  */
  setLight(led, ledR, ledG, ledB);
  pixels.show(); // This sends the updated pixel color to the hardware.

}

void turnOffLights() {
  for (int i = 0; i < NUMPIXELS; i++) {
    setLight(i, 0, 0, 0);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void turnONWhiteLights() {
  for (int i = 0; i < NUMPIXELS; i++) {
    setLight(i, 255, 255, 255);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void setLight(uint8_t n, uint8_t r, uint8_t g, uint8_t b) {
  // this function is wrapped as in some products rgb leds are not wired to RGB model but sometimes like RBG or similar
  // set here a good wiring for your leds

  mem[n] = getColorInt(r, g, b);
  pixels.setPixelColor(n, pixels.Color(r, g, b));
}


float normalize(int c) {
  return (1.0 / 255.0) * float(c);
}

unsigned long getColorInt(unsigned long r, unsigned long g, unsigned long b) {
  return (r << 16) | (g << 8) | b;
}

unsigned int getRed(unsigned long aa) {
  return (aa >> 16) & 0xFF;
}

unsigned int getGreen(unsigned long aa) {
  return (aa >> 8) & 0xFF;
}

unsigned int getBlue(unsigned long aa) {
  return (aa) & 0xFF;
}


