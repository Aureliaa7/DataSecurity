#ifndef VIGENERE_H_INCLUDED
#define VIGENERE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 15

char* getKeyFromKeyboard();
char* getTextFromFile(FILE* file);
char* encrypt(char* plainText, char* key);
char* decrypt(char* cipherText, char* key);
void writeToFile(FILE* file, char* text);
int keyIsLowerCase(char* key);

#endif // VIGENERE_H_INCLUDED
