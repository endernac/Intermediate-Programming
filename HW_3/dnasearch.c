// Andrew Cornelio
// acornel9

#include "dnasearch.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Return value is the first offset *greater than or equal to* start_at
// where pattern occurs in text.  Returns -1 if there is no such
// occurrence.
int pattern_match(const char t[], int tlen, const char p[], int plen, int start_at){
  // Set a variable that determines if a substring of text matches pattern
  int match = 0;

  // There can be tlen matches if a pattern is a single letter and the text is only that letter
  int occ = -1;

  // Iterates upto the last valid index. Note the 1 is necessary because
  // tlen - plen = (last_valid_text_index + 1) - (last_valid_pattern_index + 1)
  // = last_valid_text_index - last_valid_pattern_index
  // However, if we only use a less than, we do not actually include it, only 1 less
  // than it.
  for(int i = start_at; i < tlen - plen + 1; i++) {
    // Set a match to true by default, iterate through the pattern, and if it doesn't
    // match, break out 
    match = 1;
    for(int j = 0; j < plen; j++) {
      if(p[j] != t[i+j]) {
        match = 0;
        break;
      }
    }
    
    // If it actually matches, mission is complete- update occ and break from loop
    if(match == 1) {
      occ = i;
      break;
    }
  }
  
  // Return the occurence or -1
  return occ;
}

// Convert the pattern to uppercase 
void capitalize(char s[], int len) {
  for(int j  = 0; j < len; j++) {
    s[j] = toupper(s[j]);
  }
}

// Returns 1 if the string is valid and 0 if it isn't
int valid(const char s[], int slen, int dlen) {
  // string length must be less than or equal to desired length
  if(slen > dlen) {
    return 0;
  }
  
  // Characters can only be A, T, G, or C
  for(int i = 0; i < slen; i++) {
    if(!(s[i] == 'A' || s[i] == 'T' || s[i] == 'G' || s[i] == 'C' || s[i] == '\0')) {
      return 0;
    }
  }

  // string cannot be empty or have negative length
  if(slen <= 0) {
    return 0;
  }

  return 1;
}

// Takes a file as input and the desired length of the string and returns the string if it is valid and NULL if it is not
char* read_text(char* input_text, int slen) {
  
  FILE* input = fopen(input_text, "r");
  if(!input || ferror(input)) { // check in input file is valid
    return NULL;
  }
  
  // Variable to copy text into array
  char base;
  // Array containing all the characters
  char* str = malloc(slen);
  // counter to track position in array
  int i = 0;


  // Read in characters from stdio and store non whitespace characters
  int baseCollected = fscanf(input, "%c", &base);

  while(baseCollected == 1 && i < slen) {
    // Add capitalized non whitespace characters to array
    if(!isspace(base)) {
      str[i] = toupper(base);
      i++;
    }
    baseCollected = fscanf(input, "%c", &base);
  }
  
  fclose(input);

  str[i] = '\0'; // Incase the last charater isn't a null
  
  // we need to use count because it both counts whitespace not in text and tracks the 'true' string length > slen
  if(!valid(str, i - 1, slen) || baseCollected != -1) { 
    free(str);  // Need to free it here or it is lost forever
    return NULL;  // return null pointer
  }

  return str;
}
