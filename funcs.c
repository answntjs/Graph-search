#include "header.h"

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
    }
    else if (c >= 'A' && c <= 'Z') {
        return 2;
    }
    else if (c >= 'a' && c <= 'z') {
        return 2;
    }
    else if (c == ' ') {
        return 3;
    }
    else {
        return 0;
    }
}

unsigned int** getMatrixfromFile(FILE* input, unsigned int* matrix_size, int mode) {
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
    for (unsigned int i = 0; i < size; i++) {
        *(matrix + i) = (unsigned int*)calloc(size, sizeof(unsigned int));
        if (!*(matrix + i)) {
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
                    }
                    else {
                        if (mode == 1) {
                            col = num - 1;
                            if (row < size && col < size) matrix[row][col] = 1;
                        }
                        else {
                            if (oddeven % 2) {
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

void push(unsigned int* data, unsigned int size, unsigned int value, char mode){
    if(*data >= size) return;
    if(mode == 's'){
        *(data+(*data)+1) = value;
        (*data)++;
    }else if(mode == 'q'){
        if(*data > 0) memmove(data+2, data+1, *data*sizeof(unsigned int));
        data[1] = value;
        (*data)++;
    }else return;
}

unsigned int pop(unsigned int* data, char mode){
    if(*data == 0) return 0;
    unsigned int r = *(data+(*data));
    (*data)--;
    return r;
}

void dfs(unsigned int** matrix, unsigned int size, int* visited, unsigned int* stack) {
    //  초기화
    for (unsigned int i = 0; i < size; i++) {
        visited[i] = 0;
    }
    for (unsigned int i = 0; i <= size; i++) {
        stack[i] = 0;
    }

    // 시작 정점 push
    push(stack, size + 1, 1, 's');

    unsigned int visit_count = 0;

    // DFS
    while (1) {
        unsigned int v = pop(stack, 's');

        // pop 결과 0이면 break
        if (v == 0) break;

        unsigned int idx = v - 1;

        // 방문한 정점이면 comtinue
        if (visited[idx]) continue;

        // 방문 표시
        visited[idx] = 1;

        // 방문 순서
        if (visit_count == 0) {
            // 첫 번째 정점
            printf("%u", v);
        }
        else {
            // 그 이후 정점
            printf(" - %u", v);
        }
        visit_count++;

        // 인접 정점 push
        // 작은 번호 먼저 방문
        for (int w = (int)size; w >= 1; w--) {
            if (matrix[idx][w - 1] != 0 && !visited[w - 1]) {
                // v 와 w 가 인접, 방문하지 않은 경우
                push(stack, size + 1, (unsigned int)w, 's');
            }
        }
    }
    printf("\n");
}

void bfs(unsigned int** matrix, unsigned int size, int* visited, unsigned int* queue) {
    // 초기화
    for (unsigned int i = 0; i < size; i++) {
        visited[i] = 0;
    }
    for (unsigned int i = 0; i <= size; i++) {
        queue[i] = 0;
    }

    // 시작 정점 enqueue
    push(queue, size + 1, 1, 'q');
    visited[0] = 1;      // BFS는 enqueue 시점에 방문 표시

    unsigned int visit_count = 0;

    while (1) {
        unsigned int v = pop(queue, 'q');    // dequeue

        if (v == 0) break;

        unsigned int idx = v - 1;

        // 출력
        if (visit_count == 0) {
            printf("%u", v);
        }
        else {
            printf(" - %u", v);
        }
        visit_count++;

        // 인접 정점 탐색
        for (unsigned int w = 1; w <= size; w++) {
            if (matrix[idx][w - 1] != 0 && !visited[w - 1]) {
                push(queue, size + 1, w, 'q');
                visited[w - 1] = 1;   // enqueue 시 방문 체크
            }
        }
    }
    printf("\n");
}


    






















