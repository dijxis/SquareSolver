#include <stdio.h>
#include <TXlib.h>
#include <math.h>

enum n_roots {INF_ROOT, NO_ROOTS, ONE_ROOT, TWO_ROOTS};
const double EPSILON = 1e-9;

struct test {
        double a, b, c;
        n_roots count_roots;
        double x1, x2;
};

n_roots solve_equation(double a, double b, double c,
                       double* x1, double* x2);
n_roots solve_linear(double b, double c,
                     double* x);
n_roots solve_square(double a, double b, double c,
                     double* x1, double* x2);
void print_roots(n_roots count_roots,
                 double x1, double x2);
bool is_near_the_zero(double a);
int test_solve_equation();
int one_test(test current_test);

int main()
{
    if (test_solve_equation() == 0)
        printf("Тестирование функции solve_equation прошло успешно\n");
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

int test_solve_equation()
{
    int count_failed_tests = 0;
    test tests[] =
    {
        0, 0, 0, INF_ROOT, 0, 0,
        0, 0, 1, NO_ROOTS, 0, 0,
        0, 1, 0, ONE_ROOT, 0, 0,
        1, 4, 4, ONE_ROOT, -2, -2,
        1, 3, 2, TWO_ROOTS, -1, -2,
        1, 2, 1, ONE_ROOT, -1, -1,
        1, 2, 0, TWO_ROOTS, 0, -2,
        1, 1, 0, TWO_ROOTS, 0, -1,
        1, 0, 0, ONE_ROOT, 0, 0,
        1, 1, -2, TWO_ROOTS, 1, -2,
        1, 0, -1, TWO_ROOTS, 1, -1,
        1, -1, 0, TWO_ROOTS, 1, 0,
        1, -2, 1, ONE_ROOT, 1, 1,
        1, 0, -4, TWO_ROOTS, 2, -2,
        1, -1, -2, TWO_ROOTS, 2, -1,
        1, -2, 0, TWO_ROOTS, 2, 0,
        1, -3, 2, TWO_ROOTS, 2, 1,
        1, -4, 4, ONE_ROOT, 2, 2,
    };
    int count_tests = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < count_tests; i++)
    {
        count_failed_tests += one_test(tests[i]);
    }
    return count_failed_tests;
}

int one_test(test current_test)
{
    double x1 = 0, x2 = 0;
    n_roots count_roots = solve_equation(current_test.a, current_test.b, current_test.c, &x1, &x2);
    if (!(count_roots == current_test.count_roots &&
            is_near_the_zero(x1 - current_test.x1) &&
            is_near_the_zero(x2 - current_test.x2)))
    {
        printf("FAILED: a = %lg, b = %lg, c = %lg, count_roots = %d, x1 = %lg, x2 = %lg "
               "(should be count_roots = %d, x1 = %lg, x2 = %lg)\n",
                current_test.a, current_test.b, current_test.c, count_roots, x1, x2,
                current_test.count_roots, current_test.x1, current_test.x2);
        return 1;
    }
    return 0;
}
