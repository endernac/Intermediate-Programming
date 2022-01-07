// Andrew Cornelio & Vivek Gopalakrishnan
// acornel9 & vgopala4

#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H

#include <stdlib.h>
#include <math.h>
#include "ppm_io.h"

// Swap
int swap(Image* input);

// Invert
int invert(Image* input);

// Crop
int crop(Image* input, int top_col, int top_row, int bot_col, int bot_row);

// Edge Detection
unsigned char I(Pixel* pix, int cols, int x, int y);
int edges(Image* input, double sigma, double threshold);

// Brighten
unsigned char bound(double intensity);
int bright(Image* input, double brighting_value);

// Convert to greyscale
int grey(Image* input);

// Blur
int blur(Image* input, double sigma);

#endif
