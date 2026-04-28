#ifndef FUNC_F
#define FUNC_F

#include <stdio.h>
#include <stdlib.h>

int ReadFile(const char *filename, int *rows, int *cols, int ***arr);
void PrintArray(int rows, int cols, int **arr);
void WriteToFile(const char *filename, int rows, int cols, int **arr);
int RemoveRows(int N, int M, int **arr);

#endif