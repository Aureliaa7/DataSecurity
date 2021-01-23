#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

int differentSymbols;
int totalNoSymbols;

typedef struct CustomSymbol {
    char symbol;
    int occurrences;
} CustomSymbol;


size_t getFileLength(FILE* filePtr);
int charExists(CustomSymbol* data, char character, int currentLength);
int getPosition(CustomSymbol* data, char character, int length);
void reset(CustomSymbol* dict, int length);
void insertSymbol(CustomSymbol* data, char character, int length);
void incrementNoOccurrences(CustomSymbol* data, int index);
void writeResultToFile(FILE* file, CustomSymbol* data);
void drawGraphicToFile(FILE* file, CustomSymbol* data);

#endif // FUNCTIONS_H_INCLUDED
