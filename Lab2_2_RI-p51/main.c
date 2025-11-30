#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функція, яку інтегруємо: f(x) = x * sin²(x)
double f(double x) {
    return x * pow(sin(x), 2);
}

// Метод лівих прямокутників
double integral_left(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (unsigned int i = 0; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}

// Метод правих прямокутників
double integral_right(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (unsigned int i = 1; i <= n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}

// Метод трапецій
double integral_trapezoid(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;

    for (unsigned int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}

// Метод Сімпсона (парабол)
double integral_simpson(double a, double b, unsigned int n) {
    if (n % 2 != 0) n++; // Переконуємося, що n парне

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (unsigned int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            sum += 2.0 * f(x);
        } else {
            sum += 4.0 * f(x);
        }
    }

    return sum * h / 3.0;
}

int main() {
    double a, b, eps;
    unsigned int fixed_n[] = {10, 100, 1000, 10000};
    unsigned int N = 2;
    int choice;
    double I1, I2, delta;

    // Фіксовані межі інтегрування для варіанту №5
    a = 0.0;
    b = 1.0;

    printf("=== Calculation of integral: ∫[0,1] x·sin²(x) dx ===\n");
    printf("Integration limits: a = %.1f, b = %.1f\n", a, b);

    // Введення epsilon
    do {
        printf("Enter accuracy epsilon (0.00001 <= eps <= 0.001): ");
        scanf("%lf", &eps);
        if (eps < 0.00001 || eps > 0.001)
            printf("Error: epsilon must be in range [0.00001, 0.001]\n");
    } while (eps < 0.00001 || eps > 0.001);

    // Вибір методу
    do {
        printf("\nChoose method of calculation:\n");
        printf("  1. Left rectangles\n");
        printf("  2. Right rectangles\n");
        printf("  3. Trapezoid\n");
        printf("  4. Parabola (Simpson)\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 4)
            printf("Invalid choice. Try again.\n");
    } while (choice < 1 || choice > 4);

    // ===============================
    // Завдання 1: Розрахунок при фіксованих n
    // ===============================
    printf("\n%-25s", "Method");
    for (int i = 0; i < 4; i++) {
        printf("| n=%-8u", fixed_n[i]);
    }
    printf("\n");
    printf("-------------------------");
    for (int i = 0; i < 4; i++) {
        printf("|-----------");
    }
    printf("\n");

    switch (choice) {
        case 1:
            printf("%-25s", "Left rectangles");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf", integral_left(a, b, fixed_n[i]));
            printf("\n");
            break;

        case 2:
            printf("%-25s", "Right rectangles");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf", integral_right(a, b, fixed_n[i]));
            printf("\n");
            break;

        case 3:
            printf("%-25s", "Trapezoid");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf", integral_trapezoid(a, b, fixed_n[i]));
            printf("\n");
            break;

        case 4:
            printf("%-25s", "Parabola (Simpson)");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf", integral_simpson(a, b, fixed_n[i]));
            printf("\n");
            break;
    }

    // ===============================
    // Завдання 2: Пошук мінімального N для заданої точності
    // ===============================
    printf("\n=== Accuracy analysis ===\n");
    printf("Method: ");
    switch (choice) {
        case 1: printf("Left rectangles\n"); break;
        case 2: printf("Right rectangles\n"); break;
        case 3: printf("Trapezoid\n"); break;
        case 4: printf("Parabola (Simpson)\n"); break;
    }
    printf("Target accuracy: %.8lf\n\n", eps);

    printf("%-10s | %-15s | %-15s | %-12s\n",
           "N", "I(N)", "I(N+2)", "Delta");
    printf("-----------|-----------------|-----------------|-------------\n");

    N = 2;
    do {
        switch (choice) {
            case 1:
                I1 = integral_left(a, b, N);
                I2 = integral_left(a, b, N + 2);
                break;
            case 2:
                I1 = integral_right(a, b, N);
                I2 = integral_right(a, b, N + 2);
                break;
            case 3:
                I1 = integral_trapezoid(a, b, N);
                I2 = integral_trapezoid(a, b, N + 2);
                break;
            case 4:
                I1 = integral_simpson(a, b, N);
                I2 = integral_simpson(a, b, N + 2);
                break;
        }

        delta = fabs(I1 - I2);
        printf("%-10u | %-15.8lf | %-15.8lf | %.8lf\n",
               N, I1, I2, delta);
        N += 2;

        // Запобігаємо нескінченному циклу
        if (N > 100000) {
            printf("Warning: Maximum iterations reached!\n");
            break;
        }
    } while (delta > eps);

    // Остаточний результат
    N -= 2;
    printf("\nMinimum N found: %u (Delta ≤ %.8lf)\n", N, eps);

    // Обчислюємо остаточне значення інтегралу при цьому N
    double final_result;
    switch (choice) {
        case 1: final_result = integral_left(a, b, N); break;
        case 2: final_result = integral_right(a, b, N); break;
        case 3: final_result = integral_trapezoid(a, b, N); break;
        case 4: final_result = integral_simpson(a, b, N); break;
    }
    printf("Final integral value at N=%u: %.10lf\n", N, final_result);

    // Теоретичне значення для порівняння
    printf("\nFor comparison:\n");
    printf("Analytical solution: ∫[0,1] x·sin²(x) dx ≈ 0.272675\n");

    printf("\n");
    system("pause");
    return 0;
}
