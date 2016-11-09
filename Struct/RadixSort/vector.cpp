#include "vector.h"
#include <cstdlib>

void CreateVector(TVector *v, int space) {
  v->data = (TVType*)malloc(sizeof(TVType) * space);
  v->size = 0;
  v->capacity = space;
}

void FreeVector(TVector *v) {
  free(v->data);
}

void AddVector(TVector *v, TVType item) {
  if (v->size == v->capacity) {
    v->capacity *= 2;
    v->data = (TVType*)realloc(v->data, sizeof(TVType) * v->capacity);
  }

  v->data[v->size++] = item;
  
}
