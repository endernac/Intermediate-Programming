// Andrew Cornelio & Vivek Gopalakrishnan
// acornel9 & vgopala4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_io.h"
#include "image_manip.h"


int process(int num, char *args[]) {
    // First check argc has more than 2 args and second and third args are ppm files
    if(num < 3 || !strstr(args[1], ".ppm") || !strstr(args[2], ".ppm")) {
        printf("Failed to supply ppm input filename or output filename, or both\n");
        return 1;
    }

    // Open file if it valid
    FILE *fi = fopen(args[1], "r");
    if (!fi) {
        printf("Specified input file could not be opened\n");
        return 2;
    }

    // Read file to Image struct if it PPM file is valid
    // read_ppm returns NULL if unsuccessful
    Image *im = read_ppm(fi);
    if(!im) {
        fclose(fi);
        printf("Specified input file is not a properly-formatted PPM file, or reading input somehow fails\n");
        return 3;
    }

    // Flag to see if manipulation was specified
    int manip_flag = 0;

    // Flag to see if number and type of arguments passed to function were correct
    int n_flag = 0;

    // Flag to see if the operations were successful (or if arguments didn't make sense)
    int op_flag = 0;

    // See if the user input a manipulation keyword and perform the manipulation if it is valid and parameters are
    // correct
    if(num < 4) {
        manip_flag = 1;
    }
    else if(strcmp(args[3], "swap") == 0) {
        // User wants to swap
        if(num != 4) {
            n_flag = 1;
        }
        else {
            // Perform swap
            op_flag = swap(im);
        }
    }
    else if(strcmp(args[3], "bright") == 0) {
        // User wants to brighten
        double change = 0;

        if(num != 5 || !sscanf(args[4], "%lf", &change)) {  // Could use demorgan, but I prefer this
            n_flag = 1;
        }
        else {
            // Perform brighten
            op_flag = bright(im, change);
        }
    }
    else if(strcmp(args[3], "invert") == 0) {
        // User wants to invert

        if(num != 4) {
            n_flag = 1;
        }
        else {
            // Perform invert
            op_flag = invert(im);
        }
    }
    else if(strcmp(args[3], "gray") == 0) { // Why you spell with a?????
        // User wants to grey

        if(num != 4) {
            n_flag = 1;
        }
        else {
            // Perform grey
            op_flag = grey(im);
        }
    }
    else if(strcmp(args[3], "crop") == 0) {
        // User wants to crop

        int top_left = 0;
        int top_up = 0;
        int bot_right = 0;
        int bot_down = 0;

        if(num != 8 || !sscanf(args[4], "%d", &top_left) || !sscanf(args[5], "%d", &top_up) || !sscanf(args[6], "%d", &bot_right) || !sscanf(args[7], "%d", &bot_down)) {
            n_flag = 1;
        }

        // check if input contains '.' meaing it is a float/double
        else if(strchr(args[4], '.') || strchr(args[5], '.') || strchr(args[6], '.') || strchr(args[7], '.')) {
            n_flag = 1;
        }
        else {
            // Check parameters and perform crop
            op_flag = crop(im, top_left, top_up, bot_right, bot_down);
        }
    }
    else if(strcmp(args[3], "blur") == 0) {
        // User wants to blur
        double sigma = 0;

        if(num != 5 || !sscanf(args[4], "%lf", &sigma)) {
            n_flag = 1;
        }
        else {
            // Check parameters and perform blur
            op_flag = blur(im, sigma);
        }
    }
    else if(strcmp(args[3], "edges") == 0) {
        // User wants to detect edges

        double sigma = 0;
        double threshold = 0;

        if(num != 6 || !sscanf(args[4], "%lf", &sigma) || !sscanf(args[5], "%lf", &threshold)) {
            n_flag = 1;
        }
        else {
            // Check parameters and perform edge detect
            op_flag = edges(im, sigma, threshold);
        }
    }
    else {
        // Operation does not match any keywords
        manip_flag = 1;
    }

    // no manipulation provided or it doesn't match
    if(manip_flag) {
        fclose(fi);
        destroy_im(im);
        printf("No operation name was specified, or operation name specified was invalid\n");
        return 4;
    }

    // Number of Arguments passed to function were in correct
    if(n_flag) {
        fclose(fi);
        destroy_im(im);
        printf("Incorrect number of arguments or kind of arguments specified for the specified operation\n");
        return 5;
    }

    // Arguments did not make sense for specified function
    if(op_flag) {
        fclose(fi);
        destroy_im(im);
        printf("Arguments for the specified operation were out of range for the given input image, or otherwise senseless\n");
        return 6;
    }

    // Open output file
    FILE *fo = fopen(args[2], "wb");
    int write_flag = 0;
    if(!fo) {
        write_flag = 1;
    }
    else {
        if(write_ppm(fo, im)) {
            // Try to write image to output file
            // Destroy output and everything else othterwise
            fclose(fo);
            write_flag = 1;
        }
    }

    if(write_flag) {
        fclose(fi);
        destroy_im(im);
        printf("Specified output file could not be opened for writing, or writing output somehow fails\n");
        return 7;
    }


    // We gucci
    fclose(fi);
    fclose(fo);
    destroy_im(im);
    printf("Image Manipulation Successful\n");
    return 0;
}


int main(int argc, char *argv[]) {
    int flag = process(argc, argv);
    return flag;
}
