#include "functions.h"

int main()
{
    FILE* inFilePtr;
    FILE* outFilePtr;
    char* key;
    int choice;
    char* plainText;
    char* cipherText;

    if((inFilePtr = fopen("input.txt", "r")) == NULL)
    {
        printf("Error opening the input file!");
        exit(1);
    }

    if((outFilePtr = fopen("output.txt", "w")) == NULL)
    {
        printf("Error opening the output file!");
        exit(1);
    }
    printf("\n1. Vigenere Cipher- Autokey Variant\n");
    printf("2. Vigenere Decipher- Autokey Variant\n");
    printf("3. Exit\n");
    printf("\nYour choice: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            printf("\n*** Vigenere Cipher- Autokey Variant ***");
            key = getKeyFromKeyboard();
            plainText = getTextFromFile(inFilePtr);
            cipherText = encrypt(plainText, key);
            writeToFile(outFilePtr, cipherText);
            printf("\n--- Check the output.txt file to view the result\n");
            break;

        case 2:
            printf("\n*** Vigenere Decipher- Autokey Variant ***");
            key = getKeyFromKeyboard();
            cipherText = getTextFromFile(inFilePtr);
            plainText = decrypt(cipherText, key);
            writeToFile(outFilePtr, plainText);
            printf("\n--- Check the output.txt file to view the result\n");
            break;

        case 3:
            exit(0);

        default:
            printf("\nInvalid option!");
            exit(0);
    }


    free(plainText);
    free(cipherText);
    free(key);
    fclose(inFilePtr);
    fclose(outFilePtr);
    return 0;
}
