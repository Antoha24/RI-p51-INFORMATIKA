#ifndef MATRIX_FUNCS_H
#define MATRIX_FUNCS_H

/* ---------------- ПРОТОТИПИ (header-like) ---------------- */

/* Виділити пам'ять для матриці n x m (матриця як double pointer) */
int ** alloc_matrix(int n, int m);

/* Звільнити пам'ять матриці, виділену alloc_matrix */
void free_matrix(int **A);

/* Ініціалізація матриці: 0 - введення вручну, 1 - випадкові числа у діапазоні [minv,maxv] */
void init_matrix_input(int **A, int n, int m);
void init_matrix_random(int **A, int n, int m, int minv, int maxv);

/* Друк матриці */
void print_matrix(int **A, int n, int m, const char *name);

void print_array(int *A, int n);

/* Знайти max та min для частини матриці:
   якщо variant парний -> шукаємо для елементів нижче головної діагоналі (i>j)
   якщо variant непарний -> шукаємо для елементів вище головної діагоналі (i<j)
   повертає 0 якщо знайдено елементи, -1 якщо таких елементів немає (наприклад n=1) */
int find_max_min_diagonal_side(int **A, int n, int variant, int *out_max, int *out_min);

/* Транспонування: повертає нову матрицю m x n (не змінює вхідну) */
int ** transpose(int **B, int n, int m);

/* Множення матриць: C = A(n_a x m_a) * B(n_b x m_b)
   Повертає pointer на нову матрицю або NULL якщо розміри не сумісні */
int ** multiply_matrices(int **A, int n_a, int m_a, int **B, int n_b, int m_b);

/* Сортування усіх елементів матриці A за зростанням (впливає на матрицю) */
void sort_matrix_all(int **A, int n, int m);

/* Сортування елементів лише в межах одного рядка (0-based index row) */
int sort_matrix_row(int **A, int n, int m, int row_index);

/* Сума елементів рядків матриці A (виводить n сум) */
void sum_rows(int **A, int n, int m);

/* Сума елементів стовпців матриці B (виводить m сум) */
void sum_columns(int **B, int n, int m);

/* Допоміжні */
static void swap_int(int *a, int *b);

#endif