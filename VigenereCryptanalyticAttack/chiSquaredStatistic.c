#include "chiSquaredStatistic.h"

EnglishLetterFrequency* getEnglishLetterFrequencies(FILE* file) {
    EnglishLetterFrequency* letterFrequencies = (EnglishLetterFrequency*)malloc(26 * sizeof(EnglishLetterFrequency));
    int contor;
    char line[12];
    char* tokens;

    for(contor = 0; contor < 26; contor++) {
        fgets(line, sizeof(line),file);
        tokens = strtok (line, "   ");
        letterFrequencies[contor].letter = tokens[0];
        tokens = strtok(NULL, "  ");
        letterFrequencies[contor].percentage = atof(tokens);
    }
    return letterFrequencies;
}


char* decryptCaesar(char* cipher, int key) {
    char* plainText = (char*)malloc(strlen(cipher) * sizeof(char));
    int contor;

    for(contor = 0; contor < strlen(cipher); contor++)
    {
        if(isupper(cipher[contor]))
        {
            if((cipher[contor] - key - 65) < 0) {
                plainText[contor] = 91 + (cipher[contor] - key - 65);
            }
            else {
                plainText[contor] = (cipher[contor] - key - 65) % 26 + 65;
            }
        }
        else if(islower(cipher[contor]))
        {
            if((cipher[contor] - key - 97) < 0) {
                plainText[contor] = 123 + (cipher[contor] - key - 97);
            }
            else {
                plainText[contor] = (cipher[contor] - key - 97) % 26 + 97;
            }
        }
        else {
            plainText[contor] = cipher[contor];
        }
    }
    plainText[contor] = '\0';
    return plainText;
}

char** bruteForceAttackCaesar(char* text) {
    int key;
    char** attempts = (char**)malloc(sizeof(char*)* 26);

    for(key = 0; key < 26; key++)
    {
        attempts[key] = decryptCaesar(text, key);
    }
    return attempts;
}

float getEnglishLetterFrequency(EnglishLetterFrequency* letterFrequencies, char letter) {
    float searchedFrequency;
    int contor;

    for(contor = 0; contor < 26; contor++) {
        if(letterFrequencies[contor].letter == letter) {
            searchedFrequency = letterFrequencies[contor].percentage;
            break;
        }
    }
    return searchedFrequency;
}

TextWithChiSquared* computeChiSquaredForCipher(char* cipher, EnglishLetterFrequency* englishLetterFrequencies) {
    char** substrings = bruteForceAttackCaesar(cipher);
    int contor1, contor2, contor3;
    CustomSymbol** symbols = (CustomSymbol**)malloc(26 * sizeof(CustomSymbol*));
    float letterFrequency;
    float sumChiSquaredStatistic = 0;
    float tempChiSquared;
    float temp;
    TextWithChiSquared* textWithChiSquared = (TextWithChiSquared*)malloc(26 * sizeof(TextWithChiSquared));
    char letter;
    float expectedOccurrences;
    int differentElements;
    int found;

    /// for each substring, I create a custom symbol
    for(contor1 = 0; contor1 < 26; contor1++) {
        symbols[contor1] = createCustomSymbolArr(substrings[contor1]);
        sumChiSquaredStatistic = 0;

        /// compute chi-sq for the elements that  are in symbols[contor1]
        differentElements = getNoDifferentElements(symbols[contor1], strlen(substrings[contor1]));
        for(contor2 = 0; contor2 < differentElements; contor2++) {
            letterFrequency = getEnglishLetterFrequency(englishLetterFrequencies, symbols[contor1][contor2].symbol)/100;
            symbols[contor1][contor2].expectedOccurences = strlen(substrings[contor1]) * letterFrequency;
            temp = pow((symbols[contor1][contor2].occurrences - symbols[contor1][contor2].expectedOccurences), 2);
            tempChiSquared = (float)temp / symbols[contor1][contor2].expectedOccurences;
            sumChiSquaredStatistic += tempChiSquared;

        }
        /// also take into consideration the letters that do not appear in symbols[contor1]

        for(contor2 = 0; contor2 < 26; contor2++) {
            letter = englishLetterFrequencies[contor2].letter;
            letterFrequency = getEnglishLetterFrequency(englishLetterFrequencies, letter) / 100;
            expectedOccurrences = strlen(substrings[contor1]) * letterFrequency;
            if(!charExists(symbols[contor1], letter, differentElements)) {
                tempChiSquared = expectedOccurrences;
                sumChiSquaredStatistic += tempChiSquared;
            }
        }

        /// save the plainText, the key and the chi-squared statistic
        textWithChiSquared[contor1].chiSquaredStatistic = sumChiSquaredStatistic;
        textWithChiSquared[contor1].key = contor1;
        textWithChiSquared[contor1].plainText = substrings[contor1];
    }

/*
    for(contor1 = 0; contor1 < 26; contor1++) {
        free(symbols[contor1]);
        free(substrings[contor1]);
    }
    free(symbols);
    free(substrings);*/

    return textWithChiSquared;
}


TextWithChiSquared* getTextWithMinChiSquared(TextWithChiSquared* data) {
    int contor, contor2;
    TextWithChiSquared* textWithChiSquared = (TextWithChiSquared*)malloc(sizeof(TextWithChiSquared)*MAX_PERIOD);
    int indexForMinValue = 0;

    for(contor = 0; contor < 26; contor++) {
        if(data[contor].chiSquaredStatistic <data[indexForMinValue].chiSquaredStatistic) {
            indexForMinValue = contor;
        }
    }
    for(contor = 0, contor2 = 0; contor < 26; contor++) {
        if(data[contor].chiSquaredStatistic == data[indexForMinValue].chiSquaredStatistic) {
            textWithChiSquared[contor2] = data[contor];
            contor2++;
        }
    }
    return textWithChiSquared;
}


int getNoTextWithMinSquaredValues(TextWithChiSquared* data, int length) {
    int contor;
    int noMinChiSquared = 0;
    int indexForMinValue = 0;

    for(contor = 0; contor < length; contor++) {
        if(data[contor].chiSquaredStatistic < data[indexForMinValue].chiSquaredStatistic) {
            indexForMinValue = contor;
        }
    }

    for(contor = 0; contor < length; contor++) {
        if(data[contor].chiSquaredStatistic == data[indexForMinValue].chiSquaredStatistic) {
            noMinChiSquared++;
        }
    }

    if(!noMinChiSquared) {
        return 1;
    }
    return noMinChiSquared;
}


void writeChiSquaredStatisticToFile(FILE* file, TextWithChiSquared* chiSquaredValues, int length) {
    int contor;

    for(contor = 0; contor < length; contor++) {
        fprintf(file, "\n%s\t\t%f\t\t\t%d", chiSquaredValues[contor].plainText, chiSquaredValues[contor].chiSquaredStatistic, chiSquaredValues[contor].key);
    }
    fflush(file);
}


TextWithChiSquared* sortByChiSquaredAsc(TextWithChiSquared* data, int length) {
    int contor1, contor2;
    float tempChiSquared;
    int tempKey;
    char* tempText;

    for(contor1 = 0; contor1 < length - 1; contor1++) {
        for(contor2 = 0; contor2 < length - contor1 - 1; contor2++) {
            if(data[contor2].chiSquaredStatistic > data[contor2+1].chiSquaredStatistic) {
                tempChiSquared = data[contor2].chiSquaredStatistic;
                tempKey = data[contor2].key;
                tempText = data[contor2].plainText;
                data[contor2].chiSquaredStatistic = data[contor2+1].chiSquaredStatistic;
                data[contor2].key = data[contor2+1].key;
                data[contor2].plainText = data[contor2].plainText;
                data[contor2+1].chiSquaredStatistic = tempChiSquared;
                data[contor2+1].key = tempKey;
                data[contor2].plainText = tempText;
            }
        }
    }
    return data;
}


TextWithChiSquared* getFirstTextWithChiSq(TextWithChiSquared* data, int firstBestKeys, int length) {
    int contor;

    TextWithChiSquared* possibleKeys = (TextWithChiSquared*)malloc(firstBestKeys * sizeof(TextWithChiSquared));

    data = sortByChiSquaredAsc(data, length);
    for(contor = 0; contor < firstBestKeys; contor++) {
        possibleKeys[contor].chiSquaredStatistic = data[contor].chiSquaredStatistic;
        possibleKeys[contor].key = data[contor].key;
        possibleKeys[contor].plainText = data[contor].plainText;
    }
    return possibleKeys;
}
