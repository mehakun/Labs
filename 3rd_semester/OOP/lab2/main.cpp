#include "TList.h"
#include <iostream>

void menu(void) {
  std::cout << "1) Add square" << std::endl;
  std::cout << "2) Print list" << std::endl;
  std::cout << "3) Delete square from list" << std::endl;
  std::cout << "4) Exit" << std::endl;
}

int main(void) {
  TList list;
  int opt, index;
  Square tmp, item;

  do {
    menu();
    std::cin >> opt;
    switch(opt) {
    case 1:{
      std::cout << "Enter value and index" << std::endl;
      std::cin >> tmp >> index;
      if (list.push(tmp, index))
        std::cout << "Item was added" << std::endl;
      else
        std::cout << "Item was not added" << std::endl;
      break;
    }
    case 2:
      std::cout << list;
      break;
    case 3:{
      std::cout << "Enter index" << std::endl;
      std::cin >> index;
      item = list.pop(index);
      if (!(item == -1.0))
        std::cout << "Item was removed. It contained:"
                  << std::endl << item;
      else
        std::cout << "Item was not removed" << std::endl;
      break;
    }
    }
  } while(opt != 4);
  
    std::cout << "Bye!" << std::endl;
  return 0;
}
