#ifndef VECTOR
#define VECTOR
#include <Python.h>
#include <stdlib.h>
#include <time.h>
#define DSIZE  sizeof(double)

typedef struct
{
    PyObject_HEAD
    double* data;
    int length;
} vector;

void vector_init(vector* v, int length);
void vector_free(vector* v);
double get_v_elem(vector* v, int i);
double set_v_elem(vector* v, int i, double elem);
vector* get_random_vec(int length, int l, int r);
vector* get_zero_vec(int length);
PyObject *print_vector(PyObject* a);

#endif