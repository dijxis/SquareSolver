#ifndef TEST_SOLVER_H_INCLUDED
#define TEST_SOLVER_H_INCLUDED

#include "solver.h"

struct Test_data_equation
{
    Coefficient_equation coeff;
    Roots_data roots;
};

int testSolveEquation();
bool oneTestSolveEquation(Test_data_equation current_test);
void sortRoots(double* x1, double* x2);
bool isCorrectRoots(Test_data_equation test, Roots_data current_roots);

#endif
