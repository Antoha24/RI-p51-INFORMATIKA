#include <stdio.h>
#include <math.h>
#include "methods_header.h"

// Твоя функція (приклад): f(x) = x^3 - x - 2
double func(double x) {
    return pow(x, 3) - x - 2;
}

// Похідна (для перевірки існування єдиного кореня)
double derivative(double x) {
    return 3 * x * x - 1;
}

// === Метод половинного ділення ===
double bisection(double a, double b, double eps, int max_iter, int debug) {
    double c;
    int iter = 0;

    if (func(a) * func(b) > 0) {
        printf("Помилка: на проміжку [%.2lf, %.2lf] немає зміни знаку!\n", a, b);
        return NAN;
    }

    do {
        c = (a + b) / 2.0; // Середина відрізка
        if (debug)
            printf("Ітерація %d: a=%.6lf, b=%.6lf, c=%.6lf, f(c)=%.6lf\n",
                   iter + 1, a, b, c, func(c));

        if (func(a) * func(c) < 0)
            b = c;
        else
            a = c;

        iter++;
        if (iter >= max_iter) {
            printf("Досягнуто максимум ітерацій (%d)\n", max_iter);
            break;
        }
    } while (fabs(func(c)) > eps && fabs(b - a) > eps);

    printf("\nРезультат методом половинного ділення:\n");
    printf("Корінь ≈ %.8lf, f(x)=%.8lf, ітерацій=%d\n", c, func(c), iter);
    return c;
}

// === Метод хорд ===
double chord(double a, double b, double eps, int max_iter, int debug) {
    double x0 = a;
    double x1 = b;
    double x2;
    int iter = 0;

    if (func(a) * func(b) > 0) {
        printf("Помилка: на проміжку [%.2lf, %.2lf] немає зміни знаку!\n", a, b);
        return NAN;
    }

    do {
        x2 = x1 - func(x1) * (x1 - x0) / (func(x1) - func(x0));

        if (debug)
            printf("Ітерація %d: x0=%.6lf, x1=%.6lf, x2=%.6lf, f(x2)=%.6lf\n",
                   iter + 1, x0, x1, x2, func(x2));

        x0 = x1;
        x1 = x2;
        iter++;

        if (iter >= max_iter) {
            printf("Досягнуто максимум ітерацій (%d)\n", max_iter);
            break;
        }
    } while (fabs(func(x2)) > eps);

    printf("\nРезультат методом хорд:\n");
    printf("Корінь ≈ %.8lf, f(x)=%.8lf, ітерацій=%d\n", x2, func(x2), iter);
    return x2;
}
