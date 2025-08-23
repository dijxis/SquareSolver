#include <stdio.h>
#include <TXlib.h>
#include <math.h>

enum n_roots {INF_ROOT, NO_ROOTS, ONE_ROOT, TWO_ROOTS};
const double EPSILON = 1e-9;

n_roots solve_equation(double a, double b, double c,
                       double* x1, double* x2);
n_roots solve_linear(double b, double c,
                     double* x);
n_roots solve_square(double a, double b, double c,
                     double* x1, double* x2);
void print_roots(n_roots count_roots,
                 double x1, double x2);
bool is_near_the_zero(double a);

int main()
{
    double a = 0, b = 0, c = 0;
    printf("Введите коэффициенты уравнения ax^2 + bx + c = 0\n"
           "a, b, c: ");
    scanf("%lg %lg %lg", &a, &b, &c);

    double x1 = 0, x2 = 0;
    n_roots count_roots = solve_equation(a, b, c, &x1, &x2);

    print_roots(count_roots, x1, x2);
    return 0;
}

n_roots solve_equation(double a, double b, double c,
                       double* x1, double* x2)
{
    if (is_near_the_zero(a))
    {
        return solve_linear(b, c, x1);
    }
    else
    {
        return solve_square(a, b, c, x1, x2);
    }
}

n_roots solve_square(double a, double b, double c,
                     double* x1, double* x2)
{
    double discriminant = b*b - 4*a*c;
    if (discriminant > EPSILON)
    {
        *x1 = (-b + sqrt(discriminant)) / (2 * a);
        *x2 = (-b - sqrt(discriminant)) / (2 * a);
        return TWO_ROOTS;
    }
    else if (is_near_the_zero(discriminant))
    {
        *x1 = *x2 = -b / (2 * a);
        return ONE_ROOT;
    }
    else
    {
        return NO_ROOTS;
    }
}

n_roots solve_linear(double b, double c,
                     double* x)
{
    if (is_near_the_zero(b))
    {
        if (is_near_the_zero(c))
            return INF_ROOT;
        else
            return NO_ROOTS;
    }
    else
    {
        *x = -c / b;
        return ONE_ROOT;
    }
}

void print_roots(n_roots count_roots,
                 double x1, double x2)
{
    switch (count_roots)
    {
        case ONE_ROOT:
            printf("x = %lg", x1);
            break;
        case TWO_ROOTS:
            printf("x1 = %lg\n", x1);
            printf("x2 = %lg", x2);
            break;
        case NO_ROOTS:
            printf("Нет корней");
            break;
        case INF_ROOT:
            printf("Любое число");
            break;
        default:
            printf("count_roots = %d", count_roots);
            break;
    }
}

bool is_near_the_zero(double a)
{
    return fabs(a) <= EPSILON;
}
