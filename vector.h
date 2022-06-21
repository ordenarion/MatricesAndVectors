#ifndef VECTOR
#define VECTOR
#include <Python.h>
#include <stdlib.h>
#include <time>
#define DSIZE  sizeof(double)

typedef struct
{
    PyObject_HEAD
    double* data;
    int length;
} vector;

#endif