#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_MAX 512 //문제 내에서 path 최대사이즈는 (3+1+1)*99<512

//Struct for Dijkstra path and distance; by leesh200303-ai
struct MatrixMap{
	char path[SIZE_MAX];
	unsigned int distance;
};

//인접행렬 출력
void showGraph(unsigned int** matrix, unsigned int size); 

//동적할당 후 파일 내용에 따라 인접행렬을 1개 생성 후 행렬과 그 크기를 반환
unsigned int** getMatrixfromFile(FILE*, unsigned int*, int); 

//해당 문자의 타입을 반환(숫자, 영문, 공백, 기타)
int charType(int); 

//배열에 값을 저장함; 's' for stack, 'q' for queue.
void push(unsigned int*, unsigned int, unsigned int, char);

//배열에서 값을 꺼내옴; 's' for stack, 'q' for queue; 모드왜넣음
unsigned int pop(unsigned int*, char);

//Depth-First Search; by allpe 1025
void dfs(unsigned int** matrix, unsigned int size, int* visited, unsigned int* stack);

//Breadth-First Search; by allpe 1025
void bfs(unsigned int** matrix, unsigned int size, int* visited, unsigned int* queue);