#include "header.h"

/*
인접행렬의 최대크기는 unsigned int만큼
거리는 unsigned int 만큼
인접행렬의 원소는 거리를 의미함
input1.txt의 거리는 1로 고정
*/

void showGraph(unsigned int** matrix, unsigned int size);
unsigned int** getMatrixfromFile(FILE* input, unsigned int* matrix_size, int mode);
int charType(int c);

int main() {
    
	//input1.txt 처리
    printf("1. DFS / BFS\n\n");

    FILE* input1 = fopen("input1.txt", "r");
    if (input1 == NULL) {
        printf("Error: input1.txt.\n");
        return 1;
    }

    int graph_num = 1;
    unsigned int matrix_size;
    
    while (1) {
        unsigned int** matrix1 = NULL;
        matrix_size = 0;

		matrix1 = getMatrixfromFile(input1, &matrix_size, 1);
        if (matrix_size == 0) break;
        
        printf("Graph [%d]:\n", graph_num);
        showGraph(matrix1, matrix_size);

        /*
        여기에 1번 문제 작성
        matrix1에 각 그래프를 순차적으로 저장하고
        각각 출력하는 방식임
        즉 한 그래프에 대한 dfs 및 bfs 수행 후 출력하면 됨
        */
        if (matrix1) {
            for (unsigned int i = 0; i < matrix_size; i++) {
                free(*(matrix1 + i));
            }
            free(matrix1);
        }
        graph_num++;
    }

    fclose(input1);

















    //input2.txt 처리
    printf("2. Dijkstra\n\n");

    FILE* input2 = fopen("input2.txt", "r");
    if (input2 == NULL) {
        printf("Error: input2.txt.\n");
        return 1;
    }

    graph_num = 1;

    while (1) {
        unsigned int** matrix2 = NULL;
        matrix_size = 0;

		matrix2 = getMatrixfromFile(input2, &matrix_size, 2);
        if (matrix_size == 0) break;

        printf("Graph [%d]:\n", graph_num);
        showGraph(matrix2, matrix_size);

        /*
        여기에 1번 문제 작성
        matrix1에 각 그래프를 순차적으로 저장하고
        각각 출력하는 방식임
        즉 한 그래프에 대한 dfs 및 bfs 수행 후 출력하면 됨
        */
        if (matrix2) {
            for (unsigned int i = 0; i < matrix_size; i++) {
                free(*(matrix2 + i));
            }
            free(matrix2);
        }
        graph_num++;
    }

    fclose(input2);
    return 0;
}

void showGraph(unsigned int** matrix, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            printf("%u ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int charType(int c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }else if (c >= 'A' && c <= 'Z') {
        return 2;
    }else if (c >= 'a' && c <= 'z') {
        return 2;
    }else if (c == ' ') {
        return 3;
    }else {
        return 0;
    }
}

unsigned int ** getMatrixfromFile(FILE* input, unsigned int* matrix_size, int mode) {
	unsigned int** matrix = NULL;
	unsigned int size, row, col, oddeven, weight;
    int c;

    //행렬 크기 확인
    if (fscanf(input, "%u", &size) != 1) return NULL;
    *matrix_size = size;
    if (size == 0) return NULL;        //자료구조상 0이 나올수 없어서 0 나오면 파일이 비어있는거라고 간주함
	
    while ((c = fgetc(input)) != EOF && c != '\n');

    //행렬 메모리 동적할당
    matrix = (unsigned int**)malloc(sizeof(unsigned int*) * size);
    if (!matrix) {
        printf("Error: memory allocation: matrix.\n");
        return NULL;
    }
    for(unsigned int i=0;i<size;i++){
        *(matrix + i)=(unsigned int*)calloc(size, sizeof(unsigned int));
        if(!*(matrix + i)){
            printf("Error: memory allocation: matrix[%u].\n", i);
            return NULL;
        }
    }

    for (unsigned int i = 0; i < size; i++) {
        oddeven = 0;

        while (1) {
            c = fgetc(input);
            if (c == EOF) return matrix;
            if (c == '\n') break;
            if (charType(c) == 3) continue;
            if (charType(c) == 1) {
                ungetc(c, input);
                unsigned int num;
                if (fscanf(input, "%u", &num) == 1) {
                    if (!oddeven) {
                        row = num - 1;
                    }else{
                        if(mode == 1){
                            col = num - 1;
                            if (row < size && col < size) matrix[row][col] = 1;
                        }else{
                            if (oddeven % 2){
                                col = num - 1;
                            }
                            else {
								weight = num;
                                if (row < size && col < size) {
                                    matrix[row][col] = weight;
                                }
                            }
                        }
                    }
                    oddeven++;
                }
            }
        }
    }
	return matrix;
}