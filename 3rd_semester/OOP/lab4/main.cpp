#include "TList.h"
#include <iostream>
#include "figure.h"
#include "pryam.h"
#include "trap.h"
#include "square.h"

void menu(void) {
  std::cout << "1) Add item to list" << std::endl;
  std::cout << "2) Print list" << std::endl;
  std::cout << "3) Delete item from list" << std::endl;
  std::cout << "4) Exit" << std::endl;
}

int main(void) {
  TList<Figure> list;
  int opt, index;
  Square tmp1;
  Trap tmp2;
  Pryam tmp3;

  do {
    menu();
    std::cin >> opt;
    switch(opt) {
    case 1:{
      std::cout << "Enter 1 if square, 2 if trap, 3 if pryam" << std::endl;
      std::cin >> index;
      if (index == 1) {
        std::cin >> tmp1 >> index;
        if (list.Push(std::make_shared<Square>(tmp1), index))
          std::cout << "Item was added" << std::endl;
        else
          std::cout << "Item was not added" << std::endl;
        break;
      } else if (index == 2) {
        std::cout << "Enter value and index" << std::endl;
        tmp2.setParams(std::cin);
        std::cin >> index;
        if (list.Push(std::make_shared<Trap>(tmp2), index))
          std::cout << "Item was added" << std::endl;
        else
          std::cout << "Item was not added" << std::endl;
        break;
      } else if (index == 3) {
        std::cout << "Enter value and index" << std::endl;
        tmp3.setParams(std::cin);
        std::cin >> index;
        if (list.Push(std::make_shared<Pryam>(tmp3), index))
          std::cout << "Item was added" << std::endl;
        else
          std::cout << "Item was not added" << std::endl;
        break;
      } else {
        std::cout << "derp" << std::endl;
        break;
      }
    }
    case 2:
      std::cout << list;
      break;
    case 3:{
      std::cout << "Enter index" << std::endl;
      std::cin >> index;
      if (list.Pop(index))
        std::cout << "Item was removed" << std::endl;
      else
        std::cout << "Item was not removed" << std::endl;
      break;
    }
    }
  } while(opt != 4);
  
    std::cout << "Bye!" << std::endl;
  return 0;
}
