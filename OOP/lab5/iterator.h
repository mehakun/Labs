#ifndef TITERATOR_H
#define TITERATOR_H
#include <memory>

template <typename node, typename T>
  class TIterator {
 private:
  std::shared_ptr<node> nodePtr;
 public:
  TIterator(std::shared_ptr<node> n) {
    nodePtr = n;
  }

  std::shared_ptr<T> operator* () {
    return nodePtr.get();
  }

  std::shared_ptr<T> operator-> () {
    return nodePtr.get();
  }
  
  void operator ++ (){
    nodePtr = nodePtr->GetNext();
  }
  
  TIterator operator ++ (int) {
    TIterator iter(*this);
    ++(*this);
    return iter;
  }
  
  bool operator == (TIterator const& i) {
    return nodePtr == i.nodePtr;
  }
  
  bool operator != (TIterator const& i) {
    return !(*this == i);
  }
};


#endif
