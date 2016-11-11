#ifndef TLIST_H
#define TLIST_H
#include <memory>
#include <iostream>
//#include "iterator.h"

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

  template <typename node, typename M>
    class TIterator {
  private:
    node nodePtr;
  public:
    TIterator(node n) {
      nodePtr = n;
    }
    
    std::shared_ptr<M> operator* () {
      return nodePtr->GetItem();
    }

    std::shared_ptr<M> operator-> () {
      return nodePtr->GetItem();
    }
    
    void operator ++ () {
      nodePtr = nodePtr->GetNext();
    }
    /*  
    TIterator operator ++ (int) {
      TIterator iter(*this);
      ++(*this);
      return iter;
    }
    */
    bool operator == (TIterator const& i) {
      return nodePtr == i.nodePtr;
    }
  
    bool operator != (TIterator const& i) {
      return !(*this == i);
    }
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

  TIterator<std::shared_ptr<TNode>, T> begin() {return TIterator<std::shared_ptr<TNode>, T>(head->next);};
  TIterator<std::shared_ptr<TNode>, T> end() {return TIterator<std::shared_ptr<TNode>, T>(nullptr);};

  template <typename A> friend std::ostream& operator<< (std::ostream&, TList<A>&);
};

#include "TList.hpp"
#include "TIterator.hpp"
#endif
