// Andrew Cornelio & Vivek Gopalakrishnan
// acornel9 & vgopala4

// __Add your name and JHED above__
// ppm_io.c
// 601.220, Spring 2019
// Starter code for midterm project - feel free to edit/add to this file

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ppm_io.h"


/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp) {

    // check that fp is not NULL
    assert(fp);

    char header_line[500];
    int line = 0;
    char header[2] = "";
    int cols = 0;
    int rows = 0;
    int colors = 0;
    while (fgets(header_line, sizeof(header_line), fp)) {
        if (header_line[0] == '#') { // ignore comment line
            continue;
        }
        if (line == 0) {
            if(sscanf(header_line, "%s", header) != 1 || strcmp(header, "P6")) // first line must be P6
            return NULL;
        }
        else if (line == 1) {
            if(sscanf(header_line, "%i%i", &cols, &rows) != 2) // second line is:  columns rows
            return NULL;
        }
        else if (line == 2) {
            if(sscanf(header_line, "%i", &colors) != 1 || colors != 255) // third line must be 255
            return NULL;
            break;  // after this line the real input begins
        }
        line++;
    }

    Pixel* pix_array = malloc(sizeof(Pixel) * cols * rows);  // malloc array of Pixels
    fread(pix_array, sizeof(Pixel), rows * cols, fp); // not sure if this works - test

    if(ferror(fp)) {
        return NULL;
    }

    Image* readin = (Image *) malloc(sizeof(Image)); // malloc Image with a pointer and 2 ints

    readin->data = pix_array;
    readin->rows = rows;
    readin->cols = cols;

    rewind(fp); // allows you to read from same file twice??

    return readin;

}


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return 0 if successful and -1 otherwise
 */
int write_ppm(FILE *fp, const Image *im) {

    // check that fp is not NULL
    assert(fp);

    // write PPM file header, in the following format
    // P6
    // cols rows
    // 255
    fprintf(fp, "P6\n# Brought to you by Cat Corp.\n%d %d\n255\n", im->cols, im->rows);
    // No one will ever know... (=ΦｴΦ=)

    // now write the pixel array
    int num_pixels_written = fwrite(im->data, sizeof(Pixel), im->cols * im->rows, fp);

    if (num_pixels_written != im->cols * im->rows) {
        return 1;
    }

    rewind(fp);

    return 0;
}

/* Compare two image files to see if they are equal
 * Return 0 if equal, return 1 otherwise
 */
int comp_im(Image* imr, Image*  img) {
    if(!imr || !img) {
        return 1;
    }

    int rrows = imr->rows;
    int rcols = imr->cols;
    int grows = img->rows;
    int gcols = img->cols;

    Pixel* rpix = imr->data;
    Pixel* gpix = img->data;


    if(rrows != grows || rcols != gcols) {
        return 1;
    }

    int flag = 0;

    for(int i = 0; i < rrows; i++) {
        for(int j = 0; j < rcols; j++) {
            if(rpix[i * rcols + j].r != gpix[i * rcols + j].r || rpix[i * rcols + j].g != gpix[i * rcols + j].g || rpix[i * rcols + j].b != gpix[i * rcols + j].b) {
                printf("%i, %i\n", i, j);
                flag = 1;
            }
        }
    }

    return flag;
}



/* Destroy the pixel array and image in one function
 */
int destroy_im(Image* im) {
    if(im) {
        // Sucessfully destroyed image
        free(im->data);
        free(im);
        return 0;
    }
    else {
        // Image does not exist
        return -1;
    }
}
