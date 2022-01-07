// Andrew Cornelio
// acornel9

#include "dnasearch.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match.
 */
int fileeq(char lhsName[], char rhsName[]) {
    FILE* lhs = fopen(lhsName, "r");
    FILE* rhs = fopen(rhsName, "r");

    // don't compare if we can't open the files
    if (lhs == NULL || rhs == NULL) return 0;

    int match = 1;
    // read until both of the files are done or there is a mismatch
    while (!feof(lhs) || !feof(rhs)) {
        if (feof(lhs) ||                  // lhs done first
            feof(rhs) ||                  // rhs done first
            (fgetc(lhs) != fgetc(rhs))) { // chars don't match
            match = 0;
            break;
        }
    }
    fclose(lhs);
    fclose(rhs);
    return match;
}

// pattern test works on valid strings
int test_pattern_match(char in[], char text[], int expect[], int elen) {
    capitalize(in, (int)strlen(in));

    // Match the pattern to the text and get back all the occurences
    int match = pattern_match(text, strlen(text), in, strlen(in), 0);
    
    int k = 0;
    while(match != -1) {
      if(match != expect[k]) {
        return 0;
      }
      match = pattern_match(text, strlen(text), in, strlen(in), match + 1);
      k++;
    }
    if(k == 0 && elen !=0) {
      return 0;
    }

    return 1;
}

int streq(char s1[], char s2[], int slen) {
  for(int i = 0; i < slen; i++) {
    if(s1[i] != s2[i]) {
      return 0;
    }
  }
  return 1;
}


/* This file must test all the cases for all the functions
 * in dnasearch.c. We will carry out checks via assert 
 * statements. 
 */

int main() {
  /*
  // pattern_match
  // test function on sample data from document (note: must use caps)
  char seq[] = "CATATTACGATTACA";
  char pat0[] = "CAT";
  char pat1[] = "TAC";
  char pat2[] = "CGA";
  char pat3[] = "GGG";
  char pat4[] = "TTA";
  char pat5[] = "GC";
  char pat6[] = "A";
  char pat7[] = "ATTAC";

  int matches0[] = {0};
  int matches1[] = {5,11};
  int matches2[] = {7};
  int matches3[] = {0}; // technically array is empty but c won't accept empty array, handled in arrlen argument of arreq
  int matches4[] = {4,10};
  int matches5[] = {0}; // same as matches3
  int matches6[] = {1,3,6,9,12,14};
  int matches7[] = {3,9};
  
  assert(test_pattern_match(pat0, seq, matches0, 1));
  assert(test_pattern_match(pat1, seq, matches1, 2));
  assert(test_pattern_match(pat2, seq, matches2, 1));
  assert(test_pattern_match(pat3, seq, matches3, 0));
  assert(test_pattern_match(pat4, seq, matches4, 2));
  assert(test_pattern_match(pat5, seq, matches5, 0));
  assert(test_pattern_match(pat6, seq, matches6, 6));
  assert(test_pattern_match(pat7, seq, matches7, 2));


  // valid
  // Note: valid will only work for capital A, T, G, C
  assert(!valid("abCdsd3fdf    DAAFRRftaC attC", 26, 27)); // make the third argument greater than second to ensure that arg2 <= arg3 isn't causing a problem
  
  assert(!valid("aCtG	gTa  g", 11, 13)); // can't have spaces, or lowercases

  assert(!valid("aCtggTag", 8, 9)); // can't have lower cases

  assert(valid("ACTGGTAG", 8, 9)); // should be true

  assert(valid("ACTGGTAG", 8, 8)); // As long as arg2 not greater than arg3

  assert(!valid("ACTGGTAGB", 9, 10)); // Random B will make it false

  assert(!valid("ACTGGTAG", 0, 8)); // function interprets string to have length 0 and it will return false

  assert(!valid("ACTGGTAG", 7, 6)); // function should think the string is longer than the desired length and will be false




  // capitalize
  // This is a relatively simply function and doesn't need much testing
  char str[] = "abCdsd3fdf	DAAFRRftaC attC";
  capitalize(str, 26);
  assert(strcmp(str, "ABCDSD3FDF	DAAFRRFTAC ATTC") == 0);



  // read_text
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // checks if read_text can read a file with 1500 bases and whitespace 
  
  FILE* check1i = fopen("check1in.txt", "w");
  char correct_text[1501];

  for(int i = 0; i < 1500; i++) {
    float f = (float)rand()/(float)(RAND_MAX); // Want completely random text files with a,t,c,g (capitalization is irrelevant)
    if(f < 0.25) {
      fprintf(check1i, "a ");
      correct_text[i] = 'A';
    } else if(f < 0.50) {
      fprintf(check1i, "g\t");
      correct_text[i] = 'G';
    } else if(f < 0.75) {
      fprintf(check1i, "C\n");
      correct_text[i] = 'C';
    } else {
      fprintf(check1i, "t");
      correct_text[i] = 'T';
    }
  }
  
  correct_text[1501] = '\0';
  fclose(check1i);

  char* text1 = read_text("check1in.txt", 1501);     

  assert(streq(text1, correct_text, strlen(text1))); // see if text reader can read in 1500 A's. It should ignore spaces.
  free(text1);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // checks if it detects when the nonwhitespace length is longer than 1501

  FILE* check2i = fopen("check2in.txt", "w");

  for(int i = 0; i < 1501; i++) {
    float f = (float)rand()/(float)(RAND_MAX);
    if(f < 0.25) {
      fprintf(check1i, "a ");
    } else if(f < 0.50) {
      fprintf(check1i, "g\t");
    } else if(f < 0.75) {
      fprintf(check1i, "C\n");
    } else {
      fprintf(check1i, "t");
    }
  }
  fclose(check2i);

  // Note: read_text includes an extra character for the null terminator, but can only store 1500 bases
  char* text2 = read_text("check2in.txt", 1501);  

  assert(!text2); // see if text reader returns null since input text has more than 1500 bases (1501)
  free(text2);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // checks if it detects non atcg characters

  FILE* check3i = fopen("check3in.txt", "w");

  for(int i = 0; i < 1500; i++) { //should be the right number of characters
    float f = (float)rand()/(float)(RAND_MAX);
    if(f < 0.25) {
      fprintf(check3i, "a ");
    } else if(f < 0.50) {
      fprintf(check3i, "g\t");
    } else if(f < 0.75) {
      fprintf(check3i, "b\n");
    } else {
      fprintf(check3i, "t");
    }
  }
  fclose(check3i);

  char* text3 = read_text("check3in.txt", 1501);  

  assert(!text3);
  free(text3);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // checks if it detects when the text file is empty

  FILE* check4i = fopen("check4in.txt", "w");
  fclose(check4i);

  char* text4 = read_text("check4in.txt", 1501);  

  assert(!text4); // see if text reader returns null since input text has more than 1500 bases (1501)
  free(text4);
  */
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // integrated test of functional componenets
  FILE* check5e = fopen("check5e.txt", "w");
  fprintf(check5e, "TTA 4 10\nGC Not found\nA 1 3 6 9 12 14\nATTAC 3 9\n");
  fclose(check5e);
  
  FILE* check5i = fopen("check5i.txt", "w");
  fprintf(check5i, "CATATTAC\t\nGATTACA");
  fclose(check5i);

  char* text5 = read_text("check5i.txt", 1501);
  
  FILE* check5o = fopen("check5o.txt", "w");
  //Copied from main
  //


  char pattern[(int)sizeof(text5)];  // patterns can only be as long as the text
  
  // Cycles through all the patterns inputted by the user and matches them to the text
  while(scanf("%s", pattern) == 1) {
    // Convert the pattern to uppercase 
    capitalize(pattern, (int)strlen(pattern));

    // Match the pattern to the text and get back all the occurences
    int match = pattern_match(text5, strlen(text5), pattern, strlen(pattern), 0);
    
    // Print all the pattern followed by the index of the occurences
    fprintf(check5o, "%s", pattern);
    
    int k = 0;
    while(match != -1) {
      fprintf(check5o, " %i", match);
      match = pattern_match(text5, strlen(text5), pattern, strlen(pattern), match + 1);
      k++;
    }
    if(k == 0) {
      fprintf(check5o, " Not found"); // If there are no matches print not found
    }

    fprintf(check5o, "\n");
  }
  free(text5);
 
  
  fclose(check5o);
  
  assert(fileeq("check5e.txt", "check5o.txt"));  

  printf("All checks passed\n");
  return 0;
}
