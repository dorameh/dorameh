#include "3.h"
#include <limits.h>

int ReadFile(const char *filename, int ***arr, int *rows, int **sizes) {
    char c;
    int p;
    int cols;
    int sign;
    FILE *reader = fopen(filename, "r");
    if (reader == NULL) {
        printf("can not open reader-file\n");
        return -1;
    }

    *rows = 10;

    *arr = (int **)malloc(*rows * sizeof(int *));
    if(arr == NULL){
        printf("allocation memory fail");
        fclose(reader);
        return -1;
    }

    *sizes = (int *) malloc(*rows * sizeof(int));
    c = 0;
    for (p = 0; p < *rows; ++p) {
        if (c == EOF) {
            break;
        }
        if (p == *rows - 1) {
            *rows *= 2;
            *arr = (int **) realloc(*arr, *rows * sizeof(int *));
            if (*arr == NULL) {
                printf("allocation memory fail");
                free(arr);
                fclose(reader);
                return -1;
            }
            *sizes = (int *) realloc(*sizes, *rows * sizeof(int));
            if (*sizes == NULL) {
                printf("allocation memory fail");
                free(arr);
                fclose(reader);
                return -1;
            }
        }
        cols = 10;
        (*arr)[p] = (int *) malloc(cols * sizeof(int));
        if((*arr)[p] == NULL) {
            printf("allocation memory fail");
            free(arr);
            fclose(reader);
            return -1;
        }
        for (int q = 0; q < cols; ++q) {
            while (c != EOF && c != '\n' && !(c == '-' || (c >= '0' && c <= '9'))) {
                c = fgetc(reader);
            }
            if (c == '\n' || c == EOF) {
                (*sizes)[p] = q;
                if (c == '\n') {
                    c = fgetc(reader);
                }
                break;
            }
            if (q == cols - 1) {
                cols *= 2;
                (*arr)[p] = realloc((*arr)[p], cols * sizeof(int));
                if ((*arr)[p] == NULL) {
                    printf("allocation memory fail");
                    free(arr);
                    fclose(reader);
                    return -1;
                }
            }
            sign = 1;
            if (c == '-') {
                sign = -1;
                c = fgetc(reader);
            }
            (*arr)[p][q] = 0;
            while (c >= '0' && c <= '9') {
                (*arr)[p][q] *= 10;
                (*arr)[p][q] += c - '0';
                c = fgetc(reader);
            }
            (*arr)[p][q] *= sign;
        }
    }
    *rows = p;
    fclose(reader);
    return 0;
}

void PrintArray(int rows, int *sizes, int **arr) {
    for (int s = 0; s < rows; s++) {
        for (int c = 0; c < sizes[s]; c++) {
            if (c == sizes[s] - 1) {
                printf("%d\n", arr[s][c]);
            } else {
                printf("%d ", arr[s][c]);
            }
        }
    }
}

void WriteToFile(const char *filename, int rows, int *sizes, int **arr) {
    FILE *writer = fopen(filename, "w");
    if (writer == NULL) {
        printf("can not open writer-file\n");
        return;
    }

    for (int s = 0; s < rows; s++) {
        for (int c = 0; c < sizes[s]; c++) {
            fprintf(writer, "%d ", arr[s][c]);
        }
        fprintf(writer, "\n");
    }

    fclose(writer);
}

int RemoveRows(int rows, int *sizes, int **arr) {
    int cols = 0;
    int amount = 0;
    int *maxIndex;
    int *max;
    for (int i = 0; i < rows; ++i) {
        if (sizes[i] > cols) {
            cols = sizes[i];
        }
    }
    max = (int *)malloc(cols * sizeof(int));
    for (int i = 0; i < cols; ++i) {
        max[i] = INT_MIN;
    }
    maxIndex = (int *)malloc(cols * sizeof(int));
    for (int i = 0; i < cols; ++i) {
        maxIndex[i] = -1;
    }
    for(int j = 0; j < cols; j++) {
        for(int i = 0; i < rows; i++) {
            if (sizes[i] <= j) {
                continue;
            }
            if(arr[i][j] > max[j]){
                max[j] = arr[i][j];
                maxIndex[j] = i;
            } else if (i != 0 && arr[i][j] == max[j]) {
                maxIndex[j] = -1;
            }
        }
    }

    for(int i = 0; i < rows; i++){
        int isMax = 1;
        for(int j = 0; j < sizes[i]; j++){
            if(i != maxIndex[j]){
                isMax = 0;
                break;
            }
        }
        if(isMax) {
            free(arr[i]);
            for(int k = i; k < rows - 1; k++) {
                arr[k] = arr[k + 1];
                sizes[k] = sizes[k + 1];
            }
            amount++;
            rows--;
            break;
        }

    }
	free(max);
	free(maxIndex);
    return amount;
}
