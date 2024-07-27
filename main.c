#include <stdio.h>

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
int log_fib(int n) // This function uses matrix exponentiation
{
    int F[2][2] = {{1, 1}, {1, 0}};
    if (n == 0)
        return 0;
    power(F, n - 1);
    return F[0][0];
}

int main()
{
    printf("%d, %d\n", fib(10), lin_fib(10));
    return 0;
}