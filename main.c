#include <stdio.h>
#include <TXlib.h>
#include <math.h>

enum N_roots
{
    INF_ROOT = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};
const double EPSILON = 1e-9;

struct Test
{
        double a, b, c;
        N_roots count_roots;
        double x1, x2;
};

N_roots solve_equation(double a, double b, double c,
                       double* x1, double* x2);
N_roots solve_linear(double b, double c,
                     double* x);
N_roots solve_square(double a, double b, double c,
                     double* x1, double* x2);
void print_roots(N_roots count_roots,
                 double x1, double x2);
bool equal(double a, double b);
int test_solve_equation();
int one_test(Test current_test);
void sort_roots(double* x1, double* x2);
bool is_correct_roots(Test test, N_roots count_roots, double x1, double x2);

int main()
{
    if (test_solve_equation() == 0)
        printf("Тестирование функции solve_equation прошло успешно\n");

    double a = 0, b = 0, c = 0;
    printf("Введите коэффициенты уравнения ax^2 + bx + c = 0\n"
           "a, b, c: ");
    scanf("%lg %lg %lg", &a, &b, &c);

    double x1 = NAN, x2 = NAN;
    N_roots count_roots = solve_equation(a, b, c, &x1, &x2);

    print_roots(count_roots, x1, x2);
    return 0;
}

N_roots solve_equation(double a, double b, double c,
                       double* x1, double* x2)
{
    if (equal(a, 0))
    {
        return solve_linear(b, c, x1);
    }
    else
    {
        return solve_square(a, b, c, x1, x2);
    }
}

N_roots solve_square(double a, double b, double c,
                     double* x1, double* x2)
{
    double discriminant = b*b - 4*a*c;
    if (discriminant > EPSILON)
    {
        *x1 = (-b + sqrt(discriminant)) / (2 * a);
        *x2 = (-b - sqrt(discriminant)) / (2 * a);
        return TWO_ROOTS;
    }
    else if (equal(discriminant, 0))
    {
        *x1 = *x2 = -b / (2 * a);
        return ONE_ROOT;
    }
    else
    {
        return NO_ROOTS;
    }
}

N_roots solve_linear(double b, double c,
                     double* x)
{
    if (equal(b, 0))
    {
        if (equal(c, 0))
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

void print_roots(N_roots count_roots,
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

bool equal(double a, double b)
{
    if (isnan(a) && isnan(b))
        return 1;
    if (isnan(a) || isnan(b))
        return 0;
    return fabs(a - b) <= EPSILON;
}

int test_solve_equation()
{
    int count_failed_tests = 0;
    Test tests[] =
    {
        {0, 0, 0, INF_ROOT, NAN, NAN}, // TODO: из файла
        {0, 0, 1, NO_ROOTS, NAN, NAN},
        {0, 1, 0, ONE_ROOT, 0, 0},
        {1, 4, 4, ONE_ROOT, -2, -2},
        {1, 3, 2, TWO_ROOTS, -1, -2},
        {1, 3, 2, TWO_ROOTS, -2, -1}
    };
    int count_tests = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < count_tests; i++)
    {
        count_failed_tests += one_test(tests[i]);
    }
    return count_failed_tests;
}

int one_test(Test current_test)
{
    double x1 = NAN, x2 = NAN; // TODO: NAN
    N_roots count_roots = solve_equation(current_test.a, current_test.b, current_test.c, &x1, &x2);
    sort_roots(&x1, &x2);
    sort_roots(&current_test.x1, &current_test.x2);
    if (!is_correct_roots(current_test, count_roots, x1, x2)) // TODO: корни в другом порядке
    {
        printf("FAILED: a = %lg, b = %lg, c = %lg, count_roots = %d, x1 = %lg, x2 = %lg "
               "(should be count_roots = %d, x1 = %lg, x2 = %lg)\n",
                current_test.a, current_test.b, current_test.c, count_roots, x1, x2,
                current_test.count_roots, current_test.x1, current_test.x2);
        return 1;
    }
    return 0;
}

void sort_roots(double* x1, double* x2) // x1 = min(x1, x2), x2 = max(x1, x2), NAN > any num
{
    if (isnan(*x1) && !isnan(*x2))
    {
        *x1 = *x2;
        *x2 = NAN;
    }
    else if (!isnan(*x1) && !isnan(*x2) && *x1 > *x2)
    {
        double temp = *x1;
        *x1 = *x2;
        *x2 = temp;
    }
}

bool is_correct_roots(Test test, N_roots count_roots, double x1, double x2)
{
    if (test.count_roots != count_roots)
        return 0;
    switch (count_roots)
    {
        case ONE_ROOT:
            return equal(x1, test.x1);
        case TWO_ROOTS:
            return equal(x1, test.x1) && equal(x2, test.x2);
        default:
            return 1;
    }
}
