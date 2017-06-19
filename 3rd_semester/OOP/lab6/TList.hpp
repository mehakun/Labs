#ifdef TLIST_H
template <typename T> TList<T>::TNode::TNode() {
  item = std::shared_ptr<T>();
  next = nullptr;
}

template <typename T> TList<T>::TNode::TNode(const std::shared_ptr<T>& obj) {
  item = obj;
  next = nullptr;
}

template <typename T> TAllocator TList<T>::TNode::nodeAllocator(sizeof(TList<T>::TNode), 100);

template <typename T> void* TList<T>::TNode::operator new(size_t size) {
  return nodeAllocator.allocate();
}

template <typename T> void TList<T>::TNode::operator delete(void* ptr) {
  nodeAllocator.deallocate(ptr);
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

template <typename A> std::ostream& operator<< (std::ostream& os, const TList<A>& list) {
  if (list.IsEmpty()) {
    os << "The list is empty!" << std::endl;
    return os;
} 

  auto tmp = list.head->GetNext();
  while(tmp != nullptr) {
    tmp->GetItem()->Print();
    tmp = tmp->GetNext();
  }
  
  return os;
}

#endif
