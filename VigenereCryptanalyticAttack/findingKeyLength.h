#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "letterFrequency.h"

#define MAX_PERIOD 16
#define FIRST_BEST_PERIODS 5
#define FIRST_BEST_KEYS 3

typedef struct PeriodAverageIC {
    int period;
    float IC;
} PeriodAverageIC;

char* getTextFromFile(FILE* file);
char* extractLetters(char* text, int period, int startAt);
char** getSubstringsForPeriod(char*cipher, int period);
float computeIndexOfCoincidence(char* text);
PeriodAverageIC* computeICForPeriods(FILE* file, char* text, int maxKeyLength);
void writeExtractedSubstrings(FILE* file, char** substrings, int arrSize);
PeriodAverageIC* findPossiblePeriods(PeriodAverageIC* periods, int firstBestPeriods, int totalPeriods);
PeriodAverageIC* sortByAvgICDesc(PeriodAverageIC* periods, int totalPeriods);

#endif // FUNCTIONS_H_INCLUDED
