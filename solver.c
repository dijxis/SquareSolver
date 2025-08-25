#include "solver.h"
#include <math.h>

const double EPSILON = 1e-9;


N_roots solveEquation(double a, double b, double c,
                       double* x1, double* x2)
{
    if (equal(a, 0))
    {
        return solveLinear(b, c, x1);
    }
    else
    {
        return solveSquare(a, b, c, x1, x2);
    }
}

N_roots solveSquare(double a, double b, double c,
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

N_roots solveLinear(double b, double c,
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

bool equal(double a, double b)
{
    if (isnan(a) && isnan(b))
        return 1;
    if (isnan(a) || isnan(b))
        return 0;
    return fabs(a - b) <= EPSILON;
}
