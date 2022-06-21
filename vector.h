#ifndef VECTOR
#define VECTOR
#include <Python.h>
#define DSIZE  sizeof(double)

typedef struct
{
    PyObject_HEAD
    double* data;
    int length;
} vector;

#endif