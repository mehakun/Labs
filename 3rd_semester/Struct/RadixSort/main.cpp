#include "vector.h"
#include "sort.h"
#include <iostream>
using namespace std;

int main(void)
{
  TVType tmp;
  TVector v;
  int i;
  
  CreateVector(&v, 5);

  while((cin >> tmp.key) && (cin >> tmp.value)) {
    AddVector(&v, tmp);
  }
  RadixSort(v.data, v.size);
  for(i = 0; i < v.size; i++) {
    cout << v.data[i].key << "\t" << v.data[i].value << endl;
  }
  FreeVector(&v);
  
  return 0;
}
