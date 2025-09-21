#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Нова функція f(x)
double f(double x) {
    return 0.4 * pow((x - 100), 3) + 0.3 * x * x - 0.2 * x + 200;
}

int main() {
    unsigned int variant;
    double X1, X2, delta;
    int N;

    // Вибір варіанту
    do {
        printf("Enter variant (1 or 2): ");
        if (scanf("%u", &variant) != 1) {
            while (getchar() != '\n');
            variant = 0;
        }
    } while (variant < 1 || variant > 2);

    // Введення X1
    printf("Enter X1: ");
    while (scanf("%lf", &X1) != 1) {
        printf("Incorrect value!\n");
        while (getchar() != '\n');
        printf("Enter X1: ");
    }

    // Введення X2
    printf("Enter X2: ");
    while (scanf("%lf", &X2) != 1 || X2 <= X1) {
        printf("Incorrect value! X2 must be greater than X1.\n");
        while (getchar() != '\n');
        printf("Enter X2: ");
    }

    // Обробка варіантів
    switch (variant) {
        case 1:
            printf("Enter N: ");
            while (scanf("%d", &N) != 1 || N < 2) {
                printf("Incorrect value! N must be >= 2.\n");
                while (getchar() != '\n');
                printf("Enter N: ");
            }
            delta = (X2 - X1) / (N - 1);
            break;
        case 2:
            printf("Enter delta: ");
            while (scanf("%lf", &delta) != 1 || delta <= 0 || delta > (X2 - X1)) {
                printf("Incorrect value! delta must be > 0 and <= X2 - X1.\n");
                while (getchar() != '\n');
                printf("Enter delta: ");
            }
            N = (int)((X2 - X1) / delta) + 1;
            break;
    }

    // Виведення вхідних даних
    printf("\nInitial data:\n");
    printf("X1 = %.3f\n", X1);
    printf("X2 = %.3f\n", X2);
    printf("delta = %.3f\n", delta);
    printf("N = %d\n\n", N);

    // Виведення заголовка таблиці
    printf("+-----+--------------------+-------------------------+\n");
    printf("| Pt# |         X          |          f(X)           |\n");
    printf("+-----+--------------------+-------------------------+\n");

    double prev_f = f(X1);
    int first = 1;

    for (int i = 0; i < N; i++) {
        double x = X1 + i * delta;
        if (x > X2) x = X2;
        double y = f(x);

        // Форматоване виведення значень
        printf("|%5d|%20.6f|%25.6f", i + 1, x, y);

        // Перевірка на зміну знаку
        if (!first && (prev_f * y < 0)) {
            printf(" <- Sign change!");
        }

        printf("\n");
        prev_f = y;
        first = 0;
    }

    printf("+-----+--------------------+-------------------------+\n");

    return 0;
}
