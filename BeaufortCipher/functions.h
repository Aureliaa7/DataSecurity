#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 15

char* getKeyFromKeyboard();
char* getTextFromFile(FILE* file);
char* encrypt(char* plainText, char* key);
char* decrypt(char* cipherText, char* key);
void writeToFile(FILE* file, char* text);

#endif // FUNCTIONS_H_INCLUDED
