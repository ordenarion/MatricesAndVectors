#include "vector.h"

// методы, которые будут доступны у объекта vector
PyMethodDef vector_methods[] = {
    {
        "print",
        print_vector,
        METH_VARARGS,
        "Print vector"
    },
    {
        "fill",
        fill_vector,
        METH_VARARGS,
        "Fill vector"
    },
    {
        "len",
        len,
        METH_VARARGS,
        "len of vector"
    },
    {NULL, NULL, 0, NULL}
};

// определение типа vector_Type
PyTypeObject vector_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "vector",
    .tp_basicsize = sizeof(vector),
    .tp_dealloc = (destructor)vector_free,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Vector object",
    .tp_methods = vector_methods,
};

// вспомогательный метод для создания вектора
vector* _new_vector(int length)
{
    vector* v = PyObject_NEW(vector, &vector_Type);
    vector_init(v, length);
    return v;
}

// метод инициализации вектора
void vector_init(vector* v, int length)
{
    v->data = malloc(DSIZE * length);
    v->length = length;
}

// метод очистки вектора
void vector_free(vector* v)
{
    free(v->data);
    Py_XDECREF(v);
    Py_TYPE(v)->tp_free((PyObject*)v);
}

// геттер элемента с индексом i
double get_v_elem(vector* v, int i)
{
    i = i%(v->length);
    return v->data[i];
}

// cеттер элемента с индексом i
double set_v_elem(vector* v, int i, double elem)
{
    i = i%(v->length);
    double old_elem = v->data[i];
    v->data[i] = elem;
    return old_elem;
}

// функция, выдающая вектор, заполненный случайными числами
vector* get_random_vec(int length, double l, double r)
{
    vector* v = _new_vector(length);
    for (int i = 0; i<length; ++i){
        double el = (double)rand() / (double)RAND_MAX * (r-l) + l;
        set_v_elem(v, i, el);
    }
    return v;
}

// функция, выдающая вектор, заполненный нулями
vector* get_zero_vec(int length)
{
    vector* v = _new_vector(length);
    for (int i = 0; i<length; ++i){
        set_v_elem(v, i, 0);
    }
    return v;
}

// далее методы инициализации объектов python
// -----------------------------------------------------------------------------------------------------------------
// нулевой вектор (по умолчанию будет нулевая)
vector* new_vector(PyObject *self, PyObject *args)
{
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    return get_zero_vec(n);
}

// случайный вектор
vector* rand_new_vector(PyObject *self, PyObject *args)
{
    int n;
    double l, r;
    if (!PyArg_ParseTuple(args, "idd", &n, &l, &r))
        return NULL;
    return get_random_vec(n, l, r);
}

// далее методы, доступные для py-объекта vector
// -----------------------------------------------------------------------------------------------------------------
// печать вектора
PyObject *print_vector(PyObject* a, PyObject *args)
{
    vector* v = (vector*)a;
    for (int i = 0; i<v->length; ++i) {
        printf("%*f", 10, get_v_elem(v, i));
    }
    printf("\n\n");
    Py_INCREF(Py_None);
    return Py_None;
}

// заполнение вектора из списка
PyObject *fill_vector(PyObject* a, PyObject *args)
{
    Py_INCREF(Py_None);
    vector* self = (vector*)a;
    PyObject *pList;
    PyObject *pItem;
    Py_ssize_t n;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pList)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
        return NULL;
    }
    n = PyList_Size(pList);
    if (n!=(self->length)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    const char* st = PyList_GetItem(pList, 0)->ob_type->tp_name;
    if (strcmp("float", st)!=0 && strcmp("int", st)!=0){
            PyErr_SetString(PyExc_TypeError, "parameter must be a int or float");
            return NULL;
    }
    if (strcmp("int", st)==0) {
        for (int i=0; i<n; i++) {
            pItem = PyList_GetItem(pList, i);
            int s = PyLong_AsLong(pItem);
            set_v_elem(self, i, s);
        }
    } else if (strcmp("float", st)==0) {
        for (int i=0; i<n; i++) {
            pItem = PyList_GetItem(pList, i);
            double s = PyFloat_AsDouble(pItem);
            set_v_elem(self, i, s);
        }
    }
    return Py_None;
}

// выдача размера вектора
PyObject* len(PyObject* self, PyObject *args)
{
    vector* v = (vector*)self;
    return Py_BuildValue("i", v->length);
}

