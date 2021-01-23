#include "functions.h"


int main()
{
    FILE* inputFilePtr;
    FILE* outputFilePtr;
    char* key1 = (char*)malloc(sizeof(char) * KEY_LENGTH);
    char* key2 = (char*)malloc(sizeof(char) * KEY_LENGTH);
    char* inputText;
    char** result;
    int choice;
    int noRows;
    int inputTextSize;
    int contor;
    char** fourSquareMatrix;

    if((inputFilePtr = fopen("input.txt", "r")) == NULL) {
        printf("Error opening input.txt file!");
        exit(1);
    }

    if((outputFilePtr = fopen("output.txt", "w")) == NULL) {
        printf("Error opening output.txt file!");
        exit(1);
    }

    inputText = getTextFromFile(inputFilePtr);
    inputTextSize = strlen(inputText);
    noRows = (inputTextSize % 2) ? inputTextSize/2+1 : inputTextSize/2;

    printf("\n***** Four Square Algorithm *****\n");
    printf("\n1. Encrypt");
    printf("\n2. Decrypt");
    printf("\n3. Exit");
    printf("\nYour choice: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            printf("\nEnter the first key: ");
            key1 = getKeyFromKeyboard();
            printf("\nEnter the second key: ");
            key2 = getKeyFromKeyboard();
            result = encrypt(inputText, key1, key2);
            fprintf(outputFilePtr, "The cipher text is: \n");
            writeResultToFile(outputFilePtr, result, noRows);
            printf("\n*** Check the output.txt file to view the encrypted text ***\n");
            break;
        case 2:
            printf("\nEnter the first key: ");
            key1 = getKeyFromKeyboard();
            printf("\nEnter the second key: ");
            key2 = getKeyFromKeyboard();
            result = decrypt(inputText, key1, key2);
            fprintf(outputFilePtr, "The plain text is: \n");
            writeResultToFile(outputFilePtr, result, noRows);
            printf("\n*** Check the output.txt file to view the decrypted text ***\n");
            break;
        case 3:
            exit(0);
        default:
            exit(1);
    }

    for(contor = 0; contor < noRows; contor++) {
        free(result[contor]);
    }
    free(result);

    fclose(inputFilePtr);
    fclose(outputFilePtr);
    free(inputText);
    free(key1);
    free(key2);

    return 0;
}
