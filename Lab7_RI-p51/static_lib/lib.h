#ifndef LIB_H
#define LIB_H

/* Читання даних із вхідного файлу */
int read_input_file(const char *fname, double *x1, double *x2,
                    unsigned int *N, double *delta,
                    char *group, char *student);

/* Варіант 2 — підінтегральна функція */
double f(double x);

/* Запис у текстовий файл */
int save_text(const char *fname, double *xs, double *ys,
              unsigned int N, double x1, double x2, double delta,
              const char *group, const char *student);

/* Запис у двійковий файл */
int save_binary(const char *fname, double *xs, double *ys, unsigned int N);

#endif
