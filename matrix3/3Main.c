#include "3.h"

int main(void) {
    int amount;
    int rows = 0, *sizes;
    int **arr;

    ReadFile("data.txt", &arr, &rows, &sizes);
    if (rows <= 0) {
        return -1;
    }
    printf("given: \n");
    PrintArray(rows, sizes, arr);
    amount = RemoveRows(rows, sizes, arr);
    printf("new: \n");
    rows = rows - amount;
    PrintArray(rows, sizes, arr);
    WriteToFile("res.txt", rows, sizes, arr);
	printf("\nArray in a row: ");
	for(int i = 0; i < rows; i++){
        for(int j = 0; j < sizes[i]; j++){
            printf("|%d|", arr[i][j]);
        }
    }
    printf("\n");
    for(int p = 0; p < rows; p++){
        free(arr[p]);
    }
    free(arr);
    free(sizes);
    return 0;
}
