#include "functions.h"

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

void incrementNoOccurrences(CustomSymbol* data, int index) {
    data[index].occurrences++;
}

void writeResultToFile(FILE* file, CustomSymbol* data)
{
    int contor;
    float percentage;

    fprintf(file, "Total number of symbols: %d\n\n", totalNoSymbols);
    fprintf(file, "The result is:\n\n");
    fprintf(file, "\tsymbol\t\t   no.occurrences \t\t percentage\n");
    fprintf(file, "-----------------------------------------------------\n");
    for(contor = 0; contor < differentSymbols; contor++)
    {
        percentage = (float)data[contor].occurrences / totalNoSymbols * 100; // the percentage
        fprintf(file, "\t\t%c\t\t|\t\t %d\t\t\t|\t\t %.2f %%\n", data[contor].symbol, data[contor].occurrences, percentage);
    }
    fflush(file);
}

void drawGraphicToFile(FILE* file, CustomSymbol* data) {
    int contor1, contor2;
    float percentage;

    fprintf(file, "\n\n\n*** The letter frequency distribution ***\n", totalNoSymbols);
    for(contor1 = 0; contor1 < differentSymbols; contor1++)
    {
        fprintf(file, "\n%c\t", data[contor1].symbol);
        for(contor2 = 0; contor2 < data[contor1].occurrences; contor2++) {
            fprintf(file, "| ");
        }
    }
    fflush(file);
}

