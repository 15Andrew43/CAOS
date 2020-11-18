// #include <conio.h>
#include <stdio.h>
#include <stdlib.h>
 
#define ERROR_FILE_OPEN -3
 
int main() {
    FILE *output = NULL;
    int number = 1543;
 
    output = fopen("input", "wb");
    if (output == NULL) {
        printf("Error opening file");
        exit(ERROR_FILE_OPEN);
    }
    number = 1543;
    fwrite(&number, sizeof(int), 1, output);
    number = 17;
    fwrite(&number, sizeof(int), 1, output);

    number = 179;
    fwrite(&number, sizeof(int), 1, output);
    number = 0;
    fwrite(&number, sizeof(int), 1, output);

    number = 2020;
    fwrite(&number, sizeof(int), 1, output);
    number = 9;
    fwrite(&number, sizeof(int), 1, output);

    fclose(output);
    return 0;
}