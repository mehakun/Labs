#include "vector.h"
#include "sort.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;
unsigned rand256()
{
    static unsigned const limit = RAND_MAX - RAND_MAX % 256;
    unsigned result = rand();
    while ( result >= limit ) {
        result = rand();
    }
    return result % 256;
}

unsigned long long rand64bits()
{
    unsigned long long results = 0ULL;
    for ( int count = 8; count > 0; -- count ) {
        results = 256U * results + rand256();
    }
    return results;
}

int main(void)
{
  TVType tmp;
  TVector radix;
  TVector qsort;
  clock_t start;
  clock_t end;
  unsigned int size;
  cin >> size;
  CreateVector(&radix, 5);
  CreateVector(&qsort, 5);

  for(unsigned int i = 0; i < size; i++) {
    tmp.key = rand64bits();
    tmp.value = rand64bits();
    AddVector(&radix, tmp);
    AddVector(&qsort, tmp);
  }
  start = clock();
  RadixSort(radix.data, radix.size);
  end = clock();
  cout << fixed;
  cout << "My Radixsort time is: " << setprecision(4)
       << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

  start = clock();
  sort(qsort.data, qsort.data + qsort.size - 1,
       [](const TVType &a, const TVType &b) -> bool {
         return a.key > b.key;
       });
  end = clock();
  cout << "STL sort time is: " << setprecision(4)
       << (double)(end - start) / CLOCKS_PER_SEC << " seconds"<<endl;
  
  FreeVector(&radix);
  FreeVector(&qsort);
  
  return 0;
}
