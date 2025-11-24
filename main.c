#include "header.h"



int main() {
    FILE* input1 = fopen("input1.txt", "r");
    if (input1 == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    printf("%c",input1[0]);



    fclose(input1);
    return 0;
}