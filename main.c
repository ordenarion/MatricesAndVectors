#include "main.h"


static PyMethodDef own_methods[] = {
    { "vector", new_vector, METH_VARARGS, "New vector" },
    { "matrix", new_matrix, METH_VARARGS, "New matrix" },
    { "rand_vector", rand_new_vector, METH_VARARGS, "New vector" },
    { "rand_matrix", rand_new_matrix, METH_VARARGS, "New matrix" },
    { "eye", eye, METH_VARARGS, "Identity matrix"  },

    { "norm", norm, METH_VARARGS, "norm matrix"  },
    { "VxR", VxR, METH_VARARGS, "VxR"  },
    { "VplusV", VplusV, METH_VARARGS, "VplusV"  },
//    { "VminusV", VminusV, METH_VARARGS, "VminusV"  },
//    { "VdotV", VdotV, METH_VARARGS, "VdotV"  },
//    { "VxV", VxV, METH_VARARGS, "VxV"  },
//    { "MxR", MxR, METH_VARARGS, "MxR"  },
//    { "MplusM", MplusM, METH_VARARGS, "MplusM"  },
//    { "MminusM", MminusM, METH_VARARGS, "MminusM"  },
//    { "MxV", MxV, METH_VARARGS, "MxV"  },
//    { "MxM", MxM, METH_VARARGS, "MxM"  },
//    { "MRot", MRot, METH_VARARGS, "MRot"  },
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


