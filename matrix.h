#ifndef MATRIX
#define MATRIX
#include <Python.h>
#include <stdlib.h>
#include <time>
typedef struct
{
    PyObject_HEAD
    double* data;
    int n;
    int m;
} matrix;

#endif