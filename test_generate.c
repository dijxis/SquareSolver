#include <stdio.h>
#include <stdlib.h>

int MAX_COEFF = 100000;

int r();

int main()
{
    int count_test = 0;
    printf("count_test = ");
    scanf("%d", &count_test);
    FILE* file = fopen("tests.txt", "w");
    fprintf(file, "%d\n", count_test);

    fprintf(file, "0 0 0 -1 nan nan\n");
    fprintf(file, "0 0 1 0 nan nan\n");
    fprintf(file, "0 1 0 1 0 nan\n");
    fprintf(file, "0 1 1 1 1 nan\n");
    count_test -= 4;

    for (int i = 0; i < count_test / 10000; i++)
    {
        int b = r(), c = r();
        if (b != 0)
        {
            double x = (double) -c / b;
            fprintf(file, "0 %d %d 1 %lg nan\n", b, c, x);
        }
        else
        {
            if (c == 0)
                fprintf(file, "0 0 0 -1 nan nan\n");
            else
                fprintf(file, "0 0 %d 0 nan nan\n", c);
        }

    }
    for (int i = count_test / 10000; i < count_test; i++)
    {
        int a = ((rand() % 2 ? 1 : -1) * (rand() % 100));
        while (a == 0)
            a = ((rand() % 2 ? 1 : -1) * (rand() % 100));
        long long x1 = r(), x2 = r();
        long long b = -(x1 + x2) * a, c = x1 * x2 * a;
        fprintf(file, "%d %lld %lld %d %lld %lld\n", a, b, c, (x1 == x2 ? 1 : 2), x1, x2);
    }
}

int r()
{
    int sign = rand() % 2 ? 1 : -1;
    return (rand() % MAX_COEFF) * sign;
}
