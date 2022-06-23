#include "matrix.h"

PyMethodDef matrix_methods[] = {
    {
        "print",
        print_matrix,
        METH_VARARGS,
        "Print matrix"
    },
    {NULL, NULL, 0, NULL}
};

PyTypeObject matrix_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "matrix",
    .tp_basicsize = sizeof(matrix),
    .tp_dealloc = (destructor)matrix_free,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Matrix object",
    .tp_methods = matrix_methods,
};

matrix* new_matrix(PyObject* a, PyObject* args)
{
    int n, m;
    if (!PyArg_ParseTuple(args, "ii", &n, &m))
        return NULL;
    return get_zero_mat(m, m);
}

matrix* _new_matrix(int n, int m)
{
    matrix* mat = PyObject_NEW(matrix, &matrix_Type);
    matrix_init(mat, n, m);
    return mat;
}

PyObject *print_matrix(PyObject* a, PyObject *args)
{
    matrix* v = (matrix*)a;
    for (int i = 0; i<v->n; ++i){
        for (int j = 0; j<v->m; ++j) {
            printf("%*f", 10, get_mat_elem(v, i, j));
        }
        printf("\n");
    }
    Py_INCREF(Py_None);
    return Py_None;
}

void matrix_init(matrix* mat, int n, int m)
{
    mat->data = malloc(DSIZE * n * m);
    mat->n = n;
    mat->m = m;
}

void matrix_free(matrix* mat)
{
    free(mat->data);
    Py_XDECREF(mat);
    Py_TYPE(mat)->tp_free((PyObject*)mat);
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
    double old_elem = mat->data[i*(mat->m) + j];
    mat->data[i*(mat->m) + j];
    return old_elem;
}

matrix* get_random_mat(int n, int m, int l, int r)
{
    matrix* mat = _new_matrix(n, m);
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
    matrix* mat = _new_matrix(n, m);
    for (int i = 0; i<n; ++i)
        for (int j = 0; j<m; ++j){
            set_mat_elem(mat, i, j, 0);
        }
    return mat;
}

matrix* get_id_mat(int n)
{
    matrix* mat = get_zero_mat(n, n);
    for (int i = 0; i<n; ++i) set_mat_elem(mat, i, i, 1);
    return mat;
}

