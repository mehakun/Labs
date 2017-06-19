#include "TList.h"
#include <iostream>

TList::TList() {
  head = nullptr;
  length = 0;
}

TList::TList(Square& item) {
  head = new TListItem(item);
  length = 1;
}

TList::TList(const TList& orig) {
  head = orig.head;
}

TListItem* TList::getHead() {
  return this->head;
}

bool TList::push(Square &obj, int ind) {
  if (ind > this->getLength() || ind < 0) {
    std::cout << "change index(push)" << std::endl;
    return false;
  }
  if (this->empty()) {
    auto* newItem = new TListItem(obj);
    this->head = newItem;
    return true;
  }
  
  if (ind == 0) {
    this->pushFirst(obj);
    return true;
  }

  if (ind == this->getLength()) {
    this->pushLast(obj);
    return true;
  }
  
  auto* newItem = new TListItem(obj);
  auto* tmp = this->head;
  int i = 0;
  
  while (i < ind - 2) {
    tmp = tmp->getNext();
    i++;
  }
  
  tmp->setNext(newItem);

  return true;
}

bool TList::pushLast(Square &obj) {
  auto *newItem = new TListItem(obj);
  auto *tmp = this->head;
  
  while (tmp->getNext() != nullptr) {
    tmp = tmp->getNext();
  }
  tmp->setNext(newItem);
  return true;
}

bool TList::pushFirst(Square &obj) {
  auto *newItem = new TListItem(obj);
  auto *oldHead = this->head;

  this->head = newItem;
  this->head->setNext(oldHead);
  return true;
}

int TList::getLength() {
  int size = 0;
  auto *tmp = this->head;
  while (tmp != nullptr) {
    size++;
    tmp = tmp->getNext();
  }

  return size;
}

const bool TList::empty() const{
  return head == nullptr;
}

Square TList::pop(int ind) {
  if (ind > this->getLength() || ind < 0 || this->empty()) {
    std::cout << "change index(pop)" << std::endl;
    return Square(-1);
  }
  Square res;
  if (ind == 1) {
    res = this->popFirst();
    return res;
  }

  if (ind == this->getLength()) {
    res = this->popLast();
    return res;
  }

  auto* tmp = this->head;
  int i = 0;
  while (i < ind - 2) {
    tmp = tmp->getNext();
    i++;
  }
  res = tmp->remove();
  
  return res;
}

Square TList::popFirst() {
  if (this->empty()) {
    std::cout << "The list is empty" << std::endl;
    return Square(-1);
  }
  if (this->getLength() == 1) {
    auto res = this->head->getItem();
    delete this->head;
    this->head = nullptr;
    return res;
  }

  auto *removed = this->head;
  auto res = removed->getItem();
  this->head = this->head->getNext();

  return res;
}

Square TList::popLast() {
  if (this->empty()) {
    std::cout << "The list is empty" << std::endl;
    return Square(-1);
  }
  if (this->getLength() == 1) {
    auto res = this->head->getItem();
    delete this->head;
    this->head = nullptr;
    return res;
  }
  
  auto *tmp = this->head;
  while (tmp->getNext()->getNext() != nullptr) {
    tmp = tmp->getNext();
  }

  auto res = tmp->remove();

  return res;
}

std::ostream& operator<<(std::ostream& os, const TList& list) {
  if (list.empty()) {
    os << "The list is empty!" << std::endl;
    return os;
  } 
  
  auto *tmp = list.head;
  while(tmp != nullptr) {
    os << tmp->getItem();
    tmp = tmp->getNext();
  }

  return os;
}

TList::~TList() {
  auto *tmp = head;

  while (head != nullptr) {
    head = head->getNext();
    delete tmp;
    tmp = head;
  }
}
