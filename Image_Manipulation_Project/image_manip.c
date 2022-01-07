// Andrew Cornelio & Vivek Gopalakrishnan
// acornel9 & vgopala4

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ppm_io.h"
#include "image_manip.h"

#define PI 3.1415926535897932384

/*
ORDER OF FUNCTIONS
1. Swap
2. Invert
3. Crop
4. Edge Detection
5. Bright
6. Greyscale
7. Blur
*/


// 1. Swap

int swap(Image* input) {

    /* Swaps the color channels for the pixel values for the image struct in
    place as follows: green --> red --> blue --> green */

    // Get the size of the array
    int size = input->rows * input->cols;

    // Get pointer to image data
    Pixel* pix = input->data;

    // Create temporary varable for swapping
    char temp;

    // Loop through the array and perform basic 3 variable swap
    for (int i = 0; i < size; i++) {
        temp = pix[i].b;
        pix[i].b = pix[i].r;
        pix[i].r = pix[i].g;
        pix[i].g = temp;
    }

    // Return 0 to indicate no errors were thrown
    return 0;

}


// 2. Invert

int invert(Image* input) {

    // Get the size of the array
    int size = input->rows * input->cols;

    // Get pointer to image data
    Pixel* pix = input->data;

    // For each pixel in the array, store the complement of each color channel
    for (int i = 0; i < size; i++) {
        pix[i].b = 255 - pix[i].b;
        pix[i].r = 255 - pix[i].r;
        pix[i].g = 255 - pix[i].g;
    }

    // Return 0 to indicate no errors were thrown
    return 0;

}


// 3. Crop

int crop(Image* input, int top_col, int top_row, int bot_col, int bot_row) {
    // Save values of dimensions from old image
    int in_rows = input->rows;
    int in_cols = input->cols;

    /* Check whether:
        1) Top left corner out of bounds on left or top
        2) Top right corner out of bounds on right or bottom
        3) Top right corner lower or more right than bottom left corner
    */
    if(top_col < 0 || top_row < 0 || bot_col > in_cols || bot_row > in_rows || top_row > bot_row || top_col > bot_col) {
        return 1;
    }

    // Save values of dimensions for new image
    int new_rows = bot_row - top_row;
    int new_cols = bot_col - top_col;

    // Give the old Pixel array an easier name, and create a new array with the new dimensions
    Pixel* pix_in = input->data; //array of pixels is passed py pointer, so can access pixel values directly
    Pixel* pix_new = (Pixel*) malloc(sizeof(Pixel) * new_rows * new_cols);

    for(int i = 0; i < new_rows; i++) {
        for(int j = 0; j < new_cols; j++) {
            pix_new[i * new_cols + j].b = pix_in[(top_row + i) * in_cols + (j + top_col)].b;
            pix_new[i * new_cols + j].r = pix_in[(top_row + i) * in_cols + (j + top_col)].r;
            pix_new[i * new_cols + j].g = pix_in[(top_row + i) * in_cols + (j + top_col)].g;
        }
    }

    free(pix_in);

    input->rows = new_rows;
    input->cols = new_cols;
    input->data = pix_new;

    // Return 0 to indicate no errors were thrown
    return 0;

}


// 4. Edge Detection

unsigned char I(Pixel* pix, int cols, int x, int y) {
    /* Get the intensity of a pixel at a given (x,y) location in the image.
    Because the image has been converted to greyscale, all channels have the
    same value. Therefore, return only the intensity of the red channel. */
    return pix[x * cols + y].g;
}

int edges(Image* input, double sigma, double threshold) {
    /* Use the Canny edge detection algorithm to detect edges in an image. */

    /* Step 1: Convert image to greyscale */
    grey(input);

    /* Step 2: Denoise the image by blurring it. Check to make sure an error
    wasn't thrown while trying to blur the image. Make sure threshold >= 0*/
    if (threshold <= 0  || blur(input, sigma)) {
        return 1;
    }

    /* Step 3: Compute the intensity gradient for each non-boundary pixel */

    // Get dimensions of image
    int rows = input->rows;
    int cols = input->cols;

    // Get array of pixels and make a new array to store new values
    Pixel* pix = input->data;
    Pixel* pix2 = (Pixel *) malloc(sizeof(Pixel) * rows * cols);

    // Iterate over pixels
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Check if array is on boundary
            if(i == 0 || j == 0 || i == rows - 1 || j == cols - 1) {
                pix2[i * cols + j].r = pix[i * cols + j].r;
                pix2[i * cols + j].g = pix[i * cols + j].g;
                pix2[i * cols + j].b = pix[i * cols + j].b;
            }
            else {
                // Calculate the intensity gradient in the x- and y- directions
                double I_x =  (I(pix, cols, i, j + 1) - I(pix, cols, i, j - 1)) / 2.0;
                double I_y =  (I(pix, cols, i + 1, j) - I(pix, cols, i - 1, j)) / 2.0;

                // Get the magnitude of the gradient at (i,j)
                double I_mag = sqrt(pow(I_x, 2) + pow(I_y, 2));

                // Threshold the image by its gradient
                if (I_mag > threshold) {
                    pix2[i * cols + j].r = 0;
                    pix2[i * cols + j].g = 0;
                    pix2[i * cols + j].b = 0;
                } else {
                    pix2[i * cols + j].r = 255;
                    pix2[i * cols + j].g = 255;
                    pix2[i * cols + j].b = 255;
                }
            }
        }
    }

    // Step 4: free old array and set field to new array
    // Return 0 to indicate no errors were thrown
    free(pix);
    input->data = pix2;
    return 0;

}


// 5. Bright

unsigned char bound(double intensity) {
    /* Bound the pixel intensity value so that it is within [0,225] */

    if (0 <= intensity && intensity <= 255) {
        return (unsigned char)intensity;
    } else if (intensity < 0) {
        return (unsigned char)0;
    } else {
        return (unsigned char)255;
    }
}

int bright(Image* input, double brighting_value) {
    /* Brighten the image by a given amount */

    // Get the size of the array
    int size = (input->rows) * (input->cols);

    // Get pointer to image data
    Pixel* pix = input->data;

    // Loop through pixel array and add brightness value
    for (int i = 0; i < size; i++) {
        pix[i].r = bound(pix[i].r + (int)brighting_value);
        pix[i].g = bound(pix[i].g + (int)brighting_value);
        pix[i].b = bound(pix[i].b + (int)brighting_value);
    }

    // Return 0 to indicate no errors were thrown
    return 0;

}


// 6. Greyscale

int grey(Image* input) {
    /* Convert an image to greyscale */

    // Get the size of the array
    int size = input->rows * input->cols;

    // Get pointer to image data
    Pixel* pix = input->data;

    /* For each pixel in the array, calculate the greyscale value according to
    the NTSC standard conversion formula. Then write this greyscale value to
    every channel in the pixel. */
    for(int i = 0; i < size; i++) {
        unsigned char grey = 0.30*pix[i].r + 0.59*pix[i].g + 0.11*pix[i].b;
        pix[i].r = grey;
        pix[i].g = grey;
        pix[i].b = grey;
    }

    // Return 0 to indicate no errors were thrown
    return 0;

}


// 7. Blur
/* I didn't see the point in splitting blur into multiple functions since it
 * was realtively straight forward to write if you split it into segments and
 * wrote each part by segment. In addition, depending on what helper functions
 * you created, you might end upe with O(n^2) to O(m^2*n^2) function calls
 * that are completely unnecessary. It seems unreasonable to sacrifice that
 * much efficiency for the sake of easier understanding.
 */

int blur(Image* input, double sigma) {
    /* Blur an image using a Gaussian filter with a given variance */

    // Part 0: make sure sigma is positive and return error otherwise
    if(sigma <= 0) {
        return 1;
    }

    // Part 1: determine the size of the filter given the sigma value
    // multiply sigma by 10 and round up
    int n = (10.0 * sigma + .5);
    // make sure sigma is odd so filter has a center
    if(n % 2 == 0) {
        n++;
    }
    // find the center- useful for rest of the function
    int m = n / 2;

    // Part 2: create the 2D filter using the size from Part 1
    double filter[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            // Formula taken from documentation. SQR is defined as a macro. So is PI.
            // The Gaussian filter is symmetric, so only iterate over the upper triangular matrix.
            double gauss = 1.0/(2.0 * PI * pow(sigma, 2)) * exp(-(pow(m - i, 2) + pow(m - j, 2)) / (2.0 * pow(sigma, 2)));
            filter[i][j] = gauss;
            filter[j][i] = gauss;
        }
    }

    // Part 3: (hard part) convolve image with filter
    // Part 3a: Initialize all relevant quantities
    // Set aside rows and columns in image to make future reference easier
    int rows = input->rows;
    int cols = input->cols;

    // Set aside the Pixel array from the given image and a new Pixel array as standard
    Pixel* pix = input->data;
    Pixel* pix2 = (Pixel*) malloc(sizeof(Pixel) * rows * cols);

    // Initialize the value of the pixel sums and filter norm to be used in convolution
    double r_sum = 0;
    double g_sum = 0;
    double b_sum = 0;
    double norm = 0;

    // Part 3b: Loop through all the pixels in the image
    /* Note that the Pixel array is 1D, but due to the 2D nature of images, it
    makes sense to use nested loops as if the array were 2D. This also is
    especially helpful when dealing with the filter, which is 2D. Although it is
    possible to use a single for loop, there is no significant advantage as the
    number of iterations is unchanged. Ultimately, it would would just lead to
    messier expressions as the row and column number would have to be deduced
    from the single index on every iteration, rather than just having them off
    the bat. Finally, while this all might have been avoided by simply copying
    the 1D pixel array into a 2D array, it turns out that using 2 indices on a
    1D array is not too different from using 2 indices on a 2D array, so
    complexity is not that much of an issue. Again, I believe this is an
    efficiency, understandability tradeoff, and the gain in understandability is
    not worth the loss in efficiency. */

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
        /* Part 3b.1: Determine how close the current pixel it to an edge, and
        set appropriate bounds to be used in the summation. Originally, I had
        separated edge cases (literally!) from the standard case where you could
        sum over the entire filter, but combining them turns out to be more
        natural and general. */
        int left = -m;
        int right = m;
        int up = -m;
        int down = m;

        if(i - m < 0) {
            up = -i;
        }
        if(rows <= i +  m) {
            down = rows - i - 1;
        }
        if(j - m < 0) {
            left = -j;
        }
        if(cols <= j + m) {
            right = cols - j - 1;
        }

        // Part 3b.2: Remember to reset the sums and norm for each iteration to
        // avoid runaway!
        r_sum = 0;
        g_sum = 0;
        b_sum = 0;
        norm = 0;

        // Part 3b.3: (Actual convolution) loop through the bounds of the filter
        // (determined in 3b.1), sum the scaled pixel values, and increment the norm
        // Note that the 2D indeces for the image and the 2D indeces for the filter
        // make for relatively nice looking expressions.
        for(int r = up; r < down + 1; r++) {
            for(int s = left; s < right + 1; s++) {
                r_sum = r_sum + filter[m + r][m + s] * pix[(i + r) * cols + (j + s)].r;
                g_sum = g_sum + filter[m + r][m + s] * pix[(i + r) * cols + (j + s)].g;
                b_sum = b_sum + filter[m + r][m + s] * pix[(i + r) * cols + (j + s)].b;
                norm = norm + filter[m + r][m + s];
            }
        }

        // Part 3b.3: (technically still part of the convolution) Set the values in the
        // new pixel array to the normalized sums computed in the previous step.
        pix2[i * cols + j].r = (int)(r_sum / norm);
        pix2[i * cols + j].g = (int)(g_sum / norm);
        pix2[i * cols + j].b = (int)(b_sum / norm);
        }
    }

    // Part 4: Free the old array and substitute the new array as standard
    free(pix);
    input->data = pix2;

    // Return 0 to indicate no errors were thrown
    return 0;

    // Part 5: Celebrate
    // ┌(ﾟдﾟ)┘

}
