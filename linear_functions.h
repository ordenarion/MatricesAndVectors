#ifndef L_FUNC
#define L_FUNC
#include "vector.h"
#include "matrix.h"
#include <Python.h>
#include <math.h>

PyObject* norm(PyObject* a, PyObject *args);
PyObject* VxR(PyObject* a, PyObject *args);
PyObject* VplusV(PyObject* a, PyObject *args);
PyObject* VminusV(PyObject* a, PyObject *args);
PyObject* VdotV(PyObject* a, PyObject *args);
PyObject* VxV(PyObject* a, PyObject *args);
PyObject* MxR(PyObject* a, PyObject *args);
PyObject* MplusM(PyObject* a, PyObject *args);
PyObject* MminusM(PyObject* a, PyObject *args);
PyObject* MxV(PyObject* a, PyObject *args);
PyObject* MxM(PyObject* a, PyObject *args);
PyObject* MRot(PyObject* a, PyObject *args);

#endif