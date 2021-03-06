#ifndef MATRIX
#define MATRIX

#include <Python.h>
#include <stdlib.h>
#include <time.h>
#define DSIZE  sizeof(double)
typedef struct
{
    PyObject_HEAD
    double* data;
    int n;
    int m;
} matrix;

void matrix_init(matrix* mat, int n, int m);
void matrix_free(matrix* mat);
double get_mat_elem(matrix* mat, int i, int j);
double set_mat_elem(matrix* mat, int i, int j, double elem);
matrix* get_random_mat(int n, int m, double l, double r);
matrix* get_zero_mat(int n, int m);
matrix* get_id_mat(int n);
PyMethodDef matrix_methods[];
PyTypeObject matrix_Type;
matrix* new_matrix(PyObject* a, PyObject* args);
PyObject *print_matrix(PyObject* a, PyObject *args);
matrix* _new_matrix(int n, int m);
matrix* rand_new_matrix(PyObject* a, PyObject* args);
matrix* eye(PyObject* a, PyObject* args);
PyObject *fill_matrix(PyObject* a, PyObject *args);
PyObject *shape(PyObject* a, PyObject *args);
PyObject* get_m(PyObject* self, PyObject *args);
PyObject* set_m(PyObject* self, PyObject *args);

#endif