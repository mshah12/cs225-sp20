/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include <iostream>
template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  ListIterator beginning = List<T>::ListIterator(head_);
  return beginning;
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  if(tail_ == NULL) {
    return NULL;
  }
  ListIterator onePastEnd = List<T>::ListIterator(tail_->next);
  return onePastEnd;
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if(head_ == NULL) {
    return;
  }
  ListNode *curr = head_;
  ListNode *temp;
  while(curr->next != NULL) {
    temp = curr->next;
    delete curr;
    length_--;
    curr = temp;
  }
  delete curr;
  length_--;
  return;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  newNode->prev = NULL;
  if(head_ != NULL) {
    head_->prev = newNode;
    newNode->next = head_;
  }
  if(tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  length_++;
  return;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  newNode->next = NULL;
  if(tail_ != NULL) {
    tail_->next = newNode;
  }
  if(head_ == NULL) {
    head_ = newNode;
  }
  newNode->prev = tail_;
  tail_ = newNode;
  length_++;
  return;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode *curr = start;
  ListNode* temp;
  if(curr == NULL) {
    return NULL;
  }
  if(length_ <= splitPoint) {
    return NULL;
  }
  if(splitPoint == 0) {
    return head_;;
  }
  for(int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  if(curr == NULL) {
    return NULL;
  }
  else {
    temp = curr->prev;
    curr->prev = NULL;
    tail_ = temp;
    tail_->next = NULL;
    return curr;
  }
  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  int count = 0;
  int temp = 0;
  ListNode *curr = head_;
  int multiples = (length_ / 3);
  if(length_ < 3) {
    return;
  }
  while(count < multiples) {
    ListNode *first = curr;
    ListNode *second = curr->next;
    ListNode *third = curr->next->next;
    if(first->prev != NULL) {
      first->prev->next = second;
    }
    if(third->next != NULL) {
      third->next->prev = first;
    }
    second->prev = first->prev;
    first->next = third->next;
    first->prev = third;
    second->next = third;
    third->next = first;
    third->prev = second;
    if(temp == 0) {
      head_ = second;
      temp++;
    }
    if((length_ % 3) == 0) {
      if(count == (count - 1)) {
        tail_ = first;
      }
    }
    curr = first->next;
    count = count + 1;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  bool initial = true;
  ListNode* currNode;
  ListNode* tempNode;
  ListNode* origSP = startPoint;
  ListNode* origEP = endPoint;
  if(origSP == origEP) {
    return;
  }
  if(origSP == NULL) {
    return;
  }
  if(origEP == NULL) {
    return;
  }
  while(origEP != NULL && (initial == true)) {
		origEP = origEP->next;
		if(origEP == startPoint) {
      initial = false;
		  startPoint = endPoint;
			endPoint = origSP;
		}
	}
  currNode = startPoint;
	ListNode* beginningPt = startPoint->prev;
	ListNode* endingPt = endPoint->next;
	while(currNode != endingPt) {
  	tempNode = currNode->next;
  	currNode->next = currNode->prev;
  	currNode->prev = tempNode;
  	currNode = tempNode;
	}
	if(initial == true) {
		tempNode = startPoint;
		startPoint = endPoint;
		endPoint = tempNode;
		startPoint->prev = beginningPt;
		endPoint->next = endingPt;
	}
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  // @todo Graded in MP3.2
  if(head_ == NULL || tail_ == NULL) {
    return;
  }
  if(length_ == 0 || length_ == 1 || n == 1) {
    return;
  }
  if(length_ <= n) {
    reverse(head_, tail_);
    return;
  }
  ListNode* curr = head_;
  ListNode* temp = curr;
  int multiples = (n - 1);
  while(true) {
    if(temp != NULL) {
      for(int i = 0; i < multiples; i++) {
        if(temp->next != NULL) {
          temp = temp->next;
        }
        else {
          continue;
        }
      }
      reverse(curr, temp);
      if(temp->next != NULL) {
        temp->next->prev = temp;
      }
      if(curr->prev != NULL) {
        curr->prev->next = curr;
      }
      curr = temp->next;
      temp = curr;
    }
    else {
      break;
    }
  }
  int headTest = 0;
  int tailTest = 0;
  while(tailTest == 0) {
    if(tail_->next != NULL) {
      tail_ = tail_->next;
      continue;
    }
    break;
  }
  while(headTest == 0) {
    if(head_->prev != NULL) {
      head_ = head_->prev;
      continue;
    }
    break;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == NULL) {
    return second;
  }
  if(second == NULL) {
    return first;
  }
  int setHead = 0;
  bool nextFirst = false;
  bool nextSecond = false;
  ListNode* currFirst = first;
  ListNode* currSecond = second;
  ListNode* returnList;
  ListNode* tempNext;
  if(currFirst->data < currSecond->data) {
    setHead = 1;
    returnList = currFirst;
    currFirst = currFirst->next;
  }
  else {
    setHead = 2;
    returnList = currSecond;
    currSecond = currSecond->next;
  }
  if(setHead == 1) {
    head_ = first;
  }
  else if(setHead == 2) {
    head_ = second;
  }
  while(currFirst || currSecond) {
    if (!currSecond || (currFirst && currFirst->data < currSecond->data)) {
      nextFirst = true;
    }
    else {
      nextSecond = true;
    }
    if(nextFirst == true) {
      tempNext = currFirst;
      tempNext->prev = returnList;
      returnList->next = currFirst;
      returnList = returnList->next;
      currFirst = currFirst->next;
      nextFirst = false;
      continue;
    }
    if(nextSecond == true) {
      tempNext = currSecond;
      tempNext->prev = returnList;
      returnList->next = currSecond;
      returnList = returnList->next;
      currSecond = currSecond->next;
      nextSecond = false;
      continue;
    }
  }
  return head_;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1) {
    return start;
  }
  else {
    ListNode* firstHalf;
    ListNode* secondHalf;
    ListNode* temp;
    temp = split(start, (chainLength / 2));
    firstHalf = mergesort(start, (chainLength / 2));
    secondHalf = mergesort(temp, chainLength - (chainLength / 2));
    return merge(firstHalf, secondHalf);
  }
  return NULL;
}
