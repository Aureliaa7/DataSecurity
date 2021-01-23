#include "functions.h"

int main()
{
    int c;
    FILE *inFilePtr;
    FILE *outFilePtr;
    size_t fileLength;
    CustomSymbol* symbols;
    int contor = 0;
    int position;

    if((inFilePtr = fopen("input.txt", "r")) == NULL) {
        printf("Error!");
        exit(1);
    }

    fileLength = getFileLength(inFilePtr);
    symbols = (CustomSymbol*)malloc(fileLength*sizeof(CustomSymbol));

    reset(symbols, fileLength);

    totalNoSymbols = 0;
    c = getc(inFilePtr);
    while(c != EOF)
    {
        if((c != 32) && (c != 10))  //don't take into consideration white space
        {
            totalNoSymbols++;
            if(!charExists(symbols, c, contor))
            {
                insertSymbol(symbols, c, contor);
                contor++;
            }
            else
            {
                position = getPosition(symbols, c, contor);
                incrementNoOccurrences(symbols, position);
            }
        }
        c = getc(inFilePtr);
    }
    fclose(inFilePtr);

    if((outFilePtr = fopen("output.txt", "w")) == NULL) {
        printf("Error!");
        exit(1);
    }

    writeResultToFile(outFilePtr, symbols);
    drawGraphicToFile(outFilePtr, symbols);

    free(symbols);
    fclose(outFilePtr);
    return 0;
}
