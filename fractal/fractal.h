#ifndef _FRACTAL_H_
#define _FRACTAL_H_

#include "image.h"

/**
 * @brief Draws empty fractal, assuming image is clean
 *
 * @param picture 
 */
void empty_fractal(image_p picture);

/**
 * @brief Draws the Mandelbrot
 * @param picture Target image
 */
void mandelbrot_fractal(image_p picture);

/**
 * @brief Draws the Julia
 * @param picture Target image
 * @param c_re Real part of C
 * @param c_im Imaginary part of C
 */
void julia_fractal(image_p picture, float c_re, float c_im);

/**
 * @brief Draws the Sierpinski Carpet
 * @param picture Target image
 */
void sierpinski_carpet(image_p picture);

#endif // _FRACTAL_H_
