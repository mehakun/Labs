#ifndef TLIST_H
#define TLIST_H
#include "square.h"
#include "trap.h"
#include "pryam.h"
#include <memory>
#include <iostream>

class TList {
 private:
  class TNode {
  private:
  public:
    TNode();
    TNode(const std::shared_ptr<Figure>&);
    auto GetNext() const;
    auto GetItem() const;
    std::shared_ptr<Figure> item;
    std::shared_ptr<TNode> next;

  };
  int length;
  std::shared_ptr<TNode> head;
  
 public:
  TList();
  bool PushFront(const std::shared_ptr<Figure>&);
  bool Push(const std::shared_ptr<Figure>&, const int);
  bool PopFront();
  bool Pop(const int);
  bool IsEmpty() const;
  int GetLength() const;

  friend std::ostream& operator<< (std::ostream&, const TList&);
};

#endif
