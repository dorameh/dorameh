#ifndef FUNC_F
#define FUNC_F

#include <stdio.h>
#include <stdlib.h>

int ReadFile(const char *filename, int ***arr, int *rows, int **sizes);
void PrintArray(int rows, int *sizes, int **arr);
void WriteToFile(const char *filename, int rows, int *sizes, int **arr);
int RemoveRows(int rows, int *sizes, int **arr);

#endif
