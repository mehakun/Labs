#include "patricia.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <string>
#include <map>
#include <vector>

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

std::string generateRandomString(size_t length)
{
  const char* charmap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const size_t charmapLength = std::strlen(charmap);
  auto generator = [&](){ return charmap[rand()%charmapLength]; };
  std::string result;
  result.reserve(length);
  generate_n(back_inserter(result), length, generator);
  return result;
}

int main(void)
{
  TPatricia Test;
  std::vector<std::string> keys;
  std::vector<unsigned long long> values;
  unsigned int size = 10000;
  //  std::cin >> size;

  for(unsigned int i = 0; i < size; i++) {
    values.push_back(rand64bits());
    keys.push_back(generateRandomString(256));
  }
  //  start = clock();
  for (unsigned int i = 0; i < size; i++)
    Test.Insert(keys[i], values[i]);
  //  end = clock();
  /*
  std::cout << "Patricia insert time is: " 
            << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

  start = clock();
  for (unsigned int i = 0; i < size; i++)
    map.emplace(keys[i], values[i]);
  end = clock();
  std:: cout << "std::map insert time is: " 
             << (double)(end - start) / CLOCKS_PER_SEC << " seconds"<< std::endl;
  start = clock();
  */
  for (unsigned int i = 0; i < size; i++)
    Test.Delete(keys[i]);
  /*  end = clock();
  
  std::cout << "Patricia delete time is: " 
            << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

  start = clock();
  for (unsigned int i = 0; i < size; i++)
    map.erase(keys[i]);
  end = clock();
  std:: cout << "std::map delete time is: " 
             << (double)(end - start) / CLOCKS_PER_SEC << " seconds"<< std::endl;
  */
  return 0;
}
