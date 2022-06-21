#include "vector.h"

void vector_init(vector* v, int length)
{
    v->data = malloc(DSIZE * length);
    v->length = length;
}

void vector_free(vector* v)
{
    free(v->data);
    Py_XDECREF(v);
    Py_TYPE(self)->tp_free((PyObject*)v);
    free(v);

}

static PyObject* new_vector(PyObject *self, PyObject *args)
{
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    vector* v = PyObject_NEW(vector, &vector_Type);
    vector_init(v, n);
    return v;
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
    vector* v = new_vector(length);
    srand(time(NULL));
    for (int i = 0; i<length; ++i){
        double el = (double)rand() / (double)RAND_MAX * (r-l) + l;
        set_v_elem(v, i, el);
    }
    return v;
}

vector* get_zero_vec(int length)
{
    vector* v = new_vector(length);
    for (int i = 0; i<length; ++i){
        set_v_elem(v, i, 0);
    }
    return v;
}

static PyObject *print_vector(PyObject* a)
{
    vector* v = (vector*)a;
    for (int i = 0; i<v->length; ++i) {
        printf("%*f", 10, get_v_elem(v, i));
    }
}