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
    Py_XDECREF(mat);
    Py_TYPE(self)->tp_free((PyObject*)mat);
    free(mat);
}

vector* new_matrix(int n, int m)
{
    int n, m;
    if (!PyArg_ParseTuple(args, "ii", &n, &m))
        return NULL;
    matrix* mat = PyObject_NEW(matrix, &matrix_Type);
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

matrix* get_random_mat(int n, int m, int l, int r)
{
    matrix* mat = new_matrix(n, m);
    srand(time(NULL));
    for (int i = 0; i<n; ++i)
        for (int j = 0; j<m; ++j){
            double el = (double)rand() / (double)RAND_MAX * (r-l) + l;
            set_mat_elem(mat, i, j, el);
        }
    return mat;
}

matrix* get_zero_mat(int n, int m)
{
    matrix* mat = new_matrix(n, m);
    for (int i = 0; i<n; ++i)
        for (int j = 0; j<m; ++j){
            set_mat_elem(mat, i, j, 0);
        }
    return mat;
}

matrix get_id_mat(int n)
{
    matrix* mat = get_zero_mat(n, n);
    for (int i = 0; i<n; ++i) set_mat_elem(mat, i, i, 1);
    return mat;
}

static PyObject *print_matrix(PyObject* a)
{
    vector* v = (vector*)a;
    for (int i = 0; i<v->n; ++i){
        for (int j = 0; j<v->m; ++j) {
            printf("%*f", 10, get_v_elem(v, i, j));
        }
        printf("\n");
    }
}