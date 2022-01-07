#ifndef dnasearc_H
#define dnasearch_H
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int pattern_match(const char t[], int tlen, const char p[], int plen, int start_at);

void capitalize(char s[], int slen);

int valid(const char s[], int slen, int len);

char* read_text(char* input, int tlen);

#endif
