#include "main.h"

static PyMethodDef vector_methods[] = {
    {
        "print",
        print_vector,
        METH_VARARGS,
        "Print vector"
    },
};

static PyMethodDef matrix_methods[] = {
    {
        "print",
        print_matrix,
        METH_VARARGS,
        "Print matrix"
    },
};

static PyMethodDef own_methods[] = {
    {
        "vector",
        get_zero_vec,
        METH_VARARGS,
        "New column"
    },
    {
        "matrix",
        get_zero_mat,
        METH_VARARGS,
        "New table"
    },
    {NULL, NULL, 0, NULL}
};

static PyModuleDef simple_module = {
    PyModuleDef_HEAD_INIT,
    "vectors_and_matrices",
    "doc",
    -1,
    own_methods
};

PyMODINIT_FUNC PyInit_vectors_and_matrices(void)
{
    PyObject* mod;
    matrix_Type.tp_new = PyType_GenericNew;
    vector_Type.tp_new = PyType_GenericNew;
	if(PyType_Ready(&vector_Type) < 0 || PyType_Ready(&matrix_Type) < 0)
    	    return NULL;
    mod = PyModule_Create(&simple_module);
    if (mod==NULL)
        return NULL;

    Py_INCREF(&matrix_Type);
    Py_INCREF(&vector_Type);
    return mod;
}

static PyTypeObject matrix_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "matrix",
    .tp_basicsize = sizeof(matrix),
    .tp_dealloc = (destructor)matrix_free,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Matrix object",
    .tp_methods = matrix_methods,
};

static PyTypeObject vector_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "vector",
    .tp_basicsize = sizeof(vector),
    .tp_dealloc = (destructor)vector_free,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Vector object",
    .tp_methods = vector_methods,
};

matrix* new_matrix(PyObject* a, PyObject* args)
{
    int n, m;
    if (!PyArg_ParseTuple(args, "ii", &n, &m))
        return NULL;
    matrix* mat = PyObject_NEW(matrix, &matrix_Type);
    matrix_init(mat, n, m);
    return mat;
}

vector* new_vector(PyObject *self, PyObject *args)
{
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    vector* v = PyObject_NEW(vector, &vector_Type);
    vector_init(v, n);
    return v;
}