#include "BigInt.h"
#include <iostream>

int main(void) {
  std::string firstOp,
    secondOp,
    token;

  while (std::cin >> firstOp >> secondOp >> token) {
    TBigInt first(firstOp);
    TBigInt second(secondOp);
    
    if (token == "+") {
      try {
        TBigInt result = first + second;
        result.Print();
      } catch (const std::exception& e) {
        std::cout << "Error\n";
      }
    } else if (token == "-") {
      try {
        TBigInt result = first - second;
        result.Print();        
      } catch (const std::exception& e) {
        std::cout << "Error\n";
      }

    } else if (token == "/") {
      try {
        TBigInt result = first / second;
        result.Print();
      } catch (const std::exception& e) {
        std::cout << "Error\n";
      }
    } else if (token == "*") {
      try {
        TBigInt result = first * second;
        result.Print();
      } catch (const std::exception& e) {
        std::cout << "Error\n";
      }
    } else if (token == "^") {
      try {
        TBigInt result = first ^ second;
        result.Print();
      } catch (const std::exception& e) {
        std::cout << "Error\n";
      }
    } else if (token == ">") {
      std::cout << (first > second ? "true" : "false") << "\n";
    } else if (token == "<") {
      std::cout << (first < second ? "true" : "false") << "\n";
    } else if (token == "=") {
      std::cout << (first == second ? "true" : "false")<< "\n";
    } else {
      std::cout << "Error\n";
    }
    
  }
  
  return 0;
}
