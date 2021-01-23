#include "functions.h"

int main()
{
    FILE* inFilePtr;
    FILE* cipherFilePtr;
    FILE* decipherFilePtr;
    int key;
    char* text;
    char* cipher;
    int choice;

    if((inFilePtr = fopen("input.txt", "r")) == NULL)
    {
        printf("Error inFilePtr!");
        exit(1);
    }
    printf("\n1. Cipher\n");
    printf("2. Decipher\n");
    printf("3. Exit\n");
    printf("\nYour choice: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            printf("\n*** Cipher ***");
            printf("\nEnter the key: ");
            scanf("%d", &key);
            text = getTextFromFile(inFilePtr);
            cipher = encrypt(text, key);

            if((cipherFilePtr = fopen("cipher.txt", "w")) == NULL)
            {
                printf("Error cipherFilePtr!");
                exit(1);
            }
            fprintf(cipherFilePtr, "%s", cipher);
            printf("\nCheck the cipher.txt file to view the cipher\n");
            fclose(cipherFilePtr);
            break;

        case 2:
            printf("\n*** Decipher ***");
            text = getTextFromFile(inFilePtr);

            if((decipherFilePtr = fopen("bruteForceAttack.txt", "w")) == NULL)
            {
                printf("\n Error opening the file!");
                exit(1);
            }
            bruteForceAttack(decipherFilePtr, text);
            fclose(decipherFilePtr);
            printf("\nCheck the bruteForceAttack.txt file to view the result\n");
            break;

        case 3:
            exit(0);

        default:
            printf("\nInvalid option!");
            exit(0);
    }

    fclose(inFilePtr);
    free(cipher);
    free(text);
    return 0;
}
