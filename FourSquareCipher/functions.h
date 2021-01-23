#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 10

char** preparePlayfairMatrix(char* key);
char** prepareFourSquareMatrix(char* key1, char* key2);
char* getTextFromFile(FILE* filePtr);
char** prepareTextToBeEncrypted(char* text);
char** prepareTextToBeDecrypted(char* cipher);
size_t getFileLength(FILE* filePtr);
int keyContainsLetter(char* key, char letter);
char* prepareKey(char* key);
char** encrypt(char* plaintext, char* key1, char* key2);
char** decrypt(char* cipher, char* key1, char* key2);
char* getKeyFromKeyboard();
void writeResultToFile(FILE* filePtr, char** textArr, int noRows);

#endif // FUNCTIONS_H_INCLUDED
