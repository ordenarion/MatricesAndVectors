#include "matrix.h"

// методы, которые будут доступны у объекта matrix
PyMethodDef matrix_methods[] = {
    {
        "print",
        print_matrix,
        METH_VARARGS,
        "Print matrix"
    },
    {
        "fill",
        fill_matrix,
        METH_VARARGS,
        "Fill matrix"
    },
    {
        "shape",
        shape,
        METH_VARARGS,
        "shape of matrix"
    },
    {
        "get",
        get_m,
        METH_VARARGS,
        "getter of matrix"
    },
    {
        "set",
        set_m,
        METH_VARARGS,
        "setter of matrix"
    },
    {NULL, NULL, 0, NULL}
};

// определение типа matrix_Type
PyTypeObject matrix_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "matrix",
    .tp_basicsize = sizeof(matrix),
    .tp_dealloc = (destructor)matrix_free,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Matrix object",
    .tp_methods = matrix_methods,
};

// вспомогательный метод для создания матрицы
matrix* _new_matrix(int n, int m)
{
    matrix* mat = PyObject_NEW(matrix, &matrix_Type);
    matrix_init(mat, n, m);
    return mat;
}

// метод инициализации матрицы
void matrix_init(matrix* mat, int n, int m)
{
    mat->data = malloc(DSIZE * n * m);
    mat->n = n;
    mat->m = m;
}

// метод очистки матрицы
void matrix_free(matrix* mat)
{
    free(mat->data);
    Py_XDECREF(mat);
    Py_TYPE(mat)->tp_free((PyObject*)mat);
}

// геттер элемента с индексами i и j
double get_mat_elem(matrix* mat, int i, int j)
{
    i = i%(mat->n);
    j = j%(mat->m);
    return mat->data[i*(mat->m) + j];
}
// cеттер элемента с индексами i и j
double set_mat_elem(matrix* mat, int i, int j, double elem)
{
    i = i%(mat->n);
    j = j%(mat->m);
    double old_elem = mat->data[i*(mat->m) + j];
    mat->data[i*(mat->m) + j] = elem;
    return old_elem;
}

// функция, выдающая матрицу, заполненную случайными числами
matrix* get_random_mat(int n, int m, double l, double r)
{
    matrix* mat = _new_matrix(n, m);
    for (int i = 0; i<n; ++i)
        for (int j = 0; j<m; ++j){
            double el = (double)rand() / (double)RAND_MAX * (r-l) + l;
            set_mat_elem(mat, i, j, el);
        }
    return mat;
}

// функция, выдающая матрицу, заполненную нулями
matrix* get_zero_mat(int n, int m)
{
    matrix* mat = _new_matrix(n, m);
    for (int i = 0; i<n; ++i)
        for (int j = 0; j<m; ++j){
            set_mat_elem(mat, i, j, 0);
        }
    return mat;
}
// функция, выдающая единичную матрицу
matrix* get_id_mat(int n)
{
    matrix* mat = get_zero_mat(n, n);
    for (int i = 0; i<n; ++i) set_mat_elem(mat, i, i, 1);
    return mat;
}

// далее методы инициализации объектов python
// -----------------------------------------------------------------------------------------------------------------
// нулевая матрица (по умолчанию будет нулевая)
matrix* new_matrix(PyObject* a, PyObject* args)
{
    int n, m;
    if (!PyArg_ParseTuple(args, "ii", &n, &m))
        return NULL;
    return get_zero_mat(n, m);
}

// случайная матрица
matrix* rand_new_matrix(PyObject* a, PyObject* args)
{
    int n, m;
    double l, r;
    if (!PyArg_ParseTuple(args, "iidd", &n, &m, &l, &r))
        return NULL;
    return get_random_mat(n, m, l, r);
}

// единичная матрица
matrix* eye(PyObject* a, PyObject* args)
{
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    return get_id_mat(n);
}

// далее методы, доступные для py-объекта matrix
// -----------------------------------------------------------------------------------------------------------------
// печать матрицы
PyObject *print_matrix(PyObject* a, PyObject *args)
{
    matrix* v = (matrix*)a;
    for (int i = 0; i<v->n; ++i){
        for (int j = 0; j<v->m; ++j) {
            printf("%*f", 10, get_mat_elem(v, i, j));
        }
        printf("\n");
    }
    printf("\n");
    Py_INCREF(Py_None);
    return Py_None;
}

// заполнение матрицы из списка списков
PyObject *fill_matrix(PyObject* a, PyObject *args)
{
    Py_INCREF(Py_None);
    matrix* self = (matrix*)a;
    PyObject *pList;
    PyObject *pItem;
    Py_ssize_t n, m;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pList)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
        return NULL;
    }
    n = PyList_Size(pList);
    if (n!=(self->n)) {
        PyErr_SetString(PyExc_TypeError, "Invalid size");
        return NULL;
    }
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, PyList_GetItem(pList, 0))) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
        return NULL;
    }
    for (int i = 0; i<n; ++i){
        m = PyList_Size(PyList_GetItem(pList, i));
        if (m!=(self->m)) {
            PyErr_SetString(PyExc_TypeError, "Invalid size");
            return NULL;
        }
        const char* st = PyList_GetItem(PyList_GetItem(pList, i), 0)->ob_type->tp_name;
        if (strcmp("float", st)!=0 && strcmp("int", st)!=0){
            PyErr_SetString(PyExc_TypeError, "parameter must be a int or float");
            return NULL;
        }
        if (strcmp("int", st)==0) {
            for (int j=0; j<m; j++) {
                pItem = PyList_GetItem(PyList_GetItem(pList, i), j);
                int s = PyLong_AsLong(pItem);
                set_mat_elem(self, i, j, s);
            }
        } else if (strcmp("float", st)==0) {
            for (int j=0; j<m; j++) {
                pItem = PyList_GetItem(PyList_GetItem(pList, i), j);
                double s = PyFloat_AsDouble(pItem);
                set_mat_elem(self, i, j, s);
            }
        }
    }
    return Py_None;
}

// выдача размеров матрицы
PyObject *shape(PyObject* self, PyObject *args)
{
    matrix* mat = (matrix*)self;
    return Py_BuildValue("(ii)", mat->n, mat->m);
}

// выдача элемента по индексу
PyObject* get_m(PyObject* self, PyObject *args)
{
    int i, j;
    if (!PyArg_ParseTuple(args, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be int.");
        return NULL;
    }
    matrix* v = (matrix*)self;
    return Py_BuildValue("d", get_mat_elem(v, i, j));
}

// установить заданный элемент по индексу
PyObject* set_m(PyObject* self, PyObject *args)
{
    int i, j;
    double d;
    if (!PyArg_ParseTuple(args, "iid", &i, &j, &d)) {
        PyErr_SetString(PyExc_TypeError, "parameters must be int, int, double.");
        return NULL;
    }
    matrix* v = (matrix*)self;
    double oldv = set_mat_elem(v, i, j, d);
    return Py_BuildValue("d", oldv);
}