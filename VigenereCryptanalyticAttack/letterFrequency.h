#ifndef LETTERFREQUENCY_H_INCLUDED
#define LETTERFREQUENCY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

int differentSymbols;
int totalNoSymbols;

typedef struct CustomSymbol {
    char symbol;
    int occurrences;
    float expectedOccurences;
} CustomSymbol;

size_t getFileLength(FILE* filePtr);
int charExists(CustomSymbol* data, char character, int currentLength);
int getPosition(CustomSymbol* data, char character, int length);
void reset(CustomSymbol* dict, int length);
void insertSymbol(CustomSymbol* data, char character, int length);
void incrementNoOccurrences(CustomSymbol* data, int contor);
void writeResultToFile(FILE* file, CustomSymbol* data);
int getNoDifferentElements(CustomSymbol* data, int totalElements);
CustomSymbol* createCustomSymbolArr(char* text);


#endif // LETTERFREQUENCY_H_INCLUDED
