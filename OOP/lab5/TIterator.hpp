#ifdef TLIST_H
template <typename T> TList<T>::TIterator::TIterator(node n) {
  nodePtr = n;
}
    
template <typename T> std::shared_ptr<M> TList<T>::TIterator::operator* () {
  return nodePtr->GetItem();
}

template <typename T> std::shared_ptr<M> TList<T>::TIterator::operator-> () {
  return nodePtr->GetItem();
}
    
template <typename T> void TList<T>::TIterator::operator ++ () {
  nodePtr = nodePtr->GetNext();
}

/*  
    TIterator operator ++ (int) {
    TIterator iter(*this);
    ++(*this);
    return iter;
    }
*/

template <typename T> bool TList<T>::TIterator::operator == (TIterator const& i) {
  return nodePtr == i.nodePtr;
}

template <typename T> bool TList<T>::TIterator::operator != (TIterator const& i) {
  return !(*this == i);
}

#endif
