#include "sort.h"
#include "vector.h"

void CountSort(TVType arr[], int size, unsigned long long num) {
  TVType *output = new TVType[size];
  int i;
  int ind;
  unsigned int counter[BASE] = {0};
  
  for (i = 0; i < size; i++) {
    counter[ (arr[i].key/num)%BASE ]++;
  }
  for (i = 1; i < BASE; i++) {
    counter[i] += counter[i - 1];
  }
  for (i = size - 1; i >= 0; i--) {
    ind = (arr[i].key/num)%BASE;
    output[counter[ind] - 1].key = arr[i].key;
    output[counter[ind] - 1].value = arr[i].value;
    counter[ind]--;
  }
  for (i = 0; i < size; i++) {
    arr[i].key = output[i].key;
    arr[i].value = output[i].value;
  }
  delete [] output;
}

void RadixSort(TVType arr[], int size) {
  unsigned long long max = arr[0].key;
  unsigned long long exp = 1;
  int length = 0;
  for (int j = 0; j < size; j++) {
    if (arr[j].key > max)
      max = arr[j].key;
  }
  while (max != 0) {
    max /= BASE;
    length++;
  }
  while (length-- > 0) {
    CountSort(arr, size, exp);
    exp *= BASE;
  }
}
