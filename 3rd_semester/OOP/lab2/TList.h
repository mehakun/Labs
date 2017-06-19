#ifndef TLIST_H
#define TLIST_H
#include "square.h"
#include "TListItem.h"

class TList {
 public:
  TList();
  TList(const TList& orig);
  TList(Square& item);

  bool push(Square &obj, int ind);
  bool pushLast(Square &obj);
  bool pushFirst(Square &obj);
  const bool empty() const;
  int getLength();
  TListItem* getHead();
  Square pop(int ind);
  Square popFirst();
  Square popLast();
  friend std::ostream& operator<<(std::ostream& os, const TList& list);
  ~TList();

 private:
  int length;
  TListItem *head;  
};
#endif
