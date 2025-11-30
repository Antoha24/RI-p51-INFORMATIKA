#include <stdio.h>
#include <stdlib.h>
#include "matrix_funcs.h"

/* ---------------- РЕАЛІЗАЦІЯ ---------------- */

int ** alloc_matrix(int n, int m) {
    if (n <= 0 || m <= 0) return NULL;
    /* Виділимо масив вказівників + один суцільний блок для даних для локальної компактності */
    int **A = (int **)malloc(n * sizeof(int *));
    if (!A) return NULL;
    int *data = (int *)malloc(n * m * sizeof(int));
    if (!data) { free(A); return NULL; }
    for (int i = 0; i < n; ++i) A[i] = data + i * m;
    return A;
}

void free_matrix(int **A) {
    if (!A) return;
    /* data починається в A[0] */
    free(A[0]);
    free(A);
}

void init_matrix_input(int **A, int n, int m) {
    if (!A) return;
    printf("Введіть елементи матриці пострічково (всього %d елементів):\n", n * m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &A[i][j]);
}

void init_matrix_random(int **A, int n, int m, int minv, int maxv) {
    if (!A) return;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            A[i][j] = minv + rand() % (maxv - minv + 1);
}

void print_matrix(int **A, int n, int m, const char *name) {
    if (!A) return;
    printf("\nMatrix %s (%dx%d):\n", name ? name : "A", n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%8d", A[i][j]);
        }
        printf("\n");
    }
}

void print_array(int *A, int n) {
    if (!A) return;
    printf("\Array:\n");
    for (int j = 0; j < n; ++j) {
        printf("%8d", A[j]);
    }
    printf("\n");
}

/* Пошук max/min вище/нижче головної діагоналі */
int find_max_min_diagonal_side(int **A, int n, int variant, int *out_max, int *out_min) {
    if (!A || n <= 0) return -1;
    int found = 0;
    int maxv = 0, minv = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int consider = 0;
            if (variant % 2 == 0) { /* парний варіант => нижче головної діагоналі i>j */
                if (i > j) consider = 1;
            } else { /* непарний => вище головної діагоналі i<j */
                if (i < j) consider = 1;
            }
            if (!consider) continue;
            if (!found) {
                maxv = minv = A[i][j];
                found = 1;
            } else {
                if (A[i][j] > maxv) maxv = A[i][j];
                if (A[i][j] < minv) minv = A[i][j];
            }
        }
    }
    if (!found) return -1;
    if (out_max) *out_max = maxv;
    if (out_min) *out_min = minv;
    return 0;
}

/* Транспонування — повертає нову матрицю */
int ** transpose(int **B, int n, int m) {
    if (!B || n <= 0 || m <= 0) return NULL;
    int **T = alloc_matrix(m, n);
    if (!T) return NULL;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            T[j][i] = B[i][j];
    return T;
}

/* Множення матриць A(n_a x m_a) * B(n_b x m_b) */
int ** multiply_matrices(int **A, int n_a, int m_a, int **B, int n_b, int m_b) {
    if (!A || !B) return NULL;
    if (m_a != n_b) return NULL;
    int **C = alloc_matrix(n_a, m_b);
    if (!C) return NULL;
    for (int i = 0; i < n_a; ++i) {
        for (int j = 0; j < m_b; ++j) {
            long long sum = 0;
            for (int k = 0; k < m_a; ++k) sum += (long long)A[i][k] * (long long)B[k][j];
            C[i][j] = (int)sum; /* в лабораторних припускаємо що int вміщає результат */
        }
    }
    return C;
}

/* Псевдо-сортування через flatten + qsort (stable enough) */
static int cmp_int_asc(const void *pa, const void *pb) {
    int a = *(const int *)pa;
    int b = *(const int *)pb;
    return (a > b) - (a < b);
}
void sort_matrix_all(int **A, int n, int m) {
    if (!A) return;
    int total = n * m;
    int *buf = (int *)malloc(total * sizeof(int));
    if (!buf) return;
    int idx = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            buf[idx++] = A[i][j];
    qsort(buf, total, sizeof(int), cmp_int_asc);
    idx = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            A[i][j] = buf[idx++];
    free(buf);
}

int sort_matrix_row(int **A, int n, int m, int row_index) {
    if (!A) return -1;
    if (row_index < 0 || row_index >= n) return -1;
    qsort(A[row_index], m, sizeof(int), cmp_int_asc);
    return 0;
}

void sum_rows(int **A, int n, int m) {
    if (!A) return;
    printf("\nSums of rows (A):\n");
    for (int i = 0; i < n; ++i) {
        long long s = 0;
        for (int j = 0; j < m; ++j) s += A[i][j];
        printf("Row %d: %lld\n", i, s);
    }
}

void sum_columns(int **B, int n, int m) {
    if (!B) return;
    printf("\nSums of columns (B):\n");
    for (int j = 0; j < m; ++j) {
        long long s = 0;
        for (int i = 0; i < n; ++i) s += B[i][j];
        printf("Col %d: %lld\n", j, s);
    }
}

static void swap_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}