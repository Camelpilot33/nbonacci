#include "matrix.h"
#include <stdio.h>

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
            for (int j = 0; j < i; j++)
                free(m->matrix[j]);
            free(m->matrix);
            free(m);
            return NULL;
        }
    }
    return m;
}

// Matrix *id_matrix(int size)
// {
//     Matrix *m = create_matrix(size);
//     if (m == NULL) return NULL;
//     for (int i = 0; i < size; i++)
//     {
//         for (int j = 0; j < size; j++)
//         {
//             m->matrix[i][j] = (ull)(i == j);
//         }
//     }
//     return m;
// }

// Matrix *multiply_matrix(Matrix *a, Matrix *b)
// {
//     if (a->size != b->size) return NULL;
//     Matrix *c = create_matrix(a->size);
//     if (c == NULL) return NULL;
//     for (int i = 0; i < a->size; i++)
//     {
//         for (int j = 0; j < a->size; j++)
//         {
//             c->matrix[i][j] = 0;
//             for (int k = 0; k < a->size; k++)
//             {
//                 c->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
//             }
//         }
//     }
//     return c;
// }
// Matrix *power_matrix(Matrix *m, int n)
// {
//     if (n == 0)
//         return id_matrix(m->size);
//     if (n == 1)
//         return m;
//     Matrix *result = id_matrix(m->size);
//     Matrix *base = create_matrix(m->size);
//     if (result == NULL || base == NULL) {
//         free_matrix(result);
//         free_matrix(base);
//         return NULL;
//     }
//     for (int i = 0; i < m->size; i++)
//         for (int j = 0; j < m->size; j++)
//             base->matrix[i][j] = m->matrix[i][j];
//     while (n > 0)
//     {
//         if (n % 2 == 1)
//         {
//             Matrix *temp = multiply_matrix(result, base);
//             if (temp == NULL) {
//                 free_matrix(result);
//                 free_matrix(base);
//                 return NULL;
//             }
//             free_matrix(result);
//             result = temp;
//         }
//         n /= 2;
//         if (n > 0) {
//             Matrix *temp = multiply_matrix(base, base);
//             if (temp == NULL) {
//                 free_matrix(result);
//                 free_matrix(base);
//                 return NULL;
//             }
//             free_matrix(base);
//             base = temp;
//         }
//     }
//     free_matrix(base);
//     return result;
// }

// void free_matrix(Matrix *m)
// {
//     for (int i = 0; i < m->size; i++)
//     {
//         free(m->matrix[i]);
//     }
//     free(m->matrix);
//     free(m);
// }

int main()
{
    Matrix *m = create_matrix(2);
    if (m == NULL) return 1;
    // m->matrix[0][0] = 0;
    // m->matrix[0][1] = 1;
    // m->matrix[1][0] = 1;
    // m->matrix[1][1] = 1;
    // Matrix *a = power_matrix(m, 93); //93 is largest handled by ull
    // if (a == NULL) return 1;
    // printf("[%llu %llu]\n[%llu %llu]\n", a->matrix[0][0], a->matrix[0][1], a->matrix[1][0], a->matrix[1][1]);
    // printf("%llu\n", (ull)0xffffffffffffffff/a->matrix[0][1]);
    // if (m!=a) free_matrix(a);
    // free_matrix(m);
    return 0;
}