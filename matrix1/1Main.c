#include "1.h"

int main(void) {
    int amount;
    int rows = 0, cols = 0;
    int **arr;

    ReadFile("data.txt", &rows, &cols, &arr);
    if (rows == 0 || cols == 0 || rows < 0 || cols < 0) {
        return -1;
    }
printf("given: \n");
    PrintArray(rows, cols, arr);
    amount = RemoveRows(rows, cols, arr);
printf("new: \n");
    PrintArray(rows - amount, cols, arr);
    WriteToFile("res.txt", rows - amount, cols, arr);
	printf("\nArray in a row: ");
	for(int i=0;i<rows-1;i++){
        for(int j=0;j<cols;j++){
         printf("|%d|", arr[i][j]);   
        }
        }
    for(int p=0; p<rows;p++){
     free(arr[p]);   
    }
    free(arr);
 
    return 0;
}
