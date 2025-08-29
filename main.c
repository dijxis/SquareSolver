#include <stdio.h>
#include <math.h>
#include "solver.h"
#include "test_solver.h"

void readCoeff(Coefficient_equation* coeff);
void readOneCoeff(double* one_coeff, char name_coeff);
void printRoots(Roots_data roots);

int main()
{
    printf("Test solver? [y/n] ");
    if (getchar() == 'y' && testSolveEquation() == 0)
        printf("Testing func solveEquation success\n");
    while (getchar() != '\n');

    Coefficient_equation coeff = {NAN, NAN, NAN};
    readCoeff(&coeff);

    Roots_data roots = solveEquation(coeff);

    printRoots(roots);
    printf("\nCOMMIT GITHUB\n");
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
            printf("No roots");
            break;
        case INF_ROOT:
            printf("Any numbers");
            break;
        case NAN_ROOTS:
        default:
            printf("count_roots = %d", roots.count_roots);
            break;
    }
}


void readCoeff(Coefficient_equation* coeff)
{
    printf("Enter coefficients of equation ax^2 + bx + c = 0\n");
    readOneCoeff(&(coeff->a), 'a');
    readOneCoeff(&(coeff->b), 'b');
    readOneCoeff(&(coeff->c), 'c');
}

void readOneCoeff(double* one_coeff, char name_coeff)
{
    printf("Enter %c = ", name_coeff);
    while (1)
    {
        bool number_is_read = scanf("%lg", one_coeff);
        int ch = 0;;
        while ((ch = getchar()) == ' ');
        if (number_is_read == 1 && ch == '\n')
            break;
        while (ch != '\n')
            ch = getchar();
        printf("Invalid input, enter again %c = ", name_coeff);
    }
}
