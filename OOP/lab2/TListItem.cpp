#include "TListItem.h"
#include <iostream>

TListItem::TListItem(const Square& obj) {
  this->item = obj;
  this->next = nullptr;
}

TListItem::TListItem(const TListItem& orig) {
  this->item = orig.item;
  this->next = orig.next;
}

void TListItem::setNext(TListItem* item) {
  auto *old = this->next;
  this->next = item;
  item->next = old;
}

TListItem* TListItem::getNext() {
  return this->next;
}

Square TListItem::getItem() const {
  return this->item;
}

Square TListItem::remove() {
  auto *removed = this->next;
  auto item = removed->getItem();
  this->next = removed->getNext();
  delete removed;
  
  return item;
}
