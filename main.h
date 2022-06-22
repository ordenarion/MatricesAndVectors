#include <Python.h>
#include "vector.h"
#include "matrix.h"

static PyTypeObject matrix_Type;
static PyTypeObject vector_Type;

matrix* new_matrix(PyObject* a, PyObject* args);
vector* new_vector(PyObject* a, PyObject* args);