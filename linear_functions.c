#include "linear_functions.h"

// здесь функции, которые позволяют работать с матрицами и векторами

// норма вектора
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

// произведение вектора на число
PyObject* VxR(PyObject* a, PyObject *args)
{
    vector* v;
    double r;
    if (!PyArg_ParseTuple(args, "O!d", &vector_Type, &v, &r)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be vector and double.");
        return NULL;
    }
    vector* new_v = _new_vector(v->length);
    for (int i = 0; i<v->length; ++i){
        set_v_elem(new_v, i, get_v_elem(v, i)*r);
    }
    return new_v;
}

// сложение двух векторов
PyObject* VplusV(PyObject* a, PyObject *args)
{
    vector *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &vector_Type, &v, &vector_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be vector and vector.");
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

// разность двух векторов
PyObject* VminusV(PyObject* a, PyObject *args)
{
    vector *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &vector_Type, &v, &vector_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be vector and vector.");
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

// скалярное произведение векторов
PyObject* VdotV(PyObject* a, PyObject *args)
{
    vector *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &vector_Type, &v, &vector_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be vector and vector.");
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

// векторное произведение для матрицы 3х3
PyObject* VxV(PyObject* a, PyObject *args)
{
    vector *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &vector_Type, &v, &vector_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be vector and vector.");
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

// произведение матрицы на число
PyObject* MxR(PyObject* a, PyObject *args)
{
    matrix* v;
    double r;
    if (!PyArg_ParseTuple(args, "O!d", &matrix_Type, &v, &r)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be matrix and double.");
        return NULL;
    }
    matrix* new_v = _new_matrix(v->n, v->m);
    for (int i = 0; i<v->n; ++i){
        for (int j = 0; j<v->m; ++j){
            set_mat_elem(new_v, i, j, get_mat_elem(v, i, j)*r);
        }
    }
    return new_v;
}

// сумма двух матриц
PyObject* MplusM(PyObject* a, PyObject *args)
{
    matrix *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &matrix_Type, &v, &matrix_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be matrix and matrix.");
        return NULL;
    }
    if ((v->n)!=(w->n) && (v->m)!=(w->m)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    matrix* new_v = _new_matrix(v->n, v->m);
    for (int i = 0; i<v->n; ++i){
        for (int j = 0; j<v->m; ++j){
            set_mat_elem(new_v, i, j, get_mat_elem(v, i, j)+get_mat_elem(w, i, j));
        }
    }
    return new_v;
}

// разность двух матриц
PyObject* MminusM(PyObject* a, PyObject *args)
{
    matrix *v, *w;
    if (!PyArg_ParseTuple(args, "O!O!", &matrix_Type, &v, &matrix_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be matrix and matrix.");
        return NULL;
    }
    if ((v->n)!=(w->n) && (v->m)!=(w->m)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    matrix* new_v = _new_matrix(v->n, v->m);
    for (int i = 0; i<v->n; ++i){
        for (int j = 0; j<v->m; ++j){
            set_mat_elem(new_v, i, j, get_mat_elem(v, i, j)-get_mat_elem(w, i, j));
        }
    }
    return new_v;
}

// произведение матрицы и вектора
PyObject* MxV(PyObject* a, PyObject *args)
{
    matrix *mat;
    vector* v;
    if (!PyArg_ParseTuple(args, "O!O!", &matrix_Type, &mat, &vector_Type, &v)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be matrix and vector.");
        return NULL;
    }
    if ((mat->m)!=(v->length)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    vector* new_v = _new_vector(mat->n);
    for (int i = 0; i<new_v->length; ++i){
        double res = 0;
        for (int j = 0; j<mat->m; ++j) res += get_mat_elem(mat, i, j) * get_v_elem(v, j);
        set_v_elem(new_v, i, res);
    }
    return new_v;
}

// произведение матриц
PyObject* MxM(PyObject* a, PyObject *args)
{
    matrix *v;
    matrix* w;
    if (!PyArg_ParseTuple(args, "O!O!", &matrix_Type, &v, &matrix_Type, &w)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be matrix and matrix.");
        return NULL;
    }
    if ((v->m)!=(w->n)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    matrix* new_m = _new_matrix(v->n, w->m);
    for (int i = 0; i<new_m->n; ++i){
        for (int j = 0; j<new_m->m; ++j){
            double res = 0;
            for (int k = 0; k<v->m; ++k) res += get_mat_elem(w, i, k) * get_v_elem(v, k, j);
            set_mat_elem(new_m, i, j, res);
        }
    }
    return new_m;
}

// матрица поворота на заданный угол относительно вектора
PyObject* MRot(PyObject* a, PyObject *args)
{
    vector *v;
    double al;
    if (!PyArg_ParseTuple(args, "O!d", &vector_Type, &v, &al)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be vector and double.");
        return NULL;
    }
    if (3!=(v->length)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    matrix* s = get_zero_mat(3, 3);
    set_mat_elem(s, 0, 0, 0);
    set_mat_elem(s, 0, 1, get_v_elem(v,2));
    set_mat_elem(s, 0, 2, -get_v_elem(v,1));
    set_mat_elem(s, 1, 0, -get_v_elem(v,2));
    set_mat_elem(s, 1, 1, 0);
    set_mat_elem(s, 1, 2, get_v_elem(v,0));
    set_mat_elem(s, 2, 0, get_v_elem(v,1));
    set_mat_elem(s, 2, 1, -get_v_elem(v,0));
    set_mat_elem(s, 2, 2, 0);
    matrix* new_m;
    PyObject* t1 = Py_BuildValue("(OO)", get_id_mat(3), MxR(a,Py_BuildValue("(OO)",s, Py_BuildValue("d",sin(al)))));
    new_m = MplusM(a, t1);
    matrix* ss = MxM(a, Py_BuildValue("(OO)",s,s));
    PyObject* t2 = Py_BuildValue("(OO)", new_m, MxR(a, Py_BuildValue("(Od)", ss, "d",1-cos(al))));
    new_m = MplusM(a, t2);
    return new_m;
}