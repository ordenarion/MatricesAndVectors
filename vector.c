#include "vector.h"

PyMethodDef vector_methods[] = {
    {
        "print",
        print_vector,
        METH_VARARGS,
        "Print vector"
    },
    {NULL, NULL, 0, NULL}
};

PyTypeObject vector_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "vector",
    .tp_basicsize = sizeof(vector),
    .tp_dealloc = (destructor)vector_free,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Vector object",
    .tp_methods = vector_methods,
};

vector* new_vector(PyObject *self, PyObject *args)
{
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    return get_zero_vec(n);
}

vector* _new_vector(int length)
{
    vector* v = PyObject_NEW(vector, &vector_Type);
    vector_init(v, length);
    return v;
}

void vector_init(vector* v, int length)
{
    v->data = malloc(DSIZE * length);
    v->length = length;
}

void vector_free(vector* v)
{
    free(v->data);
    Py_XDECREF(v);
    Py_TYPE(v)->tp_free((PyObject*)v);
}

double get_v_elem(vector* v, int i)
{
    i = i%(v->length);
    return v->data[i];
}

double set_v_elem(vector* v, int i, double elem)
{
    i = i%(v->length);
    double old_elem = v->data[i];
    v->data[i] = elem;
    return old_elem;
}

vector* get_random_vec(int length, int l, int r)
{
    vector* v = _new_vector(length);
    srand(time(NULL));
    for (int i = 0; i<length; ++i){
        double el = (double)rand() / (double)RAND_MAX * (r-l) + l;
        set_v_elem(v, i, el);
    }
    return v;
}

vector* get_zero_vec(int length)
{
    vector* v = _new_vector(length);
    for (int i = 0; i<length; ++i){
        set_v_elem(v, i, 0);
    }
    return v;
}

PyObject *print_vector(PyObject* a, PyObject *args)
{
    vector* v = (vector*)a;
    for (int i = 0; i<v->length; ++i) {
        printf("%*f", 10, get_v_elem(v, i));
    }
    printf("\n");
    Py_INCREF(Py_None);
    return Py_None;
}