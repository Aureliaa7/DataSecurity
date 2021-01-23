#include "functions.h"

char* getTextFromFile(FILE* file){
    int fileSize;
    int contor = 0;
    int c;
    char* text;

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    text = (char*)malloc((fileSize-2) * sizeof(char));
    c = getc(file);
    while(c != EOF)
    {
        // ignore white spaces and new lines
        if(c != 32 && c != 10)
        {
            if(islower(c))
            {
                text[contor] = toupper(c);
            }
            else
            {
                text[contor] = c;
            }
            contor++;
        }
        c = getc(file);
    }
    text[contor] = '\0';
    return text;
}

char* encrypt(char* plainText, char* key) {
    int contor1 = 0;
    int contor2 = 0;
    int contor3;
    int textLength = strlen(plainText);
    int keyLength = strlen(key);
    char* cipherText = (char*) malloc(textLength * sizeof(char));
    char* preparedKey = prepareKey(key, plainText);

    for(contor1 = 0; contor1 < textLength; contor1++){
        cipherText[contor1] = (plainText[contor1] + preparedKey[contor1]) %26 + 'A';
    }
    cipherText[contor1] = '\0';
    free(preparedKey);

    return cipherText;
}

char decryptLetter(char cipherLetter, char keyLetter) {
    char letter;

    if((cipherLetter - keyLetter) < 0)
    {
        letter = (cipherLetter - keyLetter) + 26 + 'A';
    }
    else
    {
        letter = (cipherLetter - keyLetter) % 26 + 'A';
    }

    return letter;
}

char* decrypt(char* cipherText, char* key) {
    int contor1;
    int contor2;
    int contor3;
    int cipherLength = strlen(cipherText);
    int keyLength = strlen(key);
    char* plainText = (char*) malloc(cipherLength * sizeof(char));
    char* preparedKey = (char*)malloc(sizeof(char) * cipherLength);

    for(contor1 = 0; contor1 < keyLength; contor1++) {
        preparedKey[contor1] = key[contor1];
    }

    for(contor1 = 0, contor2 = keyLength; contor1 < cipherLength; contor1++) {
        if(contor1 == keyLength) {
            contor3 = 0;
            preparedKey[contor2++] = plainText[contor3++];
        }
        else if(contor1 > keyLength){
            preparedKey[contor2++] = plainText[contor3++];
        }
        plainText[contor1] = decryptLetter(cipherText[contor1], preparedKey[contor1]);
    }

    plainText[contor1] = '\0';
    preparedKey[cipherLength-1] = '\0';

    free(preparedKey);
    return plainText;
}

void writeToFile(FILE* file, char* text) {
    fprintf(file, "%s", text);
    fflush(file);
}

char* getKeyFromKeyboard()
{
    char* key = (char*)malloc(N * sizeof(char));
    int contor;
    int keyLength;

    printf("\nEnter the key: ");
    scanf("%s", key);
    keyLength =  strlen(key);

    for(contor = 0; contor < keyLength; contor++)
    {
        if(islower(key[contor]))
        {
            key[contor] = toupper(key[contor]);
        }
    }
    return key;
}

char* prepareKey(char* initialKey, char* text) {
    int initialKeyLength = strlen(initialKey);
    int textLength = strlen(text);
    int contor1, contor2;
    int length;
    char* preparedKey = (char*)malloc(sizeof(char) * textLength);

    for(contor1 = 0; contor1 < initialKeyLength; contor1++) {
        preparedKey[contor1] = initialKey[contor1];
    }

    for(contor1 = initialKeyLength, contor2 = 0; contor1 < textLength; contor1++) {
        if(text[contor2] != ' ') {
            preparedKey[contor1] = text[contor2++];
        }
    }
    preparedKey[contor1] = '\0';

    return preparedKey;
}
