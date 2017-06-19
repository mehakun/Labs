#include "TList.h"
#include <iostream>
#include "square.h"
#include "trap.h"
#include "pryam.h"
#include "TTree.h"

void menu(void) {
  std::cout << "1) Add item" << std::endl;
  std::cout << "2) Print" << std::endl;
  std::cout << "3) Delete by criteria" << std::endl;
  std::cout << "4) Exit" << std::endl;
}

int main(void) {
  TTree<TList<Figure>, std::shared_ptr<Figure> > tree;
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
        std::cout << "Enter value" << std::endl;
        std::cin >> tmp1;
        tree.insert(std::make_shared<Square>(tmp1));
        std::cout << "Item was added" << std::endl;
        break;
      } else if (index == 2) {
        std::cout << "Enter value" << std::endl;
        tmp2.setParams(std::cin);
        tree.insert(std::make_shared<Trap>(tmp2));
        std::cout << "Item was added" << std::endl;
        break;
      } else if (index == 3) {
        std::cout << "Enter value" << std::endl;
        tmp3.setParams(std::cin);
        tree.insert(std::make_shared<Pryam>(tmp3));
        std::cout << "Item was added" << std::endl;
        break;
      } else {
        std::cout << "derp" << std::endl;
        break;
      }
    }
    case 2:
      tree.inorder();
      break;
    case 3:{
      std::cout << "Enter criteria" << std::endl;
      std::cout << "1) by type\n2) lesser than square\n";
      std::cin >> index;
      if (index == 1) {
        std::cout << "1) square\n2) trap\n3) pryam\n";
        std::cout << "Enter type" << std::endl;
        std::cin >> index;
        tree.removeByType(index);
      } else if (index == 2) {
        double sqr = 0.0;
        std::cout << "Enter square" << std::endl;
        std::cin >> sqr;
        tree.removeLesser(sqr);
      } else {
        break;
      }
      break;
    }
    }
  } while(opt != 4);
  
    std::cout << "Bye!" << std::endl;
  return 0;
}
