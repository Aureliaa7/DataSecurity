#ifndef CHISQUAREDSTATISTIC_H_INCLUDED
#define CHISQUAREDSTATISTIC_H_INCLUDED

#include "findingKeyLength.h"
#include <string.h>
#include <math.h>

typedef struct EnglishLetterFrequency {
    char letter;
    float percentage;
} EnglishLetterFrequency;

typedef struct TextWithChiSquared {
    char* plainText;
    float chiSquaredStatistic;
    int key;
} TextWithChiSquared;

EnglishLetterFrequency* getEnglishLetterFrequencies(FILE* file);
char** bruteForceAttackCaesar(char* text);
char* decryptCaesar(char* cipher, int key);
TextWithChiSquared* computeChiSquaredForCipher(char* cipher, EnglishLetterFrequency* englishLetterFrequencies);
float getEnglishLetterFrequency(EnglishLetterFrequency* letterFrequencies, char letter);
TextWithChiSquared* getTextWithMinChiSquared(TextWithChiSquared* data);
int getNoTextWithMinSquaredValues(TextWithChiSquared* data, int length);
void writeChiSquaredStatisticToFile(FILE* file, TextWithChiSquared* chiSquaredValues, int length);
TextWithChiSquared* sortByChiSquaredAsc(TextWithChiSquared* data, int length);
TextWithChiSquared* getFirstTextWithChiSq(TextWithChiSquared* data, int firstBestKeys, int length);

#endif // CHISQUAREDSTATISTIC_H_INCLUDED
