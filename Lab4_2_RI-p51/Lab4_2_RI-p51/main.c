/* lab4_part2.c
   ЛР4 Частина 2 — робота з динамічними двовимірними масивами
   - виділення/звільнення пам'яті для int**
   - ініціалізація (ввід/рандом)
   - друк
   - max/min для частини матриці (залежно від парності)
   - транспонування
   - множення матриць A x B
   - сортування усіх елементів матриці або одного рядка
   - суми рядків (A) та стовпців (B)
   - текстове меню
   Вимоги: ніяких глобальних масивів/глобальних змінних.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "matrix_funcs.h"
#include "matrix_funcs.c"

/* ---------------- ТЕКСТОВИЙ ІНТЕРФЕЙС ---------------- */

static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {

    int n = 5;
    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    print_array(arr, n);




    srand((unsigned)time(NULL));
    int **A = NULL, **B = NULL, **C = NULL;
    int nA = 0, mA = 0, nB = 0, mB = 0;

    while (1) {
        printf("\n===== MENU: Lab4 Part2 =====\n");
        printf("1) Create/Init matrices A and B\n");
        printf("2) Print matrices\n");
        printf("3) Find max/min (above or below diag depending on variant parity)\n");
        printf("4) Transpose matrix B\n");
        printf("5) Multiply C = A x B\n");
        printf("6) Sort matrix A (all elements) or sort a single row\n");
        printf("7) Sums: rows(A) and columns(B)\n");
        printf("8) Free matrices\n");
        printf("9) Exit\n");
        printf("Choose option: ");
        int opt;
        if (scanf("%d", &opt) != 1) { printf("Bad input\n"); break; }

        if (opt == 1) {
            /* створення A */
            if (A) { free_matrix(A); A = NULL; }
            if (B) { free_matrix(B); B = NULL; }
            printf("Enter dimensions for matrix A (n m): ");
            scanf("%d %d", &nA, &mA);
            A = alloc_matrix(nA, mA);
            if (!A) { printf("Allocation failed for A\n"); continue; }
            printf("Init A: 1-manual 2-random? ");
            int t; scanf("%d", &t);
            if (t == 1) {
                init_matrix_input(A, nA, mA);
            } else {
                int mn, mx;
                printf("Enter random range min max: "); scanf("%d %d", &mn, &mx);
                init_matrix_random(A, nA, mA, mn, mx);
            }

            /* створення B */
            printf("Enter dimensions for matrix B (n m): ");
            scanf("%d %d", &nB, &mB);
            B = alloc_matrix(nB, mB);
            if (!B) { printf("Allocation failed for B\n"); continue; }
            printf("Init B: 1-manual 2-random? ");
            int tb; scanf("%d", &tb);
            if (tb == 1) {
                init_matrix_input(B, nB, mB);
            } else {
                int mn, mx;
                printf("Enter random range min max: "); scanf("%d %d", &mn, &mx);
                init_matrix_random(B, nB, mB, mn, mx);
            }

            printf("Matrices created and initialized. They will be printed on request.\n");
        }
        else if (opt == 2) {
            if (A) print_matrix(A, nA, mA, "A"); else printf("Matrix A not created\n");
            if (B) print_matrix(B, nB, mB, "B"); else printf("Matrix B not created\n");
            if (C) print_matrix(C, (C? (/*we cannot know dims here*/ 0):0), 0, "C"); /* placeholder */
        }
        else if (opt == 3) {
            if (!A) { printf("Create matrix A first\n"); continue; }
            printf("Enter variant number (integer) to determine parity: ");
            int var; scanf("%d", &var);
            int maxv, minv;
            int rc = find_max_min_diagonal_side(A, nA, var, &maxv, &minv);
            if (rc == 0) {
                if (var % 2 == 0)
                    printf("Variant %d (even) => search below main diagonal (i>j)\n", var);
                else
                    printf("Variant %d (odd) => search above main diagonal (i<j)\n", var);
                printf("Max = %d, Min = %d\n", maxv, minv);
            } else {
                printf("No elements found on the requested side (maybe matrix too small)\n");
            }
        }
        else if (opt == 4) {
            if (!B) { printf("Create matrix B first\n"); continue; }
            print_matrix(B, nB, mB, "B (before transpose)");
            int **T = transpose(B, nB, mB);
            if (!T) { printf("Transpose failed\n"); continue; }
            print_matrix(T, mB, nB, "Transpose(B)");
            free_matrix(T);
        }
        else if (opt == 5) {
            if (!A || !B) { printf("Create both A and B first\n"); continue; }
            if (mA != nB) { printf("Incompatible dims: A.m=%d must equal B.n=%d\n", mA, nB); continue; }
            if (C) { free_matrix(C); C = NULL; }
            C = multiply_matrices(A, nA, mA, B, nB, mB);
            if (!C) { printf("Multiplication failed\n"); continue; }
            print_matrix(C, nA, mB, "C = A x B");
            /* звільнити C після перегляду чи лишити для подальшої роботи? залишимо до наступного виклику */
        }
        else if (opt == 6) {
            if (!A) { printf("Create matrix A first\n"); continue; }
            printf("Sort: 1) all elements  2) single row\nChoose: ");
            int s; scanf("%d", &s);
            if (s == 1) {
                print_matrix(A, nA, mA, "A (before sort all)");
                sort_matrix_all(A, nA, mA);
                print_matrix(A, nA, mA, "A (after sort all)");
            } else {
                printf("Enter row index (0..%d): ", nA - 1);
                int r; scanf("%d", &r);
                if (sort_matrix_row(A, nA, mA, r) == 0) {
                    print_matrix(A, nA, mA, "A (after row sort)");
                } else {
                    printf("Invalid row\n");
                }
            }
        }
        else if (opt == 7) {
            if (!A) printf("Matrix A not created\n"); else { print_matrix(A, nA, mA, "A"); sum_rows(A, nA, mA); }
            if (!B) printf("Matrix B not created\n"); else { print_matrix(B, nB, mB, "B"); sum_columns(B, nB, mB); }
        }
        else if (opt == 8) {
            if (A) { free_matrix(A); A = NULL; nA = mA = 0; }
            if (B) { free_matrix(B); B = NULL; nB = mB = 0; }
            if (C) { free_matrix(C); C = NULL; }
            printf("Matrices freed\n");
        }
        else if (opt == 9) {
            printf("Exiting. Freeing memory.\n");
            if (A) { free_matrix(A); A = NULL; }
            if (B) { free_matrix(B); B = NULL; }
            if (C) { free_matrix(C); C = NULL; }
            break;
        }
        else {
            printf("Unknown option\n");
        }

        /* Очистка залишків вводу */
        flush_stdin();
    }

    return 0;
}
