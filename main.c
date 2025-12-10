#include "header.h"

/*
인접행렬의 최대크기는 unsigned int만큼
거리는 int 만큼 (다익스트라에서 -1을 무한대로 사용하기 위해 signed int로 가정)
인접행렬의 원소는 거리를 의미함
input1.txt의 거리는 1로 고정
*/

void showGraph(unsigned int** matrix, unsigned int size);
unsigned int** getMatrixfromFile(FILE* input, unsigned int* matrix_size, int mode);
int charType(int c);
void push(unsigned int* stk, unsigned int size, unsigned int value, char mode);
unsigned int pop(unsigned int* stk, char mode);
void dfs(unsigned int** matrix, unsigned int size, int* visited, unsigned int* stack);
void bfs(unsigned int** matrix, unsigned int size, int* visited, unsigned int* queue);

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

        //정점 번호 넣으면됨
        //!!오버플로 주의!!
        //구리면 바꾸거나 지워도됨
        //stack[0], queue[0]은 pop으로 나가는 값의 index
        //ex) stack = {3, 2, 3, 4}; //2, 3, 4 순서대로 push됐고 4, 3, 2 순서대로 pop됨
        //ex) queue = {4, 1, 2, 3, 4} //4, 3, 2, 1 순서대로 push됐고 4, 3, 2, 1 순서대로 pop됨
        //push, pop 함수 쓰면됨
        unsigned int* stack = (unsigned int*)calloc(matrix_size + 1, sizeof(unsigned int));
        unsigned int* queue = (unsigned int*)calloc(matrix_size + 1, sizeof(unsigned int));

        //방문하면 0에서 1로 바꿈
        int* visited = (int*)calloc(matrix_size, sizeof(int));

        printf("Graph [%d]:\n", graph_num);
        showGraph(matrix1, matrix_size);



        {
            /*
            여기에 1번 문제 작성
            matrix1에 각 그래프를 순차적으로 저장하고
            각각 출력하는 방식임
            즉 한 그래프에 대한 dfs 및 bfs 수행 후 출력하면 됨
            */
            // 그래프 탐방 수행 by allpe 1025
            printf("----------------------------\n");
            printf("DFS\n");
            dfs(matrix1, matrix_size, visited, stack);
            printf("BFS\n");
            bfs(matrix1, matrix_size, visited, queue);

            for (unsigned int i = 0; i < matrix_size; i++) {
                if (!visited[i]) printf("Unreachable Node: %u\n", i + 1);
            }
            printf("============================\n");
        }

        //free(stack);
        //free(queue);
        //free(visited);

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



        {
            /*
            여기에 2번 문제 작성
            matrix1에 각 그래프를 순차적으로 저장하고
            각각 출력하는 방식임
            즉 한 그래프에 대한 경로 및 길이 출력하면 됨
            */
            

            //map2 초기화 및 할당
            struct MatrixMap* map2;
            map2 = (struct MatrixMap*)malloc(sizeof(struct MatrixMap) * matrix_size);
            if (map2 == NULL) {
                printf("Error: 메모리 할당 실패 (map2).\n");
                // matrix2 메모리 해제
                if (matrix2) {
                    for (unsigned int i = 0; i < matrix_size; i++) {
                        free(*(matrix2 + i));
                    }
                    free(matrix2);
                }
                fclose(input2);
                return 1;
            }

            // 1. map2 초기화 (distance와 is_visited 필드 사용)
            for (unsigned int i = 0; i < matrix_size; i++) {
                map2[i].is_visited = 0; 
                strcpy(map2[i].path, "1");
                if (i == 0) {
                    map2[i].distance = 0; // 시작점은 0
                }
                else {
                    map2[i].distance = -1; // 도달 불가능은 -1
                }
            }


            // 2. 다익스트라 메인 로직 
         
            for (unsigned int count = 0; count < matrix_size; count++) {

                // 2-1. 최소 거리 노드 (u) 선택 단계
                int u = -1;
                int min_dist = 2147483647; // INT_MAX (충분히 큰 양수)

                for (unsigned int i = 0; i < matrix_size; i++) {
                    // 미방문 (!map2[i].is_visited), 도달 가능 (-1 아님), 최소 거리일 때
                    if (!map2[i].is_visited && map2[i].distance != -1 && map2[i].distance < min_dist) {
                        min_dist = map2[i].distance;
                        u = i;
                    }
                }

                // 2-2. 종료 조건 및 방문 처리
                if (u == -1) {
                    break;
                }
                map2[u].is_visited = 1; // 방문 처리

                // 2-3. 거리 갱신 (Relaxation) 단계
                for (unsigned int v = 0; v < matrix_size; v++) {

                    // u에서 v로 가는 간선이 존재하고, v가 미방문 노드일 때
                    if (!map2[v].is_visited && matrix2[u][v] != 0) {

                        int weight = matrix2[u][v];
                        int new_dist = map2[u].distance + weight;

                        // v가 도달 불가능(-1)이거나, u를 거치는 경로가 더 짧다면 갱신
                        if (map2[v].distance == -1 || new_dist < map2[v].distance) {
                            map2[v].distance = new_dist;

                            // 경로 갱신
                            strcpy(map2[v].path, map2[u].path);
                            char buffer[10];
                            sprintf(buffer, " - %d", v + 1);
                            strcat(map2[v].path, buffer);
                        }
                    }
                }
            }


            //결과 출력
            printf("-----------------------------------\n");
            printf("StartingPoint: 1\n");
            for (unsigned int i = 1; i < matrix_size; i++) {
                if (map2[i].distance == -1) { // 도달 불가능 조건 -1로 체크
                    printf("Vertex [%d]: null\n", i + 1);

                }
                else {
                    printf("Vertex [%d]: %s, Distance: %d\n", i + 1, map2[i].path, map2[i].distance); 
                }

            }
            printf("===================================\n\n");



            if (map2) {
                free(map2);
            }
        }



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
