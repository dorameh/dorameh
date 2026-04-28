#include "2.h"

int checkWord(char* word) {
    int flag = 0;

    for (size_t i = 0; i < strlen(word); ++i) {
        if (!isalpha(word[i])) {
            return 0;
        }
        if (isupper(word[i])) {
            ++flag;
        }
    }

    if (flag == 0) {
        return 0;
    }
    return 1;
}

int search(const char* SInputFile, char* word) {
    int flag = 0;
    int len;
    char symbol;
    char* temp = (char*)malloc(LEN * sizeof(char)); 
    FILE* fin = fopen(SInputFile, "r");

    if (fin == NULL) {
        free(temp);
        return -1;
    }

    while (!feof(fin)) {
        symbol = fgetc(fin);
        len = 0;
        while (symbol != ' ' && symbol != '\t' && symbol != '\n' && (int)symbol != -1) {
            temp[len] = symbol;
            ++len;
            symbol = fgetc(fin);
        }
        temp[len] = '\0';
        
        if (checkWord(temp) && strlen(word) < strlen(temp)) {
            strcpy(word, temp);
            flag = 1;   
        }
    }

    free(temp);
    fclose(fin);

    if (flag == 1) {
        return 0;
    }
    else {
        return 1;
    }
}