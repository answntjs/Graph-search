#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//인접행렬 출력
void showGraph(unsigned int** matrix, unsigned int size); 

//동적할당 후 파일 내용에 따라 인접행렬을 1개 생성 후 행렬과 그 크기를 반환
unsigned int** getMatrixfromFile(FILE*, unsigned int*, int); 

//해당 문자의 타입을 반환(숫자, 영문, 공백, 기타)
int charType(int); 

//배열에 값을 저장함; 's' for stack, 'q' for queue.
void push(unsigned int* stk, unsigned int size, unsigned int value, char mode);

//배열에서 값을 꺼내옴; 's' for stack, 'q' for queue.
unsigned int pop(unsigned int* stk, unsigned int size, char mode);
