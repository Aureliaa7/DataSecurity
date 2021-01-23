#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NUMBER_OF_LETTERS 26


void bruteForceAttack(FILE* file, char* text);
char* encrypt(char* text, int key);
char* decrypt(char* cipher, int key);
char* getTextFromFile(FILE* file);

#endif // FUNCTIONS_H_INCLUDED
