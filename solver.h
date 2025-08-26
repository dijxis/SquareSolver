#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

enum N_roots
{
    NAN_ROOTS = -2,
    INF_ROOT = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};

struct Coefficient_equation
{
    double a, b, c;
};

struct Roots_data
{
    N_roots count_roots;
    double x1, x2;
};

Roots_data solveEquation(Coefficient_equation coeff);
Roots_data solveLinear(double b, double c);
Roots_data solveSquare(Coefficient_equation coeff);
bool equalTwoDouble(double a, double b);

#endif
