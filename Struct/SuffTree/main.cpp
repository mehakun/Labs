#include <iostream>
#include "SuffTree.h"

int main(void) {
  std::string pattern;
  std::string text;
  TSuffTree tree;
  std::cin >> pattern;
  
  for (const auto& i: pattern) {
    tree.AddLetter(i);
  }
  
  while (std::cin >> text) {
    std::vector<int> ms (text.size(), 0);
    tree.SetMs(ms, text);
  }
  
  return 0;
}
