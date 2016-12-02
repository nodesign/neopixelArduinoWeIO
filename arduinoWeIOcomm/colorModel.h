//
//  colorModel.h
//  waelice
//
//  Created by uros petrevski on 07/10/12.
//  Copyright 2012 NoDesign. All rights reserved.
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


