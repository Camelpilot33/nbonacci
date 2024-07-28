#include <stdio.h>
#include <time.h>
#include "matrix.h"

// time complexity O(2^n), space complexity O(n)
int exponential(int n) // This function uses recursion and the standard formula
{
    if (n <= 1)
    {
        return n;
    }
    return exponential(n - 1) + exponential(n - 2);
}

// time complexity O(n), space complexity O(1)
void linear(int n, mpz_t result) // This function uses iteration
{
    mpz_t a, b, next;
    mpz_init_set_ui(a, 0);
    mpz_init_set_ui(b, 1);
    mpz_init(next);

    if (n == 0)
    {
        mpz_set_ui(result, 0);
        return;
    }

    for (int i = 2; i <= n; i++)
    {
        mpz_add(next, a, b);
        mpz_set(a, b);
        mpz_set(b, next);
    }

    mpz_set(result, b);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(next);
}

// time complexity O(log(n)), space complexity O(1)
void logarithmic(int n, mpz_t res) // This function uses matrix exponentiation
{

    Matrix *m = create_matrix(2);
    if (m == NULL)
        exit(1);

    mpz_set_ui(m->matrix[0][0], 0);
    mpz_set_ui(m->matrix[0][1], 1);
    mpz_set_ui(m->matrix[1][0], 1);
    mpz_set_ui(m->matrix[1][1], 1);

    Matrix *result = power_matrix(m, n);
    if (result == NULL)
        exit(1);
    mpz_set(res, result->matrix[0][1]);
    if (m != result)
        free_matrix(result);
    free_matrix(m);
}

void time_test(int n, int f)
{
    clock_t time_left = 1000;
    if (f == 0)
    {
        clock_t start = clock();
        int i = 0;
        while (clock() < start + time_left)
        {
            exponential(n);
            i++;
        }
        printf("Exponential calculated f(%d) %d times\n", n, i);
    } else if (f == 1)
    {
        clock_t start = clock();
        int i = 0;
        mpz_t linear_result;
        mpz_init(linear_result);
        while (clock() < start + time_left)
        {
            linear(n, linear_result);
            i++;
        }
        printf("Linear      calculated f(%d) %d times\n", n, i);
    } else if (f == 2)
    {
        clock_t start = clock();
        int i = 0;
        mpz_t logarithmic_result;
        mpz_init(logarithmic_result);
        while (clock() < start + time_left)
        {
            logarithmic(n, logarithmic_result);
            i++;
        }
        printf("Logarithmic calculated f(%d) %d times\n", n, i);
    }
}

int main()
{
    int m = 2;
    
    //30
    printf("30\n");
    time_test(30, 0);
    time_test(30, 1);
    time_test(30, 2);

    //2000
    printf("2000\n");
    time_test(2000, 1);
    time_test(2000, 2);
    return 0;
}