#include "functions.h"
#define KEY_LENGTH 15


int main()
{
    FILE* inputFilePtr;
    FILE* outputFilePtr;
    char* key = (char*)malloc(sizeof(char) * KEY_LENGTH);
    char* inputText;
    char** result;
    int choice;
    int noRows;
    int inputTextSize;
    int contor;

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

    printf("\n***** Playfair cipher *****\n");
    printf("\n1. Encrypt");
    printf("\n2. Decrypt");
    printf("\n3. Exit");
    printf("\nYour choice: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            printf("\nEnter the key: ");
            scanf("%s", key);
            result = encrypt(inputText, key);
            fprintf(outputFilePtr, "The cipher text is: \n");
            writeResultToFile(outputFilePtr, result, noRows);
            printf("\n*** Check the output.txt file to view the encrypted text ***\n");
            break;
        case 2:
            printf("\nEnter the key: ");
            scanf("%s", key);
            result = decrypt(inputText, key);
            fprintf(outputFilePtr, "The plain text is: \n");
            writeResultToFile(outputFilePtr, result, noRows);
            printf("\n*** Check the output.txt file to view the decrypted text ***\n");
            break;
        case 3:
            exit(0);
        default:
            printf("\nInvalid option!");
            exit(1);
    }

    for(contor = 0; contor < noRows; contor++) {
        free(result[contor]);
    }
    free(result);
    fclose(inputFilePtr);
    fclose(outputFilePtr);
    free(inputText);
    free(key);

    return 0;
}
