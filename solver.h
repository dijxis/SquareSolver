enum N_roots
{
    NAN_ROOTS = -2,
    INF_ROOT = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};

N_roots solveEquation(double a, double b, double c,
                       double* x1, double* x2);
N_roots solveLinear(double b, double c,
                     double* x);
N_roots solveSquare(double a, double b, double c,
                     double* x1, double* x2);
bool equal(double a, double b);

