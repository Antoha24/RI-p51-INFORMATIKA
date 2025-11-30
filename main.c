#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    double x, y;

    printf("Enter x: ");
    scanf("%lf", &x);

    // Визначення значення функції за умовами варіанту №5
    if (x >= -20 && x < -10) {
        // y = 2^|x|
        y = pow(2.0, fabs(x));
    }
    else if (x >= -2 && x < 2) {
        // y = |sin(x)| / (cos(x) + 2)
        y = fabs(sin(x)) / (cos(x) + 2.0);
    }
    else if (x >= 5 && x < 10) {
        // y = 2x + sqrt(x^2 - 4)
        y = 2.0 * x + sqrt(pow(x, 2.0) - 4.0);
    }
    else {
        // y = x/5 + (x-1)/2 - для всіх інших значень x
        y = (x / 5.0) + ((x - 1.0) / 2.0);
    }

    printf("x = %.6lf", x);
    printf("\ny = %.6lf", y);

    printf("\n");
    system("pause");
    return 0;
}
