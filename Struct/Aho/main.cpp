#include "AC.h"
#include <iostream>
#include <sstream>

int main(void) {
  std::vector< std::pair<int, int> > answer;
  std::vector<std::string> pattern;
  std::vector<unsigned long> textToSearch;
  std::string input, token;
  TFinitaAuto aho;
  
  std::getline(std::cin, input);
  std::stringstream ss(input);

  while (ss >> token) {
    pattern.emplace_back(std::string(token));
  }

  int lineCount = 1;
  int wordCount = 1;

  while (std::getline(std::cin, input)) {
    std::stringstream textSS (input);

    while (textSS >> token) {
      textToSearch.emplace_back(std::stoul(token));
      answer.emplace_back(std::make_pair(lineCount, wordCount));
      wordCount++;
    }

    lineCount++;
    wordCount = 1;
  }
  
  aho.Build(pattern);
  aho.Search(textToSearch, answer, pattern.size());

  return 0;
}
