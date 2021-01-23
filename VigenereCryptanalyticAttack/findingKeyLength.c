#include "findingKeyLength.h"

char* extractLetters(char* text, int period, int startAt) {
    int iterator1, iterator2;
    char* extractedLetters = (char*) malloc(strlen(text) * sizeof(char));

    for(iterator1 = startAt, iterator2 = 0; iterator1 < strlen(text); iterator1+=period) {
        extractedLetters[iterator2] = text[iterator1];
        iterator2++;
    }
    extractedLetters[iterator2] = '\0';
    return extractedLetters;
}

char** getSubstringsForPeriod(char*cipher, int period) {
    char** substrings = (char**)malloc(strlen(cipher) * sizeof(char*));
    int contor1, contor2;

    for(contor1 = 0, contor2 = 0; contor1 < period; contor1++) {
        substrings[contor1] = extractLetters(cipher, period, contor2);
        contor2++;
    }
    return substrings;
}

char* getTextFromFile(FILE* file) {
    int fileLength = getFileLength(file);
    char* text = (char*)malloc(fileLength*sizeof(char));
    int c;
    int contor = 0;

    c = getc(file);
    while(c != EOF)
    {
        if((c != 32) && (c != 10))  //don't take into consideration white space
        {
            text[contor++] = c;
        }
        c = getc(file);
    }
    text[contor] = '\0';
    return text;
}

float computeIndexOfCoincidence(char* text) {
    CustomSymbol* data = createCustomSymbolArr(text);
    int contor;
    float indexOfCoincidence;
    int noElementsInData;
    int size = strlen(text);
    int sum = 0;
    int N = size * (size - 1);

    noElementsInData = getNoDifferentElements(data, size);

    for(contor = 0; contor < noElementsInData; contor++) {
        sum += (data[contor].occurrences * (data[contor].occurrences - 1));
    }
    indexOfCoincidence =(float) sum / N;
    free(data);
    return indexOfCoincidence;
}

// i suppose that the key is of length 2, then 3, ... ,then maxKeyLength
PeriodAverageIC* computeICForPeriods(FILE* file, char* text, int maxKeyLength) {
    PeriodAverageIC* possiblePeriods = (PeriodAverageIC*)malloc(sizeof(PeriodAverageIC) * (maxKeyLength-1));
    int contor1;  // represents the length of the key
    int contor2;
    int contor3 = 0;
    char** substrings;
    float averageIC = 0;
    float sumIC = 0;

    for(contor1 = 2; contor1 <= maxKeyLength; contor1++) {
        // extract the corresponding letters
        substrings = getSubstringsForPeriod(text, contor1);
        sumIC = 0;
        fprintf(file, "\n\n***** Period %d ***** ", contor1);
        writeExtractedSubstrings(file, substrings, contor1);

        for(contor2 = 0; contor2 < contor1; contor2++) {
            fprintf(file, "\n IC for substring no. %d: %f", contor2, computeIndexOfCoincidence(substrings[contor2]));
            sumIC += computeIndexOfCoincidence(substrings[contor2]);
        }
        averageIC = sumIC / contor1;
        fprintf(file, "\n* Average IC: %f", averageIC);
        possiblePeriods[contor3].period = contor1;
        possiblePeriods[contor3].IC = averageIC;
        contor3++;
        fflush(file);
    }
    for (contor1 = 0; contor1 < maxKeyLength; contor1++) {
        free(substrings[contor1]);
    }
    free(substrings);

    return possiblePeriods;
}

void writeExtractedSubstrings(FILE* file, char** substrings, int arrSize) {
    int contor;

    for(contor = 0; contor < arrSize; contor++) {
        fprintf(file, "\n substring %d: %s", contor, substrings[contor]);
    }
}

// firstBestPeriods represents the first x periods which have the greatest average IC
PeriodAverageIC* findPossiblePeriods(PeriodAverageIC* periods, int firstBestPeriods, int totalPeriods) {
    int contor;
    PeriodAverageIC* possiblePeriods = (PeriodAverageIC*)malloc(firstBestPeriods * sizeof(PeriodAverageIC));

    periods = sortByAvgICDesc(periods, totalPeriods);
    for(contor = 0; contor < firstBestPeriods; contor++) {
        possiblePeriods[contor].period = periods[contor].period;
        possiblePeriods[contor].IC = periods[contor].IC;
    }
    return possiblePeriods;
}

PeriodAverageIC* sortByAvgICDesc(PeriodAverageIC* periods, int totalPeriods){
    int contor1, contor2;
    float tempIC;
    int tempPeriod;

    for(contor1 = 0; contor1 < totalPeriods - 1; contor1++) {
        for(contor2 = 0; contor2 < totalPeriods - contor1 - 1; contor2++) {
            if(periods[contor2].IC < periods[contor2+1].IC) {
                tempPeriod = periods[contor2].period;
                tempIC = periods[contor2].IC;
                periods[contor2].period = periods[contor2+1].period;
                periods[contor2].IC = periods[contor2+1].IC;
                periods[contor2+1].period = tempPeriod;
                periods[contor2+1].IC = tempIC;
            }
        }
    }
    return periods;
}
