#include "functions.h"

char* encrypt(char* text, int key)
{
    char* cipher = (char*)malloc(strlen(text) * sizeof(char));
    int contor;

    for(contor = 0; contor < strlen(text); contor++)
    {
        if(isupper(text[contor]))
        {
            cipher[contor] = (text[contor] + key - 65) % NUMBER_OF_LETTERS + 65;
        }
        else if(islower(text[contor]))
        {
            cipher[contor] = (text[contor] + key - 97) % NUMBER_OF_LETTERS + 97;
        }
        else
        {
            cipher[contor] = text[contor];
        }
    }
    cipher[contor] = '\0';
    return cipher;
}

char* decrypt(char* cipher, int key) {
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
                plainText[contor] = (cipher[contor] - key - 65) % NUMBER_OF_LETTERS + 65;
            }
        }
        else if(islower(cipher[contor]))
        {
            if((cipher[contor] - key - 97) < 0) {
                plainText[contor] = 123 + (cipher[contor] - key - 97);

            }
            else {
                plainText[contor] = (cipher[contor] - key - 97) % NUMBER_OF_LETTERS + 97;
            }
        }
        else {
            plainText[contor] = cipher[contor];
        }
    }
    plainText[contor] = '\0';
    return plainText;
}

void bruteForceAttack(FILE* file, char* text) {
    int key;
    int contor;
    char* attempt;

    for(key = 0; key < NUMBER_OF_LETTERS; key++)
    {
        attempt = decrypt(text, key);
        fprintf(file, "%s\n", attempt);
    }
    fflush(file);
    free(attempt);
}

char* getTextFromFile(FILE* file){
    int fileSize;
    int contor;
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
