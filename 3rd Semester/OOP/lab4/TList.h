#ifndef TLIST_H
#define TLIST_H
#include <memory>
#include <iostream>

template <typename T> class TList {
 private:
  class TNode {
  private:
  public:
    TNode();
    TNode(const std::shared_ptr<T>&);
    auto GetNext() const;
    auto GetItem() const;
    std::shared_ptr<T> item;
    std::shared_ptr<TNode> next;

  };
  int length;
  std::shared_ptr<TNode> head;
  
 public:
  TList();
  bool PushFront(const std::shared_ptr<T>&);
  bool Push(const std::shared_ptr<T>&, const int);
  bool PopFront();
  bool Pop(const int);
  bool IsEmpty() const;
  int GetLength() const;

  template <typename A> friend std::ostream& operator<< (std::ostream&, const TList<A>&);
};

#include "TList.hpp"
#endif
