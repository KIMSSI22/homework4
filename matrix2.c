#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **matrix, int row, int col);  //프린트 함수
int **addition_matrix(int **matrix1, int row1, int col1, int **matrix2, int row2, int col2);  //덧셈 함수
int **subtraction_matrix(int **matrix1, int row1, int col1, int **matrix2, int row2, int col2);  //뺄셈 함수
int **transpose_matrix(int **matrix, int row, int col);  //전치 행렬 함수
int **multiply_matrix(int **matrix1, int row1, int col1, int **matrix2, int row2, int col2);  //곱셈 함수
void free_matrix(int **matrix, int row);  //메모리 해제 함수

int main() {
    printf("----- 김민서 2022040010 -----\n\n");

    int row1, col1, row2, col2;
    printf("Enter row and column of matrix A: ");  //행렬 A의 행과 열 입력
    scanf("%d %d", &row1, &col1);
    printf("Enter row and column of matrix B: ");  //행렬 B의 행과 열 입력
    scanf("%d %d", &row2, &col2);

    //동적 메모리 할당으로 행렬 A의 값을 받음
    int **matrix1 = (int **)malloc(row1 * sizeof(int *));  
    for (int i = 0; i < row1; i++) {
        matrix1[i] = (int *)malloc(col1 * sizeof(int));
        for (int j = 0; j < col1; j++) {
            printf("Enter the element (%d, %d) of matrix A: ", i+1, j+1);
            scanf("%d", &matrix1[i][j]);
        }
    }

    //동적 메모리 할당으로 행렬 B의 값을 받음
    int **matrix2 = (int **)malloc(row2 * sizeof(int *)); 
    for (int i = 0; i < row2; i++) {
        matrix2[i] = (int *)malloc(col2 * sizeof(int));
        for (int j = 0; j < col2; j++) {
            printf("Enter the element (%d, %d) of matrix B: ", i+1, j+1);
            scanf("%d", &matrix2[i][j]);
        }
    }

    // A, B의 행렬을 출력
    printf("\nMatrix A:\n");
    print_matrix(matrix1, row1, col1);
    printf("\nMatrix B:\n");
    print_matrix(matrix2, row2, col2);

    //A + B
    int **sum_matrix = addition_matrix(matrix1, row1, col1, matrix2, row2, col2);
    if (sum_matrix != NULL) {
        printf("\nA + B:\n");
        print_matrix(sum_matrix, row1, col1);
        free_matrix(sum_matrix, row1);
    }

    //A − B
    int **diff_matrix = subtraction_matrix(matrix1, row1, col1, matrix2, row2, col2);
    if (diff_matrix != NULL) {
        printf("\nA - B:\n");
        print_matrix(diff_matrix, row1, col1);
        free_matrix(diff_matrix, row1);
    }

    //A의 전치행렬
    int **transpose_matrix1 = transpose_matrix(matrix1, row1, col1);
    if (transpose_matrix1 != NULL) {
        printf("\nTranspose of matrix A:\n");
        print_matrix(transpose_matrix1, col1, row1);
        free_matrix(transpose_matrix1, col1);
    }

    //B의 전치행렬
    int **transpose_matrix2 = transpose_matrix(matrix2, row2, col2);
    if (transpose_matrix2 != NULL) {
        printf("\nTranspose of matrix B:\n");
        print_matrix(transpose_matrix2, col2, row2);
        free_matrix(transpose_matrix2, col2);
    }

    //A × B
    if (col1 != row2) {  //행렬의 곱셈이 불가능 할 때는 불가능 출력
        printf("\nCannot multiply\n");
    } 
    else {
        int **product_matrix = multiply_matrix(matrix1, row1, col1, matrix2, row2, col2);
        if (product_matrix != NULL) {
            printf("\nA * B:\n");
            print_matrix(product_matrix, row1, col2);
            free_matrix(product_matrix, row1);
        }
    }

    //할당된 메모리를 해제
    free_matrix(matrix1, row1);
    free_matrix(matrix2, row2);

    return 0;
    }


//행렬 출력 함수
void print_matrix(int **matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", matrix[i][j]);  //이차원 배열에 저장된 행렬을 출력
        }
        printf("\n");
    }
}

// 행렬 덧셈 함수
int **addition_matrix(int **matrix1, int row1, int col1, int **matrix2, int row2, int col2) {
    if (row1 != row2 || col1 != col2) {
        printf("\nCannot add\n");  //덧셈 불가능 시 출력
        return NULL;
    }

    int **sum_matrix = (int **)malloc(row1 * sizeof(int *));  //동적 메모리 할당
    for (int i = 0; i < row1; i++) {
        sum_matrix[i] = (int *)malloc(col1 * sizeof(int));  //동적 메모리 할당
        for (int j = 0; j < col1; j++) {
            sum_matrix[i][j] = matrix1[i][j] + matrix2[i][j]; 
        }
    }
    return sum_matrix;
}

// 행렬 뺄셈 함수
int **subtraction_matrix(int **matrix1, int row1, int col1, int **matrix2, int row2, int col2) {
    if (row1 != row2 || col1 != col2) {
        printf("\nCannot subtract\n");  //뺄셈 불가능 시 출력
        return NULL;
    }
    int **diff_matrix = (int **)malloc(row1 * sizeof(int *));  //동적 메모리 할당
    for (int i = 0; i < row1; i++) {
        diff_matrix[i] = (int *)malloc(col1 * sizeof(int));  //동적 메모리 할당
        for (int j = 0; j < col1; j++) {
            diff_matrix[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return diff_matrix;
}

// 행렬의 전치행렬 함수
int **transpose_matrix(int **matrix, int row, int col) {
    int **transpose_matrix = (int **)malloc(col * sizeof(int *));  //동적 메모리 할당
    for (int i = 0; i < col; i++) {
        transpose_matrix[i] = (int *)malloc(row * sizeof(int));  //동적 메모리 할당
        for (int j = 0; j < row; j++) {
            transpose_matrix[i][j] = matrix[j][i];  //전치 과정
        }
    }
    return transpose_matrix;
}

// 행렬 곱셈 함수
int **multiply_matrix(int **matrix1, int row1, int col1, int **matrix2, int row2, int col2) {
    int **product_matrix = (int **)malloc(row1 * sizeof(int *));  //동적 메모리 할당
    for (int i = 0; i < row1; i++) {
        product_matrix[i] = (int *)malloc(col2 * sizeof(int));  //동적 메모리 할당
        for (int j = 0; j < col2; j++) {
            product_matrix[i][j] = 0;
            for (int k = 0; k < col1; k++) {
                product_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return product_matrix;
}

// 동적 메모리 할당 해제 함수
void free_matrix(int **matrix, int row) {
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
}