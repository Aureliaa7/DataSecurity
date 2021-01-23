#include "functions.h"

size_t getFileLength(FILE* filePtr) {
    size_t position = ftell(filePtr);
    fseek(filePtr, 0, SEEK_END);
    size_t length = ftell(filePtr);
    fseek(filePtr, position, SEEK_SET);
    return length;
}

char* getTextFromFile(FILE* filePtr) {
    int fileLength = getFileLength(filePtr);
    char* text = (char*)malloc(fileLength*sizeof(char));
    int c;
    int contor = 0;

    c = getc(filePtr);
    while(c != EOF)
    {
        if((c != 32) && (c != 10))  //don't take into consideration white space and new line
        {
            text[contor++] = c;
        }
        c = getc(filePtr);
    }
    text[contor] = '\0';
    return text;
}

char** preparePlayfairMatrix(char* key) {
    int contor1, contor2, contor3;
    char** playfairMatrix = (char**)malloc(sizeof(char*) * 5);
    int keyLength;
    int keyIsInMatrix = 0;
    char alphabet[] = {'A', 'B', 'C', 'D', 'E',
                        'F', 'G', 'H', 'I', 'K',
                        'L', 'M', 'N', 'O', 'P',
                        'Q', 'R', 'S', 'T', 'U',
                        'V', 'W', 'X', 'Y', 'Z'};

    for(contor1 = 0; contor1 < 5; contor1++) {
        playfairMatrix[contor1] = (char*)malloc(sizeof(char) * 5);
    }

    key = prepareKey(key);
    keyLength = strlen(key);

    /// start the matrix with the letters of the key
    for(contor1 = 0, contor3 = 0; contor1 < 5; contor1++) {
        for(contor2 = 0; contor2 < 5; contor2++) {
            if(contor3 < keyLength) {
                playfairMatrix[contor1][contor2] =  toupper(key[contor3]);
                contor3++;
            }
            else {
                keyIsInMatrix = 1;
                break;
            }
        }
        if(keyIsInMatrix) {
            break;
        }
    }

    /// complete the matrix with the remaining letters from alphabet
    for(contor3 = 0; contor3 < 26; contor3++) {
        if(contor2 > 4) {
            contor2 = 0;
            contor1++;
        }
          if(contor1 > 4) {
            break;
        }
        if(!keyContainsLetter(key, alphabet[contor3])) {
            playfairMatrix[contor1][contor2] = alphabet[contor3];
            contor2++;
        }
    }

    ///print the obtained matrix
    printf("\nThe obtained Playfair matrix is: \n");
    for(contor1 = 0; contor1 < 5; contor1++) {
        for(contor2 = 0; contor2 < 5; contor2++) {
            printf("%c ", playfairMatrix[contor1][contor2]);
        }
        printf("\n");
    }

    return playfairMatrix;
}

int keyContainsLetter(char* key, char letter) {
    int contor;
    int found = 0;

    for(contor = 0; contor < strlen(key); contor++) {
        if(toupper(key[contor]) == toupper(letter)) {
            found = 1;
            break;
        }
    }
    return found;
}

char* prepareKey(char* key) {
    int contor1, contor2, contor3 = 0;
    int size = strlen(key);
    char* preparedKey = (char*)malloc(sizeof(char)*size);

    for(contor1 = 0; contor1 < size; contor1++) {
        for(contor2 = 0; contor2 < contor1; contor2++)  {
            if(key[contor1] == key[contor2]) {
                break;
            }
        }
     if(contor1 == contor2) {
        preparedKey[contor3++] = key[contor1];
     }
   }
   preparedKey[contor3] = '\0';

   /// print the obtained key
   printf("\n\n*** The prepared key is: %s\n", preparedKey);
   return preparedKey;
}

char** prepareTextToBeEncrypted(char* text) {
    int size = strlen(text);
    char** preparedPlaintext;
    int contor1, contor2 = 0, contor3 = 0;
    int noRows;

    noRows = (size % 2)? size / 2 + 1 : size/2;
    preparedPlaintext = (char**)malloc(sizeof(char*) * noRows);

    for(contor1 = 0; contor1 < noRows; contor1++) {
        preparedPlaintext[contor1] = (char*)malloc(sizeof(char) * 2);
    }

    for(contor1 = 0; contor1 < size; contor1++) {
        if(contor3 == 2) {
            contor3 = 0;
            contor2++;
        }
        if(text[contor1] == 'J') {
            text[contor1] = 'I';
        }

        preparedPlaintext[contor2][contor3] = toupper(text[contor1]);
        contor3++;
    }
    if(size % 2) {
        preparedPlaintext[size/2][1] = 'X';
    }

    for(contor1 = 0; contor1 < noRows; contor1++) {
        if(preparedPlaintext[contor1][0] == preparedPlaintext[contor1][1]) {
            preparedPlaintext[contor1][1] = 'X';
        }
    }

    printf("\nThe prepared plaintext: \n");
    for(contor1 = 0; contor1 < noRows; contor1++) {
        printf("%c %c\t", preparedPlaintext[contor1][0], preparedPlaintext[contor1][1]);
    }

    return preparedPlaintext;
}

char** encrypt(char* plaintext, char* key) {
    int contor1, contor2, contor3;
    int size = strlen(plaintext);
    char** preparedPlaintext = prepareTextToBeEncrypted(plaintext);
    int noRows = (size % 2)? size / 2 + 1 : size/2;
    char** playfairMatrix = preparePlayfairMatrix(key);
    char letter1, letter2;
    int index1Letter1, index2Letter1;
    int index1Letter2, index2Letter2;
    char** cipher = (char**)malloc(sizeof(char*) * noRows);
    int foundLetter1, foundLetter2;

    for(contor1 = 0; contor1 < noRows; contor1++) {
        cipher[contor1] = (char*)malloc(sizeof(char) * 2);
        letter1 = preparedPlaintext[contor1][0];
        letter2 = preparedPlaintext[contor1][1];
        foundLetter1 = foundLetter2 = 0;

        for(contor2 = 0; contor2 < 5; contor2++) {
            for(contor3 = 0; contor3 < 5; contor3++) {
                if(playfairMatrix[contor2][contor3] == letter1) {
                    index1Letter1 = contor2;
                    index2Letter1 = contor3;
                    foundLetter1 = 1;
                }
                else if(playfairMatrix[contor2][contor3] == letter2) {
                    index1Letter2 = contor2;
                    index2Letter2 = contor3;
                    foundLetter2 = 1;
                }
                if(foundLetter1 && foundLetter2) {
                    goto label;
                }
            }
        }
       label:
        ///1. check if the 2 letters form a square
        if(index1Letter1 != index1Letter2 && index2Letter1 != index2Letter2) {
            cipher[contor1][0] = playfairMatrix[index1Letter1][index2Letter2];
            cipher[contor1][1] = playfairMatrix[index1Letter2][index2Letter1];
        }
        ///2. check if the 2 letters are on the same row
        else if(index1Letter1 == index1Letter2) {
            cipher[contor1][0] = playfairMatrix[index1Letter1][(index2Letter1+1)%5];
            cipher[contor1][1] = playfairMatrix[index1Letter2][(index2Letter2+1)%5];
        }
        ///3. check if the 2 letters are on the same column
        else if(index2Letter1 == index2Letter2) {
            cipher[contor1][0] = playfairMatrix[(index1Letter1+1)%5][index2Letter1];
            cipher[contor1][1] = playfairMatrix[(index1Letter2+1)%5][index2Letter2];
        }
    }

    for(contor1 = 0; contor1 < 5; contor1++) {
        free(playfairMatrix[contor1]);
    }
    free(playfairMatrix);
    for(contor1 = 0; contor1 < noRows; contor1++) {
        free(preparedPlaintext[contor1]);
    }
    free(preparedPlaintext);

    return cipher;
}

char** decrypt(char* cipher, char* key) {
    int contor1, contor2, contor3;
    int size = strlen(cipher);
    char** preparedCipher = prepareTextToBeDecrypted(cipher);
    char** playfairMatrix = preparePlayfairMatrix(key);
    char letter1, letter2;
    int index1Letter1, index2Letter1;
    int index1Letter2, index2Letter2;
    char** plaintext = (char**)malloc(sizeof(char*) * size);

    for(contor1 = 0; contor1 < size; contor1++) {
        plaintext[contor1] = (char*)malloc(sizeof(char) * 2);
        letter1 = preparedCipher[contor1][0];
        letter2 = preparedCipher[contor1][1];
        for(contor2 = 0; contor2 < 5; contor2++) {
            for(contor3 = 0; contor3 < 5; contor3++) {
                if(playfairMatrix[contor2][contor3] == letter1) {
                    index1Letter1 = contor2;
                    index2Letter1 = contor3;
                }
                else if(playfairMatrix[contor2][contor3] == letter2) {
                    index1Letter2 = contor2;
                    index2Letter2 = contor3;
                }
            }
        }

        if(index1Letter1 != index1Letter2 && index2Letter1 != index2Letter2) {
            plaintext[contor1][0] = playfairMatrix[index1Letter1][index2Letter2];
            plaintext[contor1][1] = playfairMatrix[index1Letter2][index2Letter1];
        }
        else if(index1Letter1 == index1Letter2) {
            plaintext[contor1][0] = playfairMatrix[index1Letter1][(index2Letter1-1+5)%5];
            plaintext[contor1][1] = playfairMatrix[index1Letter2][(index2Letter2-1+5)%5];
        }
        else if(index2Letter1 == index2Letter2) {
            plaintext[contor1][0] = playfairMatrix[(index1Letter1-1+5)%5][index2Letter1];
            plaintext[contor1][1] = playfairMatrix[(index1Letter2-1+5)%5][index2Letter2];
        }
    }

    for(contor1 = 0; contor1 < 5; contor1++) {
        free(playfairMatrix[contor1]);
    }
    free(playfairMatrix);
    for(contor1 = 0; contor1 < size; contor1++) {
        free(preparedCipher[contor1]);
    }
    free(preparedCipher);

    return plaintext;
}

char** prepareTextToBeDecrypted(char* cipher) {
    int size = strlen(cipher);
    char** preparedCipher;
    int contor1, contor2 = 0, contor3 = 0;

    preparedCipher = (char**)malloc(sizeof(char*) * size);

    for(contor1 = 0; contor1 < size; contor1++) {
        preparedCipher[contor1] = (char*)malloc(sizeof(char) * 2);
    }

    for(contor1 = 0; contor1 < size; contor1++) {
        if(contor3 == 2) {
            contor3 = 0;
            contor2++;
        }
        if(cipher[contor1] == 'J') {
            cipher[contor1] = 'I';
        }
        preparedCipher[contor2][contor3] = toupper(cipher[contor1]);
        contor3++;
    }

    /// print the prepared cipher
    for(contor1 = 0; contor1 < size; contor1++) {
        for(contor2 = 0; contor2 < 2; contor2++){
            printf("%c", preparedCipher[contor1][contor2]);
        }
        printf("\t");
    }

    return preparedCipher;
}

void writeResultToFile(FILE* filePtr, char** textArr, int noRows) {
    int contor1, contor2;

    for(contor1 = 0; contor1 < noRows; contor1++) {
        for(contor2 = 0; contor2 < 2; contor2++) {
            fprintf(filePtr, "%c", textArr[contor1][contor2]);
        }
        fprintf(filePtr ," ");
    }
}
