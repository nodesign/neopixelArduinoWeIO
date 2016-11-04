# Drive Neopixels directly from Web using WeIO and Arduino boards
This is example of communicating from Web to Neopixels using WeIO + Arduino boards.
Neopixel low level driver existes for Arduino but not for WeIO. As it demands a huge work of time to port it to LPC processor (that was used in WeIO as coprocessor) the connection is established using one Arduino connected to WeIO.
# Installation
1. Install Neopixels driver into Arduino https://github.com/adafruit/Adafruit_NeoPixel
2. Compile and upload arduinoWeIOcomm.ino to Arduino board https://github.com/nodesign/neopixelArduinoWeIO/blob/master/arduinoWeIOcomm/arduinoWeIOcomm.ino
3. Create new project inside WeIO and copy file by file inside it from https://github.com/nodesign/neopixelArduinoWeIO/tree/master/neopixelWeIO

