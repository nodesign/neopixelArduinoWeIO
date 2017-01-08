//
//  colorModel.h
//  waelice
//

#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <avr/io.h>



struct color {
  uint8_t red,green,blue;
  float hue,saturation,brightness;
};

void HSBtoRGB(struct color *c);
void RGBtoHSB(struct color *c);

#endif // COLORMODEL_H



