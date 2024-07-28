#include <stdio.h>
#include "matrix.h"

// time complexity O(2^n), space complexity O(n)
int fib(int n) // This function uses recursion and the standard formula
{
    if (n <= 1)
    {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

// time complexity O(n), space complexity O(1)
int lin_fib(int n) // This function stores stores only the last two numbers of the sequence
{
    int a = 0, b = 1, next;
    if (n == 0)
        return a;
    for (int i = 2; i <= n; i++)
    {
        next = a + b;
        a = b;
        b = next;
    }
    return b;
}

// time complexity O(log(n)), space complexity O(1)
mpz_t *log_fib(int n) // This function uses matrix exponentiation
{
    if (n == 0)
        return 0;
    Matrix *m = create_matrix(2);
    if (m == NULL) exit(1);
    mpz_set_ui(m->matrix[0][0], 0);
    mpz_set_ui(m->matrix[0][1], 1);
    mpz_set_ui(m->matrix[1][0], 1);
    mpz_set_ui(m->matrix[1][1], 1);
    Matrix *result = power_matrix(m, n);
    if (result == NULL) exit(1);
    //set out to result->matrix[0][1];
    mpz_t *out = malloc(sizeof(mpz_t));
    mpz_init(*out);
    mpz_set(*out, result->matrix[0][1]);
    if (m!=result) free_matrix(result);
    free_matrix(m);
    return out;
}

int main()
{
    gmp_printf("%d, %d, %Zd\n", fib(10), lin_fib(10), *log_fib(10));
    return 0;
}