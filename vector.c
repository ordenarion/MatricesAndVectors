#include "vector.h"

void vector_init(vector* v, int length)
{
    v->data = malloc(DSIZE * length);
    v->length = length;
}

void vector_free(vector* v)
{
    free(v->data);
    free(v);
}

vector* new_vector(int length)
{
    vector* v = malloc(sizeof(vector));
    vector_init(v, length);
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