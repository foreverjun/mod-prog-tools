#include <math.h>
#include <assert.h>
#include "image.h"
#include "fractal.h"

#define MAX_ITER 255

static pixel_data calculate_pixel_value(int iter)
{
    if (iter == MAX_ITER) return 0;
    
    return (pixel_data)(iter % 255);
}

void sierpinski_carpet(image_p picture)
{
    assert(picture != NULL);
    assert(get_width(picture) > 0 && get_height(picture) > 0);

    pixel_coord w = get_width(picture);
    pixel_coord h = get_height(picture);

    for (pixel_coord py = 0; py < h; ++py) {
        for (pixel_coord px = 0; px < w; ++px) {

            pixel_coord x = px;
            pixel_coord y = py;
            int is_empty = 0;

            while (x > 0 || y > 0) {
                if ((x % 3 == 1) && (y % 3 == 1)) {
                    is_empty = 1;
                    break;
                }
                x /= 3;
                y /= 3;
            }

            set_pixel(picture, px, py, is_empty ? 0 : 255);
        }
    }
}

void mandelbrot_fractal(image_p picture)
{
    assert(picture != NULL);
    
    pixel_coord w = get_width(picture);
    pixel_coord h = get_height(picture);
    
    for (pixel_coord py = 0; py < h; ++py) {
        for (pixel_coord px = 0; px < w; ++px) {
            float x0 = (float)px / w * 3.5f - 2.5f;
            float y0 = (float)py / h * 2.0f - 1.0f;
            
            float x = 0.0f;
            float y = 0.0f;
            int i = 0;

            while ((x*x + y*y <= 4.0f) && (i < MAX_ITER)) {
                float xtemp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xtemp;
                i++;
            }

            set_pixel(picture, px, py, calculate_pixel_value(i));
        }
    }
}

void julia_fractal(image_p picture, float c_re, float c_im)
{
    assert(picture != NULL);

    pixel_coord w = get_width(picture);
    pixel_coord h = get_height(picture);

    float moveX = 0.0f, moveY = 0.0f;

    for (pixel_coord py = 0; py < h; ++py) {
        for (pixel_coord px = 0; px < w; ++px) {
            float newRe = 1.5f * (px - w / 2.0f) / (0.5f * w) + moveX;
            float newIm = (py - h / 2.0f) / (0.5f * h) + moveY;

            int i = 0;
            while ((newRe * newRe + newIm * newIm <= 4.0f) && (i < MAX_ITER)) {
                float oldRe = newRe;
                float oldIm = newIm;
                newRe = oldRe * oldRe - oldIm * oldIm + c_re;
                newIm = 2 * oldRe * oldIm + c_im;
                i++;
            }

            set_pixel(picture, px, py, calculate_pixel_value(i));
        }
    }
}

void empty_fractal(image_p picture)
{
    (void)(picture);
}
