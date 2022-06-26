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

PyObject* VxR(PyObject* a, PyObject *args)
{
    vector* v;
    double r;
    if (!PyArg_ParseTuple(args, "O!d", &vector_Type, &v, &r)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be a vector and a double.");
        return NULL;
    }
    vector* new_v = _new_vector(v->length);
    for (int i = 0; i<v->length; ++i){
        set_v_elem(new_v, i, get_v_elem(v, i)*r);
    }
    return new_v;
}

PyObject* VplusV(PyObject* a, PyObject *args)
{
    vector *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &vector_Type, &v, &vector_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be a vector and a vector.");
        return NULL;
    }
    if ((v->length)!=(w->length)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    vector* new_v = _new_vector(v->length);
    for (int i = 0; i<v->length; ++i){
        set_v_elem(new_v, i, get_v_elem(v, i)+get_v_elem(w, i));
    }
    return new_v;
}
PyObject* VminusV(PyObject* a, PyObject *args)
{
    vector *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &vector_Type, &v, &vector_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be a vector and a vector.");
        return NULL;
    }
    if ((v->length)!=(w->length)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    vector* new_v = _new_vector(v->length);
    for (int i = 0; i<v->length; ++i){
        set_v_elem(new_v, i, get_v_elem(v, i)-get_v_elem(w, i));
    }
    return new_v;
}

PyObject* VdotV(PyObject* a, PyObject *args)
{
    vector *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &vector_Type, &v, &vector_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be a vector and a vector.");
        return NULL;
    }
    if ((v->length)!=(w->length)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    double res = 0;
    for (int i = 0; i<v->length; ++i){
        res += get_v_elem(v, i)*get_v_elem(w, i);
    }
    return Py_BuildValue("d", res);
}

PyObject* VxV(PyObject* a, PyObject *args)
{
    vector *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &vector_Type, &v, &vector_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be a vector and a vector.");
        return NULL;
    }
    if ((v->length)!=(w->length) && 3!=(w->length)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    double ax = get_v_elem(v, 0), ay = get_v_elem(v, 1), az = get_v_elem(v, 2);
    double bx = get_v_elem(w, 0), by = get_v_elem(w, 1), bz = get_v_elem(w, 2);
    vector* new_v = _new_vector(v->length);
    set_v_elem(new_v, 0, ay*bz-az*by);
    set_v_elem(new_v, 1, az*bx-ax*bz);
    set_v_elem(new_v, 2, ax*by-ay*bx);
    return new_v;
}

// -----------------------------------------------------------------------------------------------------------------

//PyObject* MxR(PyObject* a, PyObject *args);
//PyObject* MplusM(PyObject* a, PyObject *args);
//PyObject* MminusM(PyObject* a, PyObject *args);
//PyObject* MxV(PyObject* a, PyObject *args);
//PyObject* MxM(PyObject* a, PyObject *args);
//PyObject* MRot(PyObject* a, PyObject *args);