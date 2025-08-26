#define TX_COMPILED
#include <TXlib.h>
#include <stdio.h>
#include "solver.h"
#include "test_solver.h"

void printRoots(Roots_data roots);

int main()
{
    if (testSolveEquation() == 0)
        printf("Тестирование функции solve_equation прошло успешно\n");

    Coefficient_equation coeff = {0, 0, 0};
    printf("Введите коэффициенты уравнения ax^2 + bx + c = 0\n"
           "a, b, c: ");
    scanf("%lg %lg %lg", &coeff.a, &coeff.b, &coeff.c);

    Roots_data roots = solveEquation(coeff);

    printRoots(roots);
    printf("\nCOMMIT GITHUB");
    return 0;
}

void printRoots(Roots_data roots)
{
    switch (roots.count_roots)
    {
        case ONE_ROOT:
            printf("x = %lg", roots.x1);
            break;
        case TWO_ROOTS:
            printf("x1 = %lg\n", roots.x1);
            printf("x2 = %lg", roots.x2);
            break;
        case NO_ROOTS:
            printf("Нет корней");
            break;
        case INF_ROOT:
            printf("Любое число");
            break;
        case NAN_ROOTS:
        default:
            printf("count_roots = %d", roots.count_roots);
            break;
    }
}
