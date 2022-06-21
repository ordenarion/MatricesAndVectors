#include "main.h"

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

static PyModuleDef simple_module = {
    PyModuleDef_HEAD_INIT,
    "vectors_and_matrices",
    "doc",
    -1,
    own_methods
};

PyMODINIT_FUNC PyInit_module(void)
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
    return m;
}

static PyMethodDef vector_methods[] = {
    {
        "print",
        print_vector,
        METH_VARARGS,
        "Print vector"
    },
}

static PyMethodDef matrix_methods[] = {
    {
        "print",
        print_matrix,
        METH_VARARGS,
        "Print matrix"
    },
}

static PyMethodDef own_methods[] = {
    {
        "vector",
        new_column,
        METH_VARARGS,
        "New column"
    },
    {
        "matrix",
        new_table,
        METH_VARARGS,
        "New table"
    },
    {NULL, NULL, 0, NULL}
};