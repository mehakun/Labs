#include "TList.h"

TList::TNode::TNode() {
  item = std::make_shared<Square>();
  next = nullptr;
}

TList::TNode::TNode(const std::shared_ptr<Figure>& obj) {
  item = obj;
  next = nullptr;
}

TList::TList() {
  head = std::make_shared<TNode>();
  length = 0;
}

bool TList::IsEmpty() const {
  return this->length == 0;
}

int TList::GetLength() const {
  return this->length;
}

bool TList::PushFront(const std::shared_ptr<Figure>& obj) {  
  auto Nitem = std::make_shared<TNode>(obj);
  std::swap(Nitem->next, head->next);
  std::swap(head->next, Nitem);
  length++;
  
  return true;
}

bool TList::Push(const std::shared_ptr<Figure>& obj, int pos = 1) {
  if (pos == 1 || length == 0)
    return PushFront(obj);
  if (pos < 0 || pos > length)
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

bool TList::PopFront() {
  if (IsEmpty())
    return false;
  
  head->next = std::move(head->next->next);

  length--;
  
  return true;
}

bool TList::Pop(int pos = 1) {
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

auto TList::TNode::GetNext() const {
  return this->next;
}

auto TList::TNode::GetItem() const {
  return this->item;
}

std::ostream& operator<< (std::ostream& os, const TList& list) {
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
