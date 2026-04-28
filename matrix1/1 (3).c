#include "1.h"

int ReadFile(const char *filename, int *rows, int *cols, int ***arr) {
    FILE *reader = fopen(filename, "r");
    if (reader == NULL) {
        printf("can not open reader-file\n");
        return -1;
    }

    fscanf(reader, "%d %d", rows, cols);
     
    if (*rows == 0 || *cols == 0 || *rows < 0 || *cols < 0) {
        printf(" invalid data\n");
        fclose(reader);
        return -1;
    }

    *arr = (int **)malloc(*rows * sizeof(int *));
    if(arr==NULL){
     printf("allocation memory fail");
     
fclose(reader);
return -1;
        
    }
    for (int p = 0; p < *rows; p++) {
         (*arr)[p] = malloc(*cols * sizeof(int));
    	 if((*arr)[p]==NULL){
     	     printf("allocation memory fail");
             free(arr);
             fclose(reader);
             return -1;
         }
    }

    for (int s = 0; s < *rows; s++) {
        for (int c = 0; c < *cols; c++) {
            fscanf(reader, "%d", &(*arr)[s][c]);
        }
    }

    fclose(reader);
   
    return 0;
}

void PrintArray(int rows, int cols, int **arr) {

    for (int s = 0; s < rows; s++) {
        for (int c = 0; c < cols; c++) {
            if (c == cols - 1) {
                printf("%d\n", arr[s][c]);
            } else {
                printf("%d ", arr[s][c]);
            }
        }
    }
}

void WriteToFile(const char *filename, int rows, int cols, int **arr) {
    FILE *writer = fopen(filename, "w");
    if (writer == NULL) {
        printf("can not open writer-file\n");
        return;
    }

    for (int s = 0; s < rows; s++) {
        for (int c = 0; c < cols; c++) {
            fprintf(writer, "%d ", arr[s][c]);
        }
        fprintf(writer, "\n");
    }

    fclose(writer);
}

int RemoveRows(int N, int M, int **arr) {
    int amount = 0;
    int *maxIndex ;
    int *max = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; ++i) {
        max[i] = arr[0][i];
    }
   maxIndex = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; ++i) {
        maxIndex[i] = 0;
    }
    for(int j = 0; j < M; j++){
        for(int i = 0; i < N; i++){
            if(arr[i][j] > max[j]){
                max[j] = arr[i][j];
                maxIndex[j] = i;
            } else if (i != 0 && arr[i][j] == max[j]) {
                
                maxIndex[j] = -1;
            }
        }
    }
    for(int i = 0; i < N; i++){
        int isMax = 1;
        for(int j = 0; j < M; j++){
            if(i != maxIndex[j]){
                isMax = 0;
                break;
            }
        }
        if(isMax) {
            for(int k = i; k < N; k++) {
            
                for (int j = 0; j < M; j++) {
                    if (k + 1 < N) {
                        arr[k][j] = arr[k + 1][j];
                    }
                }
            }
            amount++;
            N--;
        }
		
    }
	free(max);
	free(maxIndex);
    return amount;
}
