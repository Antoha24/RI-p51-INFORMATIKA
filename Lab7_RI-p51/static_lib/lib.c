#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib.h"

/* Читання даних із вхідного файлу */
int read_input_file(const char *fname, double *x1, double *x2,
                    unsigned int *N, double *delta,
                    char *group, char *student)
{
    FILE *f = fopen(fname, "r");
    if (!f) return -1;

    char buf[256];

    fgets(buf, sizeof(buf), f);
    *x1 = atof(buf);

    fgets(buf, sizeof(buf), f);
    *x2 = atof(buf);

    fgets(buf, sizeof(buf), f);
    *N = (unsigned int)atoi(buf);

    fgets(buf, sizeof(buf), f);
    *delta = atof(buf);

    fgets(buf, sizeof(buf), f);
    buf[strcspn(buf, "\n")] = 0;
    strcpy(group, buf);

    fgets(buf, sizeof(buf), f);
    buf[strcspn(buf, "\n")] = 0;
    strcpy(student, buf);

    fclose(f);
    return 0;
}

/* Варіант 2: f(x) = 0.25*x^5 + 4*(x+20)^4 - 2x */
double f(double x) {
    return 0.25 * pow(x, 5)
         + 4.0 * pow(x + 20.0, 4)
         - 2.0 * x;
}

/* Запис у текстовий файл */
int save_text(const char *fname, double *xs, double *ys,
              unsigned int N, double x1, double x2, double delta,
              const char *group, const char *student)
{
    FILE *f = fopen(fname, "w");
    if (!f) return -1;

    fprintf(f, "X1 = %.6f\n", x1);
    fprintf(f, "X2 = %.6f\n", x2);
    fprintf(f, "N  = %u\n", N);
    fprintf(f, "delta = %.6f\n\n", delta);

    fprintf(f, "   i        x               f(x)\n");
    fprintf(f, "----------------------------------------\n");

    for (unsigned int i = 0; i < N; i++) {
        fprintf(f, "%4u   %12.6f   %12.6f\n", i + 1, xs[i], ys[i]);
    }

    fprintf(f, "\n%s\n", group);
    fprintf(f, "%s\n", student);

    fclose(f);
    return 0;
}

/* Запис у двійковий файл */
int save_binary(const char *fname, double *xs, double *ys, unsigned int N) {
    FILE *f = fopen(fname, "wb");
    if (!f) return -1;

    fwrite(&N, sizeof(unsigned int), 1, f);

    for (unsigned int i = 0; i < N; i++) {
        fwrite(&xs[i], sizeof(double), 1, f);
        fwrite(&ys[i], sizeof(double), 1, f);
    }

    fclose(f);
    return 0;
}
