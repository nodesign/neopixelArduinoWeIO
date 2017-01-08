//
//  colorModel.c
//  waelice

#include "colorModel.h"
#include <math.h>

/**
 * Converts the components of a color, as specified by the HSB 
 * model, to an equivalent set of values for the default RGB model. 
 * <p>
 * The <code>saturation</code> and <code>brightness</code> components
 * should be floating-point values between zero and one
 * (numbers in the range 0.0-1.0).  The <code>hue</code> component
 * can be any floating-point number.  The floor of this number is
 * subtracted from it to create a fraction between 0 and 1.  This
 * fractional number is then multiplied by 360 to produce the hue
 * angle in the HSB color model.
 * <p>
 * The integer that is returned by <code>HSBtoRGB</code> encodes the 
 * value of a color in bits 0-23 of an integer value that is the same 
 * format used by the method {@link #getRGB() <code>getRGB</code>}.
 * This integer can be supplied as an argument to the
 * <code>Color</code> constructor that takes a single integer argument. 
 * @param     hue   the hue component of the color
 * @param     saturation   the saturation of the color
 * @param     brightness   the brightness of the color
 * @return    the RGB value of the color with the indicated hue, 
 *                            saturation, and brightness.
 * @see       java.awt.Color#getRGB()
 * @see       java.awt.Color#Color(int)
 * @see       java.awt.image.ColorModel#getRGBdefault()
 * @since     JDK1.0
 */
void HSBtoRGB(struct color *c) {

    if (c->saturation == 0) {
        c->red = c->green = c->blue = (int) (c->brightness * 255.0f + 0.5f);
    } 
    else {
        float h = (c->hue - (float)floor(c->hue)) * 6.0f;
        float f = h - (float)floor(h);
        float p = c->brightness * (1.0f - c->saturation);
        float q = c->brightness * (1.0f - c->saturation * f);
        float t = c->brightness * (1.0f - (c->saturation * (1.0f - f)));
        switch ((int) h) {
            case 0:
                c->red = (int) (c->brightness * 255.0f + 0.5f);
                c->green = (int) (t * 255.0f + 0.5f);
                c->blue = (int) (p * 255.0f + 0.5f);
                break;
            case 1:
                c->red = (int) (q * 255.0f + 0.5f);
                c->green = (int) (c->brightness * 255.0f + 0.5f);
                c->blue = (int) (p * 255.0f + 0.5f);
                break;
            case 2:
                c->red = (int) (p * 255.0f + 0.5f);
                c->green = (int) (c->brightness * 255.0f + 0.5f);
                c->blue = (int) (t * 255.0f + 0.5f);
                break;
            case 3:
                c->red = (int) (p * 255.0f + 0.5f);
                c->green = (int) (q * 255.0f + 0.5f);
                c->blue = (int) (c->brightness * 255.0f + 0.5f);
                break;
            case 4:
                c->red = (int) (t * 255.0f + 0.5f);
                c->green = (int) (p * 255.0f + 0.5f);
                c->blue = (int) (c->brightness * 255.0f + 0.5f);
                break;
            case 5:
                c->red = (int) (c->brightness * 255.0f + 0.5f);
                c->green = (int) (p * 255.0f + 0.5f);
                c->blue = (int) (q * 255.0f + 0.5f);
                break;
        }
    }
    
}

/**
 * Converts the components of a color, as specified by the default RGB 
 * model, to an equivalent set of values for hue, saturation, and 
 * brightness that are the three components of the HSB model. 
 * <p>
 * If the <code>hsbvals</code> argument is <code>null</code>, then a 
 * new array is allocated to return the result. Otherwise, the method 
 * returns the array <code>hsbvals</code>, with the values put into 
 * that array. 
 * @param     r   the red component of the color
 * @param     g   the green component of the color
 * @param     b   the blue component of the color
 * @param     hsbvals  the array used to return the 
 *                     three HSB values, or <code>null</code>
 * @return    an array of three elements containing the hue, saturation, 
 *                     and brightness (in that order), of the color with 
 *                     the indicated red, green, and blue components.
 * @see       java.awt.Color#getRGB()
 * @see       java.awt.Color#Color(int)
 * @see       java.awt.image.ColorModel#getRGBdefault()
 * @since     JDK1.0
 */

void RGBtoHSB(struct color *c) {
    int cmax = (c->red > c->green) ? c->red : c->green;
    if (c->blue > cmax) cmax = c->blue;
    int cmin = (c->red< c->green) ? c->red : c->green;
    if (c->blue < cmin) cmin = c->blue;
    
    c->brightness = ((float) cmax) / 255.0f;
    if (cmax != 0)
        c->saturation = ((float) (cmax - cmin)) / ((float) cmax);
    else
        c->saturation = 0;
    if (c->saturation == 0)
        c->hue = 0;
    else {
        float redc = ((float) (cmax - c->red)) / ((float) (cmax - cmin));
        float greenc = ((float) (cmax - c->green)) / ((float) (cmax - cmin));
        float bluec = ((float) (cmax - c->blue)) / ((float) (cmax - cmin));
        if (c->red== cmax)
            c->hue = bluec - greenc;
        else if (c->green == cmax)
            c->hue = 2.0f + redc - bluec;
        else
            c->hue = 4.0f + greenc - redc;
        c->hue = c->hue / 6.0f;
        if (c->hue < 0)
            c->hue = c->hue + 1.0f;
    }
}


