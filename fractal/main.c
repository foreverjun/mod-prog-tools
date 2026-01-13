#include <stdio.h>
#include "image.h"
#include "fractal.h"

int main()
{
    image_p img = create_image(800, 800);

    printf("Generating Sierpinski Carpet...\n");
    sierpinski_carpet(img);
    save_pgm(img, "sierpinski.pgm");

    clear_image(img);

    printf("Generating Mandelbrot...\n");
    mandelbrot_fractal(img);
    save_pgm(img, "mandelbrot.pgm");

    clear_image(img);

    printf("Generating Julia...\n");
    julia_fractal(img, -0.7f, 0.27015f);
    save_pgm(img, "julia.pgm");

    free_image(img);
    return 0;
}