#include "TList.h"
#include <iostream>
#include "square.h"
#include "trap.h"
#include "pryam.h"
#include "TTree.h"
#include <random>

int main(void) {
  TList<Figure> list;
  typedef std::function<void(void)> command;
  TTree<std::shared_ptr<command> > tree(4);
  command cmdInsert = [&]() {
    std::cout << "Command: Insert" << std::endl;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 10);
    for (int i = 0; i < 10; i++) {
      int side = distribution(generator);
      if ((side % 2) == 0) {
        list.PushFront(std::make_shared<Trap>(Trap(side, side, side, side)));
      } else if((side % 3) == 0) {
        list.PushFront(std::make_shared<Pryam>(Pryam(side, side + 1)));
      } else {
        list.PushFront(std::make_shared<Square>(Square(side)));
      }
    }
  };
  command cmdPrint = [&]() {
    std::cout << "Command: Print" << std::endl;
    for (const auto& i : list) {
      i->Print();
    }
  };
  command cmdRemove = [&]() {
    std::cout << "Command: Remove" << std::endl;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(1.0, 150.0);
    double sqr = distribution(generator);
    std::cout << "Lesser than " << sqr << std::endl;
    for (int i = 0; i < 10; i++) {
      auto iter = list.begin();
      
      for (int k = 0; k < list.GetLength(); k++) {
        if (iter->getSquare() < sqr) {
          list.Pop(k + 1);
          break;
        }
        ++iter;
      }
    }
  };
  
  tree.insert(std::shared_ptr<command>(&cmdInsert, [](command*){}));
  tree.insert(std::shared_ptr<command>(&cmdPrint, [](command*){}));
  tree.insert(std::shared_ptr<command>(&cmdRemove, [](command*){}));
  tree.insert(std::shared_ptr<command>(&cmdPrint, [](command*){}));              
  tree.inorder();
  
  return 0;
}

