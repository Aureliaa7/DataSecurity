#include "letterFrequency.h"

CustomSymbol* createCustomSymbolArr(char* text)
{
    CustomSymbol* data = (CustomSymbol*)malloc(strlen(text) * sizeof(CustomSymbol));
    int contor1;
    int contor2;
    int position;

    for(contor1 = 0, contor2 = 0; contor1 < strlen(text); contor1++)
    {
        if(!charExists(data, text[contor1], contor2))
        {
            insertSymbol(data, text[contor1], contor2);
            contor2++;
        }
        else
        {
            position = getPosition(data, text[contor1], contor2);
            incrementNoOccurrences(data, position);
        }
    }
    return data;
}

size_t getFileLength(FILE* filePtr) {
    size_t position = ftell(filePtr);
    fseek(filePtr, 0, SEEK_END);
    size_t length = ftell(filePtr);
    fseek(filePtr, position, SEEK_SET);
    return length;
}

int charExists(CustomSymbol* data, char character, int currentLength) {
    int iterator;
    int exists = 0;
    for(iterator = 0; iterator < currentLength; iterator++) {
        if(data[iterator].symbol == character) {
            exists = 1;
            break;
        }
    }
    return exists;
}

int getPosition(CustomSymbol* data, char character, int length) {
    int iterator;
    int position = -1;
    for(iterator = 0; iterator < length; iterator++) {
        if(data[iterator].symbol == character) {
            position = iterator;
            break;
        }
    }
    return position;
}

void reset(CustomSymbol* data, int length) {
    int iterator;
    for(iterator = 0; iterator < length; iterator++) {
        data[iterator].symbol = '\000';
        data[iterator].occurrences = 0;
    }
}

void insertSymbol(CustomSymbol* data, char character, int length) {
    differentSymbols++;
    data[length].symbol = character;
    data[length].occurrences = 1;
}

void incrementNoOccurrences(CustomSymbol* data, int contor) {
    data[contor].occurrences++;
}

void writeResultToFile(FILE* file, CustomSymbol* data)
{
    int contor;
    float percentage;

    fprintf(file, "Total symbols: %d\n\n", totalNoSymbols);
    fprintf(file, "The result is:\n\n");
    fprintf(file, "\tsymbol\t\t no.occurrences\t\n");

     for(contor = 0; contor < differentSymbols; contor++)
    {
        fprintf(file, "\t\t%c\t\t\t\t %d\t\t\t\t\n", data[contor].symbol, data[contor].occurrences);
    }
    fflush(file);
}

int getNoDifferentElements(CustomSymbol* data, int totalElements) {
    int noDifferentElements = 0;
    int contor = 0;

    while(totalElements > 0) {
        totalElements -= data[contor++].occurrences;
        noDifferentElements++;
    }
    return noDifferentElements;
}
