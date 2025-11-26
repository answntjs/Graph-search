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
void push(unsigned int* stk, char mode);
void pop(unsigned int* stk char mode);

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

		//방문하면 0에서 1로 바꿈
		int* visited = (int*)calloc(matrix_size, sizeof(int));

		//정점 번호 넣으셈
		//push, pop 함수 쓰면됨
		unsigned int* stack = (unsigned int*)calloc(matrix_size, sizeof(unsigned int));
		unsigned int* queue = (unsigned int*)calloc(matrix_size, sizeof(unsigned int));

		
		
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
        여기에 2번 문제 작성
        matrix1에 각 그래프를 순차적으로 저장하고
        각각 출력하는 방식임
        즉 한 그래프에 대한 경로 및 길이 출력하면 됨
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
