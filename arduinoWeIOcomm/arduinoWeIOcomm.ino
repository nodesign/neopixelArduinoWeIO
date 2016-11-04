///////////////////// NEOPIXEL INIT
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      20

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

///////////////////// NEOPIXEL INIT END


//////////////////////////////////////////////////////////////////////////
//
//   Example 1 : "A R255 G255 B255\n"
//   A - stands for all leds
//
//   Example 2 : "P R255 G255 B255 L9\n"
//   P - stands for specific led number defined by L parameter
//
//   It has to start with A or P other data order is not relevant
//   It has to finish with \n to be interpreted correctly
// 
//////////////////////////////////////////////////////////////////////////

char buf[64]; // max size that can be accepted in arduino
int8_t bufindex;

void setup() {
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.

  turnOffLights();
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

}


void parseCmd(char * cmd)
{
  if (cmd[0] == 'A') { // command all lights
    allLights(cmd);
  } else if (cmd[0] == 'P') { // command specific light
    singleLight(cmd);
  }
  Serial.println("OK");
}

void allLights(char * cmd)
{
  char * tmp;
  char * str;
  str = strtok_r(cmd, " ", &tmp);
  int ledR = 0;
  int ledG = 0;
  int ledB = 0;

  while (str != NULL) {
    str = strtok_r(0, " ", &tmp);
    if (str[0] == 'R') {
      ledR = atoi(str + 1);
    } else if (str[0] == 'G') {
      ledG = atoi(str + 1);
    } else if (str[0] == 'B') {
      ledB = atoi(str + 1);
    }
  }

/*
  Serial.print(ledR);
  Serial.print("  ");
  Serial.print(ledG);
  Serial.print("  ");
  Serial.println(ledB);
  
*/

  for (int i = 0; i < NUMPIXELS; i++) {
    setLight(i, ledR, ledG, ledB);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

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
    } else if (str[0] == 'G') {
      ledG = atoi(str + 1);
    } else if (str[0] == 'B') {
      ledB = atoi(str + 1);
    } else if (str[0] == 'L') { // number of LED to be changed
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
    setLight(i,0,0,0);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void turnONWhiteLights() {
  for (int i = 0; i < NUMPIXELS; i++) {
    setLight(i,255,255,255);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void setLight(uint8_t n, uint8_t r, uint8_t g, uint8_t b) {
  // this function is wrapped as in some products rgb leds are not wired to RGB model but sometimes like RBG or similar
  // set here a good wirting for your leds
  pixels.setPixelColor(n, pixels.Color(r, g, b)); // Moderately bright green color.
}
