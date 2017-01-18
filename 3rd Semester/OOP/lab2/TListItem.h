#ifndef TLISTITEM_H
#define TLISTITEM_H
#include "square.h"

class TListItem {
 public:
  TListItem(const Square& obj);
  TListItem(const TListItem& orig);

  TListItem* getNext();
  Square getItem() const;
  Square remove();
  void setNext(TListItem* item);
  
  ~TListItem(){};

 private:
  Square item;
  TListItem *next;
};

#endif
