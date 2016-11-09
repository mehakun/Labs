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


template <typename T> TList<T>::TNode::TNode() {
  item = std::make_shared<T>();
  next = nullptr;
}

template <typename T> TList<T>::TNode::TNode(const std::shared_ptr<T>& obj) {
  item = obj;
  next = nullptr;
}

template <typename T> TList<T>::TList() {
  head = std::make_shared<TNode>();
  length = 0;
}

template <typename T> bool TList<T>::IsEmpty() const {
  return this->length == 0;
}

template <typename T> int TList<T>::GetLength() const {
  return this->length;
}

template <typename T> bool TList<T>::PushFront(const std::shared_ptr<T>& obj) {  
  auto Nitem = std::make_shared<TNode>(obj);
  std::swap(Nitem->next, head->next);
  std::swap(head->next, Nitem);
  length++;
  
  return true;
}

template <typename T> bool TList<T>::Push(const std::shared_ptr<T>& obj, int pos) {
  if (pos == 1 || length == 0)
    return PushFront(obj);
  if (pos < 0 || pos > length + 1)
    return false;

  auto iter = head->next;
  int i = 0;

  while (i < pos - 2) {
    iter = iter->next;
    i++;
  }

  auto Nitem = std::make_shared<TNode>(obj);
  std::swap(Nitem->next, iter->next);
  std::swap(iter->next, Nitem);
  length++;
  
  return true;
}

template <typename T> bool TList<T>::PopFront() {
  if (IsEmpty())
    return false;
  
  head->next = std::move(head->next->next);

  length--;
  
  return true;
}

template <typename T> bool TList<T>::Pop(int pos) {
  if (pos < 1 || pos > length || IsEmpty())
    return false;
  if (pos == 1)
    return PopFront();

  auto iter = head->next;
  int i = 0;

  while (i < pos - 2) {
    iter = iter->next;
    i++;
  }
  
  iter->next = std::move(iter->next->next);
  length--;

  return true;
}

template <typename T> auto TList<T>::TNode::GetNext() const {
  return this->next;
}

template <typename T> auto TList<T>::TNode::GetItem() const {
  return this->item;
}

template <typename A> std::ostream& operator<< (std::ostream& os, TList<A>& list) {
  if (list.IsEmpty()) {
    os << "The list is empty!" << std::endl;
    return os;
} 
  auto tmp = list.head->next;
  while (tmp != nullptr) {
    tmp->GetItem()->Print();
    tmp = tmp->GetNext();
  }
  
  return os;
}

#endif
