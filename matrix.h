#ifndef MATRIX
#define MATRIX
#include <Python.h>

typedef struct
{
    PyObject_HEAD
    double* data;
    int n;
    int m;
} matrix;

#endif