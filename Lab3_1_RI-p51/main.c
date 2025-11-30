#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double calculate_function(double x);       // Обчислення f(x)
double calculate_derivative(double x);     // Обчислення f'(x)
void print_table_with_points(double start_x, double end_x, int num_points);
void print_table_with_step(double start_x, double end_x, double step);
void print_table_header();                 // Друк заголовка таблиці
void print_table_row(double x);            // Друк одного рядка таблиці


int main() {
    int choice;
    double x1, x2;
    double step;
    int points_count;

    // Простий заголовок без спецсимволів
    printf("=================================================\n");
    printf("    PROGRAM FOR CALCULATING FUNCTION AND DERIVATIVE\n");
    printf("            f(x) = 2x^3 - 0.2x^2 + 0.5x + 3\n");
    printf("=================================================\n\n");

    while(1) {
        // Просте меню без спецсимволів
        printf("\n---------------- SELECT MODE ----------------\n");
        printf("1 - Enter start, end and number of points\n");
        printf("2 - Enter start, end and step size\n");
        printf("0 - Exit program\n");
        printf("---------------------------------------------\n");
        printf("Your choice: ");

        scanf("%d", &choice);

        if (choice == 0) {
            printf("\n>>> Program finished. Goodbye!\n");
            break;
        }

        switch(choice) {
            case 1: {
                printf("\n--- MODE 1: By number of points ---\n");

                printf("Enter start X: ");
                scanf("%lf", &x1);
                printf("Enter end X: ");
                scanf("%lf", &x2);
                printf("Enter number of points: ");
                scanf("%d", &points_count);

                if (x2 <= x1) {
                    printf("\nERROR: End X must be greater than start X!\n\n");
                    break;
                }
                if (points_count <= 1) {
                    printf("\nERROR: Number of points must be at least 2!\n\n");
                    break;
                }

                printf("\nData accepted: X1=%.2f, X2=%.2f, Points=%d\n", x1, x2, points_count);
                print_table_with_points(x1, x2, points_count);
                break;
            }

            case 2: {
                printf("\n--- MODE 2: By step size ---\n");

                printf("Enter start X: ");
                scanf("%lf", &x1);
                printf("Enter end X: ");
                scanf("%lf", &x2);
                printf("Enter step size: ");
                scanf("%lf", &step);

                if (x2 <= x1) {
                    printf("\nERROR: End X must be greater than start X!\n\n");
                    break;
                }
                if (step <= 0) {
                    printf("\nERROR: Step size must be positive!\n\n");
                    break;
                }

                printf("\nData accepted: X1=%.2f, X2=%.2f, Step=%.4f\n", x1, x2, step);
                print_table_with_step(x1, x2, step);
                break;
            }

            default: {
                printf("\nERROR: Invalid choice! Please select 0, 1, or 2.\n\n");
                break;
            }
        }
    }

    return 0;
}



double calculate_function(double x) {
    return 2.0 * pow(x, 3) - 0.2 * pow(x, 2) + 0.5 * x + 3.0;
}

double calculate_derivative(double x) {
    return 6.0 * pow(x, 2) - 0.4 * x + 0.5;
}


void print_table_with_points(double start_x, double end_x, int num_points) {
    double step = (end_x - start_x) / (num_points - 1);

    printf("\nCALCULATING TABLE:\n");
    printf("  Calculated step: %.6f\n", step);
    printf("  Number of points: %d\n\n", num_points);

    print_table_header();

    for (int i = 0; i < num_points; i++) {
        double current_x = start_x + i * step;
        print_table_row(current_x);
    }

    printf("-------------------------------------------------\n");
    printf("Table completed! %d points printed.\n\n", num_points);
}

void print_table_with_step(double start_x, double end_x, double step) {
    int points_count = 0;

    printf("\nCALCULATING TABLE:\n");
    printf("  Step size: %.6f\n\n", step);

    print_table_header();

    for (double current_x = start_x; current_x <= end_x; current_x += step) {
        print_table_row(current_x);
        points_count++;
    }

    printf("-------------------------------------------------\n");
    printf("Table completed! %d points printed.\n\n", points_count);
}

void print_table_header() {
    printf("-------------------------------------------------\n");
    printf("      x      |     f(x)      |     f'(x)     \n");
    printf("-------------------------------------------------\n");
}

void print_table_row(double x) {
    double function_value = calculate_function(x);
    double derivative_value = calculate_derivative(x);

    printf(" %10.4f  | %13.6f | %13.6f \n", x, function_value, derivative_value);
}
