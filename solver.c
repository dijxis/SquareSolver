#include "solver.h"
#include <math.h>

const double EPSILON = 1e-9;


Roots_data solveEquation(Coefficient_equation coeff)
{
    if (equalTwoDouble(coeff.a, 0))
    {
        return solveLinear(coeff.b, coeff.c);
    }
    else
    {
        return solveSquare(coeff);
    }
}

Roots_data solveSquare(Coefficient_equation coeff)
{
    Roots_data roots = {NAN_ROOTS, NAN, NAN};
    double discriminant = coeff.b * coeff.b - 4 * coeff.a * coeff.c;
    if (discriminant > EPSILON)
    {
        roots.x1 = (-coeff.b + sqrt(discriminant)) / (2 * coeff.a);
        roots.x2 = (-coeff.b - sqrt(discriminant)) / (2 * coeff.a);
        roots.count_roots = TWO_ROOTS;
    }
    else if (equalTwoDouble(discriminant, 0))
    {
        roots.x1 = roots.x2 = -coeff.b / (2 * coeff.a);
        roots.count_roots = ONE_ROOT;
    }
    else
    {
        roots.count_roots = NO_ROOTS;
    }
    return roots;
}

Roots_data solveLinear(double b, double c)
{
    Roots_data roots = {NAN_ROOTS, NAN, NAN};
    if (equalTwoDouble(b, 0))
    {
        if (equalTwoDouble(c, 0))
            roots.count_roots = INF_ROOT;
        else
            roots.count_roots = NO_ROOTS;
    }
    else
    {
        roots.x1 = -c / b;
        roots.count_roots = ONE_ROOT;
    }
    return roots;
}

bool equalTwoDouble(double a, double b)
{
    if (isnan(a) && isnan(b))
        return 1;
    if (isnan(a) || isnan(b))
        return 0;
    return fabs(a - b) <= EPSILON;
}
