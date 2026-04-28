#include "2.h"

int main(void) {
     int result;
    char SInputFile[] = "input.txt";
    char* word = (char*)malloc(LEN * sizeof(char));
    word[0] = '\0';
     result = search(SInputFile, word);

    if (result == -1) {
        printf("file cannot open\n");
    }
    if (result == 0) {
        printf("%s\n", word);
    }
    if (result == 1) {
        printf("no needed words\n");
    }
    free(word);
    return 0;
}
