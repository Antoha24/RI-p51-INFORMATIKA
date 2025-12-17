#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"

int main() {

    char input_name[128];
    char output_text_name[128];
    char output_bin_name[128];

    double X1, X2, delta;
    unsigned int N;

    char group[64];
    char student[128];

    printf("Enter input filename: ");
    scanf("%127s", input_name);

    if (read_input_file(input_name, &X1, &X2, &N, &delta, group, student) != 0) {
        printf("Error reading input file.\n");
        return 1;
    }

    /* Визначаємо N або delta */
    if (N == 0 && delta > 0) {
        N = (unsigned int)((X2 - X1) / delta) + 1;
    } else if (N > 1 && delta == 0) {
        delta = (X2 - X1) / (N - 1);
    } else if (N == 0 && delta == 0) {
        printf("Error: either N or delta must be non-zero.\n");
        return 1;
    }

    /* Виділення пам'яті */
    double *xs = (double*)malloc(N * sizeof(double));
    double *ys = (double*)malloc(N * sizeof(double));

    if (!xs || !ys) {
        printf("Memory allocation error.\n");
        free(xs);
        free(ys);
        return 1;
    }

    /* Заповнення таблиці */
    for (unsigned int i = 0; i < N; i++) {
        xs[i] = X1 + i * delta;
        if (i == N - 1) xs[i] = X2;
        ys[i] = f(xs[i]);
    }

    /* Вивід на екран */
    printf("\n--- TABLE OF VALUES (first 10 rows) ---\n");
    unsigned int limit = (N < 10) ? N : 10;

    for (unsigned int i = 0; i < limit; i++) {
        printf("%3u | x = %12.6f | f(x) = %12.6f\n",
               i + 1, xs[i], ys[i]);
    }

    /* Запис у текстовий файл */
    printf("\nEnter output text filename: ");
    scanf("%127s", output_text_name);

    if (save_text(output_text_name, xs, ys, N, X1, X2, delta, group, student) == 0) {
        printf("Text file saved.\n");
    } else {
        printf("Error saving text file.\n");
    }

    /* Запис у бінарний файл */
    printf("Enter output binary filename: ");
    scanf("%127s", output_bin_name);

    if (save_binary(output_bin_name, xs, ys, N) == 0) {
        printf("Binary file saved.\n");
    } else {
        printf("Error saving binary file.\n");
    }

    free(xs);
    free(ys);

    printf("\nDone.\n");
    return 0;
}

