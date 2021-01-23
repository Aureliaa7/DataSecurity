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
        if((c != 32) && (c != 10))
        {
            if(islower(c)) {
                c = toupper(c);
            }
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

    // start the matrix with the letters of the key
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

    // complete the matrix with the remaining letters from alphabet
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
    return playfairMatrix;
}

char** prepareTwoSquareMatrix(char* key1, char* key2) {
    char** playfairMatrix1 = (char**)malloc(sizeof(char*) * 5);
    char** playfairMatrix2 = (char**)malloc(sizeof(char*) * 5);
    char** twoSquareMatrix = (char**)malloc(sizeof(char*) * 10);
    int contor1, contor2, contor3;

     for(contor1 = 0; contor1 < 10; contor1++) {
        if(contor1 < 5) {
            playfairMatrix1[contor1] = (char*)malloc(sizeof(char) * 5);
            playfairMatrix2[contor1] = (char*)malloc(sizeof(char) * 5);
        }
        twoSquareMatrix[contor1] = (char*)malloc(sizeof(char) * 5);
     }
    playfairMatrix1 = preparePlayfairMatrix(key1);
    playfairMatrix2 = preparePlayfairMatrix(key2);

    for(contor1 = 0; contor1 < 10; contor1++) {
        for(contor2 = 0; contor2 < 5; contor2++) {
            if(contor1 < 5) {
                twoSquareMatrix[contor1][contor2] = playfairMatrix1[contor1][contor2];
            }
            else if(contor1 >= 5) {
                twoSquareMatrix[contor1][contor2] = playfairMatrix2[contor1%5][contor2];
            }
        }
    }

    for(contor1 = 0; contor1 < 5; contor1++) {
        free(playfairMatrix1[contor1]);
        free(playfairMatrix2[contor1]);
    }
    free(playfairMatrix1);
    free(playfairMatrix2);

    printf("\n\n*** The two square matrix ***\n");
    for(contor1 = 0; contor1 < 10; contor1++) {
        for(contor2 = 0; contor2 < 5; contor2++) {
            printf("%c ", twoSquareMatrix[contor1][contor2]);
        }
          if(contor1 == 4)
            {
                printf("\n------------");
            }
        printf("\n");
    }

    return twoSquareMatrix;
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
        if(key[contor1] == 'J')
        {
            key[contor1] = 'I';
        }
    }

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

   printf("\n*** The prepared key is: %s\n", preparedKey);
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
    return preparedPlaintext;
}

char** encrypt(char* plaintext, char* key1, char* key2) {
    int contor1, contor2, contor3;
    int size = strlen(plaintext);
    char** preparedPlaintext = prepareTextToBeEncrypted(plaintext);
    int noRows = (size % 2)? size / 2 + 1 : size/2;
    char** twoSquareMatrix = prepareTwoSquareMatrix(key1, key2);
    char letter1, letter2;
    int index1Letter1, index2Letter1;
    int index1Letter2, index2Letter2;
    char** cipher = (char**)malloc(sizeof(char*) * noRows);
    int foundLetter1, foundLetter2;

    for(contor1 = 0; contor1 < noRows; contor1++) {
        cipher[contor1] = (char*)malloc(sizeof(char) * 2);
        letter1 = preparedPlaintext[contor1][0];
        letter2 = preparedPlaintext[contor1][1];
        foundLetter1 = 0;
        foundLetter2 = 0;

        for(contor2 = 0; contor2 < 10; contor2++) {
            for(contor3 = 0; contor3 < 5; contor3++) {
                // search the 1st letter in the upper matrix
                if(!foundLetter1) {
                    if(contor2 < 5) {
                        if(twoSquareMatrix[contor2][contor3] == letter1) {
                            index1Letter1 = contor2;
                            index2Letter1 = contor3;
                            foundLetter1 = 1;
                        }
                    }
                }

                // search the 2nd letter in the bottom matrix
                if(!foundLetter2) {
                    if(contor2 >= 5) {
                        if(twoSquareMatrix[contor2][contor3] == letter2) {
                            index1Letter2 = contor2;
                            index2Letter2 = contor3;
                            foundLetter2 = 1;
                        }
                    }
                }

                if(foundLetter1 && foundLetter2) {
                    goto et;
                }
            }
        }
        et:
         // check if the 2 letters are on the same column
        if(index2Letter1 == index2Letter2) {
            cipher[contor1][0] = twoSquareMatrix[(index1Letter1+1)%5][index2Letter1];
            if(index1Letter2 < 9) {
                cipher[contor1][1] = twoSquareMatrix[(index1Letter2+1)%10][index2Letter2];
            }
            else {
                cipher[contor1][1] = twoSquareMatrix[5][index2Letter2];
            }
        }

        // the 2 letters form a square/rectangle
       else {
            cipher[contor1][0] = twoSquareMatrix[index1Letter1][index2Letter2];
            cipher[contor1][1] = twoSquareMatrix[index1Letter2][index2Letter1];
        }
    }

    for(contor1 = 0; contor1 < 10; contor1++) {
        free(twoSquareMatrix[contor1]);
    }
    free(twoSquareMatrix);
    for(contor1 = 0; contor1 < noRows; contor1++) {
        free(preparedPlaintext[contor1]);
    }
    free(preparedPlaintext);

    return cipher;
}

char** decrypt(char* cipher, char* key1, char*key2) {
    int contor1, contor2, contor3;
    int size = strlen(cipher);
    char** preparedCipher = prepareTextToBeDecrypted(cipher);
    char** twoSquareMatrix = prepareTwoSquareMatrix(key1, key2);
    char letter1, letter2;
    int index1Letter1, index2Letter1;
    int index1Letter2, index2Letter2;
    char** plaintext = (char**)malloc(sizeof(char*) * size);
    int foundLetter1, foundLetter2;

    for(contor1 = 0; contor1 < size; contor1++) {
        plaintext[contor1] = (char*)malloc(sizeof(char) * 2);
        letter1 = preparedCipher[contor1][0];
        letter2 = preparedCipher[contor1][1];
        foundLetter1 = 0;
        foundLetter2 = 0;

        for(contor2 = 0; contor2 < 10; contor2++) {
            for(contor3 = 0; contor3 < 5; contor3++) {
                // search the 1st letter in the upper square
                if(!foundLetter1 && contor2 < 5) {
                    if(twoSquareMatrix[contor2][contor3] == letter1) {
                        index1Letter1 = contor2;
                        index2Letter1 = contor3;
                        foundLetter1 = 1;
                    }
                }
                // search the 2nd letter in the bottom square
                if(!foundLetter2 && contor2 >= 5) {
                    if(twoSquareMatrix[contor2][contor3] == letter2) {
                        index1Letter2 = contor2;
                        index2Letter2 = contor3;
                        foundLetter2 = 1;
                    }
                }
                if(foundLetter1 && foundLetter2) {
                    goto et;
                }
            }
        }

        et:
        // check if the 2 letters are on the same column
        if(index2Letter1 == index2Letter2) {
            plaintext[contor1][0] = twoSquareMatrix[(index1Letter1+5-1)%5][index2Letter1];
            if(index1Letter2 < 9) {
                plaintext[contor1][1] = twoSquareMatrix[(index1Letter2-1+10)%10][index2Letter2];
            }
            else {
                plaintext[contor1][1] = twoSquareMatrix[9][index2Letter2];
            }
        }

        // the 2 letters form a square/rectangle
       else {
            plaintext[contor1][0] = twoSquareMatrix[index1Letter1][index2Letter2];
            plaintext[contor1][1] = twoSquareMatrix[index1Letter2][index2Letter1];
        }
    }

    for(contor1 = 0; contor1 < 10; contor1++) {
        free(twoSquareMatrix[contor1]);
    }
    free(twoSquareMatrix);

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

char* getKeyFromKeyboard() {
    char* key = (char*)malloc(KEY_LENGTH * sizeof(char));
    int contor;
    int keyLength;

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
