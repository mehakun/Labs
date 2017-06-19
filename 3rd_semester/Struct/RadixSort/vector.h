#ifndef VECTOR_H
#define VECTOR_H

typedef struct TVType {
  unsigned long long key;
  unsigned long long value;
} TVType;
typedef struct TVector {
  TVType *data;
  int capacity;
  int size;
} TVector;

void CreateVector(TVector*, int);
void FreeVector(TVector*);
void AddVector(TVector*, TVType);

#endif
