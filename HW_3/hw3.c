// Andrew Cornelio
// acornel9

#include <stdio.h>
#include <string.h>
#include "dnasearch.h"

/* This is the main file. It must (a) read a file name from the 
 * CL, (b) check the contents of the file is valid, (c) read the
 * contents of the file into an array, (d) read a list of strings
 * from stdin, (e) match the user inputted pattern strings to the
 * text string from the file, (f) display pattern strings with the
 * locations in the text string.
 */
int main(int argc, char* argv[]) {
  // TODO
  // OPEN FILE ON CL
  if(argc > 2) { // Make sure there is only one input file
    printf("Error: too many arguments\n");
    return 1;
  } else if(argc == 0) {
    printf("Error: no text file added\n");
  }


  // Read in the characters from the text file and return a null if invalid text or
  // capitalized text with no whitespace if it's valid 
  char* text = read_text(argv[1], 1501); 

  if(!text) {
    printf("Invalid text\n");
    return 3;
  }
  
  // TODO
  // READ USER INPUT PATTERN STRINGS
  char pattern[(int)sizeof(text)];  // patterns can only be as long as the text
  
  // Cycles through all the patterns inputted by the user and matches them to the text
  while(scanf("%s", pattern) == 1) {
    // Convert the pattern to uppercase 
    capitalize(pattern, (int)strlen(pattern));

    // Check validity
    if(!valid(pattern, (int)strlen(pattern), (int)strlen(text))) {
      printf("Invalid pattern\n"); 
      free(text);
      return 4;
    }

    // Match the pattern to the text and get back all the occurences
    int match = pattern_match(text, strlen(text), pattern, strlen(pattern), 0);
    
    // Print all the pattern followed by the index of the occurences
    printf("%s", pattern);
    
    int k = 0;
    while(match != -1) {
      printf(" %i", match);
      match = pattern_match(text, strlen(text), pattern, strlen(pattern), match + 1);
      k++;
    }
    if(k == 0) {
      printf(" Not found"); // If there are no matches print not found
    }

    printf("\n");
  }
  free(text);
  return 0;
}
