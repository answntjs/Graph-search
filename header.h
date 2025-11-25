#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showGraph(unsigned int** matrix, unsigned int size); //인접행렬 출력

unsigned int** getMatrixfromFile(FILE*, unsigned int*, int); //동적할당 후 파일 내용에 따라 인접행렬을 1개 생성 후 행렬과 그 크기를 반환

int charType(int); //해당 문자의 타입을 반환(숫자, 영문, 공백, 기타)
