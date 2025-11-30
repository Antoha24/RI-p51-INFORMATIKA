#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "methods_header.h"
#include "methods_impl.c"

int main() {
    double a, b, eps;
    int max_iter, choice, debug;
    clock_t start, end;
    double root;

    printf("=== Розв'язання нелінійного рівняння ===\n");
    printf("Приклад: f(x) = x^3 - x - 2\n\n");

    printf("Введіть ліву межу інтервалу a: ");
    scanf("%lf", &a);
    printf("Введіть праву межу інтервалу b: ");
    scanf("%lf", &b);
    printf("Введіть похибку ε: ");
    scanf("%lf", &eps);
    printf("Введіть максимальну кількість ітерацій: ");
    scanf("%d", &max_iter);

    printf("Увімкнути режим налагодження (1 - так, 0 - ні)? ");
    scanf("%d", &debug);

    if (func(a) * func(b) >= 0) {
        printf("\n(!) На проміжку [%.2lf, %.2lf] немає зміни знаку або їх декілька!\n", a, b);
        return 1;
    }

    printf("\nОберіть метод:\n");
    printf("1 - Метод половинного ділення\n");
    printf("2 - Метод хорд\n");
    printf("Ваш вибір: ");
    scanf("%d", &choice);

    start = clock();

    switch (choice) {
        case 1:
            root = bisection(a, b, eps, max_iter, debug);
            break;
        case 2:
            root = chord(a, b, eps, max_iter, debug);
            break;
        default:
            printf("Невірний вибір!\n");
            return 1;
    }

    end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nЧас виконання: %.6lf секунд\n", time_spent);
    printf("Значення функції у корені f(x)=%.8lf\n", func(root));

    return 0;
}
