
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    size_t rootIdx = 1;
    return rootIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    size_t leftChildIdx = (2 * currentIdx);
    return leftChildIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    size_t rightChildIdx = ((2 * currentIdx) + 1);
    return rightChildIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    size_t parentIdx = (currentIdx / 2);
    return parentIdx;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(_elems.size() > (2 * currentIdx)) {
      return true;
    }
    if(_elems.size() > ((2 * currentIdx) + 1)) {
      return true;
    }
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t rc = rightChild(currentIdx);
    size_t lc = leftChild(currentIdx);
    if(rc >= _elems.size() || higherPriority(_elems[lc], _elems[rc])) {
      return lc;
    }
    return rc;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx) == false) {
      return;
    }
    else {
      size_t temp = maxPriorityChild(currentIdx);
      if(higherPriority(_elems[temp], _elems[currentIdx])) {
        T tempElem = _elems[temp];
        _elems[temp] = _elems[currentIdx];
        _elems[currentIdx] = tempElem;
        heapifyDown(temp);
      }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    T temp = T();
    _elems.push_back(temp);
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    T temp = T();
    _elems.push_back(temp);
    size_t size = elems.size();
    for(size_t count = 0; count < size; count++) {
      _elems.push_back(elems[count]);
    }
    size_t idx = (_elems.size() - 1);
    while(idx > 0) {
      heapifyDown(idx);
      idx--;
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if(empty() == false) {
      T temp = _elems[1];
      size_t oldSize = (_elems.size() - 1);
      _elems[1] = _elems[oldSize];
      _elems.pop_back();
      heapifyDown(1);
      return temp;
    }
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    T temp = _elems[1];
    return temp;
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    size_t size = (_elems.size() - 1);
    heapifyUp(size);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    T oldElem = _elems[idx];
    _elems[idx] = elem;
    if(elem >= oldElem) {
      heapifyDown(idx);
      return;
    }
    heapifyUp(idx);
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size() - 1 > 0) {
      return false;
    }
    return true;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
