#ifndef TTREE_H
#define TTREE_H

#include "figure.h"
#include <memory>
#include <iostream>

template <typename Q, typename O> class TTree {
 private:
  class Node {
  public:
    Q data;
    std::shared_ptr<Node> son;
    std::shared_ptr<Node> sibling;
    Node();
    Node(const O&);
    int itemsInNode;
  };

  std::shared_ptr<Node> root;

  void recRemByType(std::shared_ptr<Node>&, const int&);
  void recInsert(std::shared_ptr<Node>&, const O&);
  void recInorder(const std::shared_ptr<Node>&);
  void recRemLesser(std::shared_ptr<Node>&, const double&);
  void clear(std::shared_ptr<Node>&, std::shared_ptr<Node>&);
 public:
  TTree();

  void insert(const O&);
  void inorder(); 
  void removeByType(const int&);
  void removeLesser(const double&);
};

#include "TTree.hpp"
#endif
