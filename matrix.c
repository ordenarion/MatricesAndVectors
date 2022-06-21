#include "matrix.h"

void matrix_init(matrix* mat, int n, int m)
{
    v->data = malloc(DSIZE * n * m);
    v->n = n;
    v->m = m;
}

void matrix_free(matrix* mat)
{
    free(mat->data);
    free(mat);
}

vector* new_matrix(int n, int m)
{
    matrix* mat = malloc(sizeof(matrix));
    matrix_init(v, n, m);
    return mat;
}

double get_mat_elem(matrix* mat, int i, int j)
{
    i = i%(mat->n);
    j = j%(mat->m);
    return mat->data[i*(mat->m) + j];
}

double set_mat_elem(matrix* mat, int i, int j, double elem)
{
    i = i%(mat->n);
    j = j%(mat->m);
    double old_elem = mat->data[i*m + j];
    data[i*(mat->m) + j]
    return old_elem;
}