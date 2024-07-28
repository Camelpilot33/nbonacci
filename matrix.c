#include "matrix.h"
#include <stdio.h>
#include <time.h>

Matrix *create_matrix(int size)
{
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    if (m == NULL) return NULL;
    m->size = size;
    m->matrix = (ull**)malloc(size * sizeof(ull *));
    if (m->matrix == NULL) {
        free(m);
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        m->matrix[i] = (ull *)malloc(size * sizeof(ull));
        if (m->matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < size; k++)
                    mpz_clear(m->matrix[j][k]);
                free(m->matrix[j]);
            }
            free(m->matrix);
            free(m);
            return NULL;
        }
        for (int j = 0; j < size; j++) {
            mpz_init(m->matrix[i][j]);
        }
    }
    return m;
}

Matrix *id_matrix(int size)
{
    Matrix *m = create_matrix(size);
    if (m == NULL) return NULL;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                mpz_set_ui(m->matrix[i][j], 1);
            else
                mpz_set_ui(m->matrix[i][j], 0);
        }
    }
    return m;
}

Matrix *multiply_matrix(Matrix *a, Matrix *b)
{
    if (a->size != b->size) return NULL;
    Matrix *c = create_matrix(a->size);
    if (c == NULL) return NULL;
    for (int i = 0; i < a->size; i++)
    {
        for (int j = 0; j < a->size; j++)
        {
            mpz_set_ui(c->matrix[i][j], 0);
            for (int k = 0; k < a->size; k++)
            {
                ull temp;
                mpz_init(temp);
                mpz_mul(temp, a->matrix[i][k], b->matrix[k][j]);
                mpz_add(c->matrix[i][j], c->matrix[i][j], temp);
                mpz_clear(temp);
            }
        }
    }
    return c;
}

Matrix *power_matrix(Matrix *m, unsigned long long int n)
{
    if (n == 0)
        return id_matrix(m->size);
    if (n == 1)
        return m;

    Matrix *result = id_matrix(m->size);
    Matrix *base = create_matrix(m->size);

    if (result == NULL || base == NULL) {
        free_matrix(result);
        free_matrix(base);
        return NULL;
    }

    for (int i = 0; i < m->size; i++)
        for (int j = 0; j < m->size; j++)
            mpz_set(base->matrix[i][j], m->matrix[i][j]);

    while (n > 0)
    {
        if (n % 2 == 1)
        {
            Matrix *temp = multiply_matrix(result, base);
            if (temp == NULL) {
                free_matrix(result);
                free_matrix(base);
                return NULL;
            }
            free_matrix(result);
            result = temp;
        }
        n /= 2;
        if (n > 0) {
            Matrix *temp = multiply_matrix(base, base);
            if (temp == NULL) {
                free_matrix(result);
                free_matrix(base);
                return NULL;
            }
            free_matrix(base);
            base = temp;
        }
    }
    free_matrix(base);
    return result;
}

void free_matrix(Matrix *m)
{
    if (m == NULL) return;
    for (int i = 0; i < m->size; i++)
    {
        for (int j = 0; j < m->size; j++)
            mpz_clear(m->matrix[i][j]);
        free(m->matrix[i]);
    }
    free(m->matrix);
    free(m);
}

// // Test
// int main()
// {
//     clock_t start = clock();   
//     Matrix *m = create_matrix(2);
//     if (m == NULL) return 1;
//     mpz_set_ui(m->matrix[0][0], 0);
//     mpz_set_ui(m->matrix[0][1], 1);
//     mpz_set_ui(m->matrix[1][0], 1);
//     mpz_set_ui(m->matrix[1][1], 1);   
//     int n = 40000000;
//     Matrix *result = power_matrix(m, n);
//     if (result == NULL) return 1;
//     printf("Number of digits: %d\n", mpz_sizeinbase(result->matrix[0][1], 10));
//     if (m!=result) free_matrix(result);
//     free_matrix(m);
//     printf("Time taken: %.2fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
//     return 0;
// }