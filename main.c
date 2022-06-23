#include "main.h"


static PyMethodDef own_methods[] = {
    {
        "vector",
        new_vector,
        METH_VARARGS,
        "New column"
    },
    {
        "matrix",
        new_matrix,
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


