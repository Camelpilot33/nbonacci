#include <stdio.h>
#include <time.h>
#include "matrix.h"

// time complexity O(2^n), space complexity O(n)
int exponential(int n, int m) // This function uses recursion and the standard formula
{
    if (n < m)
        return 0;
    if (n == m)
        return 1;
    int res = 0;
    for (int i = 1; i <= m; i++)
    {
        res += exponential(n - i, m);
    }
    return res;
}

// time complexity O(n), space complexity O(1)
void linear(int n, int m, mpz_t result) // This function uses iteration
{
    mpz_t next;
    mpz_t a[m];
    for (int i = 0; i < m; i++)
    {
        mpz_init_set_ui(a[i], i==m-1);
    }
    mpz_init(next);

    if (n < m)
    {
        mpz_set_ui(result, 0);
        return;
    }

    for (int i = m; i <= n; i++)
    {
        mpz_set_ui(next, 0);
        for (int j = 0; j < m; j++)
        {
            mpz_add(next, next, a[j]);
        }
        for (int j = 0; j < m - 1; j++)
        {
            mpz_set(a[j], a[j + 1]);
        }
        mpz_set(a[m - 1], next);
    }

    mpz_set(result, a[m - 1]);
    for (int i = 0; i < m; i++)
    {
        mpz_clear(a[i]);
    }
    mpz_clear(next);
}

// time complexity O(log(n)), space complexity O(1)
void logarithmic(int n, int p, mpz_t res) // This function uses matrix exponentiation
{

    Matrix *m = create_matrix(p);
    if (m == NULL)
        exit(1);

    /*
    m[p*p]=
    0 1 0 .. 0
    0 0 1 .. 0
    .    .   .
    .      . .
    0 0 0 .. 1
    1 1 1 .. 1

    m^n * | 0 | = | fp(n)     |
          | 0 |   | fp(n+1)   |
          | . |   |    .     |
          | . |   |    .     |
          | 1 |   | fp(n+m-1) |
    */

    for (int i=0;i<p;i++) {
        for (int j=0;j<p-1;j++) {
            mpz_set_ui(m->matrix[i][j], i==j+1);
        }
        mpz_set_ui(m->matrix[i][p-1], 1);
    }

    Matrix *result = power_matrix(m, n);
    //print:
    // for (int i=0;i<p;i++) {
    //     for (int j=0;j<p;j++) {
    //         gmp_printf("%Zd ", result->matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    if (result == NULL)
        exit(1);
    mpz_set(res, result->matrix[0][1]);
    if (m != result)
        free_matrix(result);
    free_matrix(m);
}

void time_test(int n, int m, int f)
{
    clock_t time_left = 1000;
    if (f == 0)
    {
        clock_t start = clock();
        int i = 0;
        while (clock() < start + time_left)
        {
            exponential(n,m);
            i++;
        }
        printf("Exponential > f_%d(%d) %d\n", m, n, i);
    } else if (f == 1)
    {
        clock_t start = clock();
        int i = 0;
        mpz_t linear_result;
        mpz_init(linear_result);
        while (clock() < start + time_left)
        {
            linear(n, m, linear_result);
            i++;
        }
        printf("Linear      > f_%d(%d) %d\n", m, n, i);
    } else if (f == 2)
    {
        clock_t start = clock();
        int i = 0;
        mpz_t logarithmic_result;
        mpz_init(logarithmic_result);
        while (clock() < start + time_left)
        {
            logarithmic(n, m, logarithmic_result);
            i++;
        }
        printf("Logarithmic > f_%d(%d) %d\n", m, n, i);
    }
}

int main()
{
    int m = 4;
    for (int i=0;i<20;i++) {
        mpz_t res;
        mpz_init(res);
        logarithmic(i,m,res);
        gmp_printf("f(%d) = %Zd\n", i, res);
    }
    //30
    // printf("\n30\n");
    // time_test(30, m, 0);
    // time_test(30, m, 1);
    // time_test(30, m, 2);

    // //3000
    // printf("\n2000\n");
    // time_test(3000, m, 1);
    // time_test(3000, m, 2);
    return 0;
}