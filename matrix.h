#include <stdlib.h>
#include <gmp.h>

typedef mpz_t ull;
typedef struct {
    int size;
    ull **matrix;
} Matrix;

Matrix *create_matrix(int size);
Matrix *id_matrix(int size);
Matrix *multiply_matrix(Matrix *a, Matrix *b);
Matrix *power_matrix(Matrix *m, unsigned long long int n);
void free_matrix(Matrix *m);