#include "test_solver.h"
#include <math.h>
#include <stdio.h>

int testSolveEquation()
{
    int count_failed_tests = 0;
    FILE *file = fopen("tests.txt", "r");
    int count_tests = 0;
    fscanf(file, "%d", &count_tests);
    for (int test_num = 0; test_num < count_tests; test_num++)
    {
        Test_data_equation test = {{NAN, NAN, NAN}, {NAN_ROOTS, NAN, NAN}};
        int temp = 0;
        fscanf(file, "%lg %lg %lg %d %lg %lg", &test.coeff.a, &test.coeff.b, &test.coeff.c,
               &temp, &test.roots.x1, &test.roots.x2);
        test.roots.count_roots = (N_roots) temp;
        count_failed_tests += oneTestSolveEquation(test);
    }
    fclose(file);
    return count_failed_tests;
}

bool oneTestSolveEquation(Test_data_equation current_test)
{
    Roots_data roots = solveEquation(current_test.coeff);
    sortRoots(&roots.x1, &roots.x2);
    sortRoots(&current_test.roots.x1, &current_test.roots.x2);
    if (!isCorrectRoots(current_test, roots))
    {
        printf("FAILED: a = %lg, b = %lg, c = %lg, count_roots = %d, x1 = %lg, x2 = %lg "
               "(should be count_roots = %d, x1 = %lg, x2 = %lg)\n",
                current_test.coeff.a, current_test.coeff.b, current_test.coeff.c, roots.count_roots, roots.x1, roots.x2,
                current_test.roots.count_roots, current_test.roots.x1, current_test.roots.x2);
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

bool isCorrectRoots(Test_data_equation test, Roots_data current_roots)
{
    if (test.roots.count_roots != current_roots.count_roots)
        return 0;
    if (current_roots.count_roots == ONE_ROOT)
        return equalTwoDouble(current_roots.x1, test.roots.x1) || equalTwoDouble(current_roots.x2, test.roots.x2);
    if (current_roots.count_roots == TWO_ROOTS)
        return equalTwoDouble(current_roots.x1, test.roots.x1) && equalTwoDouble(current_roots.x2, test.roots.x2);
    return 1;
}
