#include "vigenere.h"

char* getTextFromFile(FILE* file){
    int fileSize;
    int contor = 0;
    int c;
    char* text;

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    text = (char*)malloc(fileSize * sizeof(char));
    c = getc(file);
    while(c != EOF)
    {
        text[contor] = c;
        contor++;
        c = getc(file);
    }
    text[contor] = '\0';
    return text;
}

char* encrypt(char* plainText, char* key) {
    int contor1 = 0;
    int contor2 = 0;
    int textLength = strlen(plainText);
    int keyLength = strlen(key);
    char* cipherText = (char*) malloc((textLength+1) * sizeof(char));

    for (contor1 = 0, contor2 = 0; contor1 < textLength; contor1++)
    {
        if(isupper(plainText[contor1]))
        {
            cipherText[contor1] = (plainText[contor1] - 'A' + key[contor2 % keyLength] - 'a') %26 + 'A';
            contor2++;
        }
        else if(islower(plainText[contor1]))
        {
            cipherText[contor1] = (plainText[contor1] - 'a' + key[contor2 % keyLength] - 'a') %26 + 'a';
            contor2++;
        }
        else
        {
            cipherText[contor1] = plainText[contor1];
        }
    }
     cipherText[contor1] = '\0';

    return cipherText;
}

char* decrypt(char* cipherText, char* key) {
    int contor1;
    int contor2;
    int cipherLength = strlen(cipherText);
    int keyLength = strlen(key);
    char* plainText = (char*) malloc(cipherLength * sizeof(char));

    for (contor1 = 0, contor2 = 0; contor1 < cipherLength; contor1++)
    {
        if(isupper(cipherText[contor1]))
        {
            if((cipherText[contor1] - toupper(key[contor2%keyLength])) < 0){
                plainText[contor1] = (cipherText[contor1] - toupper(key[contor2%keyLength]))+26 + 'A';
            }
            else {
               plainText[contor1] = (cipherText[contor1] - toupper(key[contor2%keyLength])) % 26 + 'A';
            }
            contor2++;
        }
        else if(islower(cipherText[contor1]))
        {
            if((cipherText[contor1] - key[contor2%keyLength]) < 0) {
                plainText[contor1] = (cipherText[contor1]  - key[contor2%keyLength])+26 + 'a';
            }
            else {
                plainText[contor1] = (cipherText[contor1] - key[contor2%keyLength])%26 + 'a';
            }
             contor2++;
        }
        else
        {
            plainText[contor1] = cipherText[contor1];
        }
    }
    plainText[contor1] = '\0';

    return plainText;
}

void writeToFile(FILE* file, char* text) {
    fprintf(file, "%s", text);
    fflush(file);
}

int keyIsLowerCase(char* key) {
    int contor;
    int isLowerCase = 1;

    for(contor = 0; contor < strlen(key); contor++) {
        if(isupper(key[contor])) {
            isLowerCase = 0;
            break;
        }
    }
    return isLowerCase;
}

char* getKeyFromKeyboard()
{
    char* key = (char*)malloc(N * sizeof(char));

getKey:
    printf("\nEnter the key: ");
    scanf("%s", key);
    if(!keyIsLowerCase(key))
    {
        printf("\nThe key must be in lower case!");
        goto getKey;
    }
    return key;
}
