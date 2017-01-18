#include "SuffTree.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <sstream>

unsigned long _LongRand () {

  unsigned char MyBytes[4];
  unsigned long MyNumber = 0;
  unsigned char * ptr = (unsigned char *) &MyNumber;

  MyBytes[0] = rand() % 256; //0-255
  MyBytes[1] = rand() % 256; //256 - 65535
  MyBytes[2] = rand() % 256; //65535 -
  MyBytes[3] = rand() % 256; //16777216
  
  memcpy (ptr+0, &MyBytes[0], 1);
  memcpy (ptr+1, &MyBytes[1], 1);
  memcpy (ptr+2, &MyBytes[2], 1);
  memcpy (ptr+3, &MyBytes[3], 1);

  return(MyNumber);
}

std::string generateRandomString(size_t length)
{
  const char* charmap = "qwertyuiopasdfghjklzxcvbnm";
  const size_t charmapLength = std::strlen(charmap);
  auto generator = [&](){ return charmap[rand()%charmapLength]; };
  std::string result;
  result.reserve(length);
  generate_n(back_inserter(result), length, generator);
  return result;
}

int main(void)
{
  TSuffTree tree;
  clock_t start, end;
  size_t size, length;
  std::string pattern;
  std::string text;
  std::cin >> size >> length;

  pattern = generateRandomString(size);
  text = generateRandomString(length);
  std::vector<int> ms (text.size(), 0);
  
  start = clock();
  for (const auto& c: pattern) {
    tree.AddLetter(c);
  }
  tree.SetMs(ms, text);
  end = clock();

  std::cout << "Stat search time is: " 
            << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;


  start = clock();
  for (size_t i = 0; i < text.size(); i++) {
    text.find(pattern, i);
  }  
  end = clock();
  std:: cout << "std::string::find search time is: " 
             << (double)(end - start) / CLOCKS_PER_SEC << " seconds"<< std::endl;

  return 0;
}
