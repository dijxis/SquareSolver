#define TX_COMPILED
#include <TXlib.h>
#include <stdio.h>
#include <math.h>
#include "solver.h"


struct Test_data_equation
{
    double a, b, c;
    N_roots count_roots;
    double x1, x2;
};

void printRoots(N_roots count_roots,
                 double x1, double x2);
int testSolveEquation();
bool oneTestSolveEquation(Test_data_equation current_test);
void sortRoots(double* x1, double* x2);
bool isCorrectRoots(Test_data_equation test, N_roots count_roots, double x1, double x2);

int main()
{
    if (testSolveEquation() == 0)
        printf("Тестирование функции solve_equation прошло успешно\n");

    double a = 0, b = 0, c = 0;
    printf("Введите коэффициенты уравнения ax^2 + bx + c = 0\n"
           "a, b, c: ");
    scanf("%lg %lg %lg", &a, &b, &c);

    double x1 = NAN, x2 = NAN;
    N_roots count_roots = solveEquation(a, b, c, &x1, &x2);

    printRoots(count_roots, x1, x2);
    return 0;
}

void printRoots(N_roots count_roots,
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
        case NAN_ROOTS:
        default:
            printf("count_roots = %d", count_roots);
            break;
    }
}


int testSolveEquation()
{
    int count_failed_tests = 0;
    FILE *file = fopen("tests.txt", "r");
    int count_tests = 0;
    fscanf(file, "%d", &count_tests);
    for (int i = 0; i < count_tests; i++)
    {
        double a = NAN, b = NAN, c = NAN;
        N_roots count_roots = NAN_ROOTS;
        double x1 = NAN, x2 = NAN;
        int temp = 0;
        fscanf(file, "%lg %lg %lg %d %lg %lg", &a, &b, &c, &temp, &x1, &x2);
        count_roots = (N_roots)temp;
        Test_data_equation test = {a, b, c, count_roots, x1, x2};
        count_failed_tests += oneTestSolveEquation(test);
    }
    fclose(file);
    return count_failed_tests;
}

bool oneTestSolveEquation(Test_data_equation current_test)
{
    double x1 = NAN, x2 = NAN;
    N_roots count_roots = solveEquation(current_test.a, current_test.b, current_test.c, &x1, &x2);
    sortRoots(&x1, &x2);
    sortRoots(&current_test.x1, &current_test.x2);
    if (!isCorrectRoots(current_test, count_roots, x1, x2))
    {
        printf("FAILED: a = %lg, b = %lg, c = %lg, count_roots = %d, x1 = %lg, x2 = %lg "
               "(should be count_roots = %d, x1 = %lg, x2 = %lg)\n",
                current_test.a, current_test.b, current_test.c, count_roots, x1, x2,
                current_test.count_roots, current_test.x1, current_test.x2);
        return true;
    }
    return false;
}

void sortRoots(double* x1, double* x2) // x1 = min(x1, x2), x2 = max(x1, x2), NAN > any num
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

bool isCorrectRoots(Test_data_equation test, N_roots count_roots, double x1, double x2)
{
    if (test.count_roots != count_roots)
        return 0;
    if (count_roots == ONE_ROOT)
        return equal(x1, test.x1) || equal(x2, test.x2);
    if (count_roots == TWO_ROOTS)
        return equal(x1, test.x1) && equal(x2, test.x2);
    return 1;
}
