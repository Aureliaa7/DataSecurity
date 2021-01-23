#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** preparePlayfairMatrix(char* key);
char* getTextFromFile(FILE* filePtr);
char** prepareTextToBeEncrypted(char* text);
char** prepareTextToBeDecrypted(char* cipher);
size_t getFileLength(FILE* filePtr);
int keyContainsLetter(char* key, char letter);
char* prepareKey(char* key);
char** encrypt(char* plaintext, char* key);
char** decrypt(char* cipher, char* key);
void writeResultToFile(FILE* filePtr, char** textArr, int noRows);

#endif // FUNCTIONS_H_INCLUDED
