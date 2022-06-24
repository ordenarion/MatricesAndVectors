#include "linear_functions.h"


PyObject* norm(PyObject* a, PyObject *args)
{
    vector* v;
    if (!PyArg_ParseTuple(args, "O!", &vector_Type, &v)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a vector.");
        return NULL;
    }
    double n = 0;
    for (int i = 0; i<v->length; ++i){
        double cur = get_v_elem(v, i);
        n += cur*cur;
    }
    return Py_BuildValue("d", sqrt(n));
}
//PyObject* VxR(PyObject* a, PyObject *args);
//PyObject* VplusV(PyObject* a, PyObject *args);
//PyObject* VminusV(PyObject* a, PyObject *args);
//PyObject* VdotV(PyObject* a, PyObject *args);
//PyObject* VxV(PyObject* a, PyObject *args);
//PyObject* MxR(PyObject* a, PyObject *args);
//PyObject* MplusM(PyObject* a, PyObject *args);
//PyObject* MminusM(PyObject* a, PyObject *args);
//PyObject* MxV(PyObject* a, PyObject *args);
//PyObject* MxM(PyObject* a, PyObject *args);
//PyObject* MRot(PyObject* a, PyObject *args);