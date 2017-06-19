#include "AC.h"
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
  const char* charmap = "0123456789 ";
  const size_t charmapLength = std::strlen(charmap);
  auto generator = [&](){ return charmap[rand()%charmapLength]; };
  std::string result;
  result.reserve(length);
  generate_n(back_inserter(result), length, generator);
  return result;
}

int main(void)
{
  clock_t start, end;
  size_t size, length;
  TFinitaAuto ac;
  std::string derp;
  std::string token;
  std::vector<std::string> pattern;
  std::vector<unsigned long> textToSearch;
  std::string text;
  std::vector< std::pair<int, int> > answer;
  std::cin >> size >> length;

  derp = generateRandomString(size);
  text = generateRandomString(length);

  std::stringstream ss(derp);

  for (size_t i = 0; i < size; i++) {
    pattern.emplace_back(std::to_string(_LongRand()));
  }

  int lineCount = 1;
  int wordCount = 1;

  std::stringstream textSS (text);
  
  for (size_t i = 0; i < length; i++) {
    textToSearch.emplace_back(_LongRand());
    answer.emplace_back(std::make_pair(lineCount, wordCount));
    wordCount++;
  }

  start = clock();
  ac.Build(pattern);
  ac.Search(textToSearch, answer, pattern.size());
  end = clock();

  std::cout << "Aho-Corasick search time is: " 
            << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;


  start = clock();
  for (const auto& string : pattern) {
    auto it = std::find(textToSearch.begin(), textToSearch.end(), std::stoul(string));
  }  
  end = clock();
  std:: cout << "std::find search time is: " 
             << (double)(end - start) / CLOCKS_PER_SEC << " seconds"<< std::endl;

  return 0;
}
