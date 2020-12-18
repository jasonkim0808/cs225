/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_=0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);

}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
	ListNode *c = NULL;
	c = this->head_;
	ListNode *n = NULL;
  	while (c != NULL) {
		n = c;
		c = c -> next;
		delete n;
	}
	
	this->tail_ = NULL;
	this->length_ = 0;
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
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
    
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_ = newNode;
  length_++;

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
  
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if (head_ == NULL) {
    head_ = newNode;

  }
  if (tail_ != NULL) {
    tail_->next = newNode;
  }

  tail_ = newNode;
  length_++;

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
  if (start == NULL || splitPoint == 0)
    return NULL;

  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }  

  curr->prev->next = NULL;
  curr->prev = NULL;
  
  return curr;
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
  if (head_->next->next == NULL)
    return;
  ListNode * one = head_;
  ListNode * two = head_->next;
  ListNode * three = two->next;
  ListNode * oneP = one->prev;
  ListNode * threeN = three->next;

  int count = 1;
  bool t = true;
  while (t) {
    count++;
    if (count % 3 == 2) {
      three -> next = one;
      two->prev = oneP;
      if (oneP != NULL)
        oneP->next = two;
      if (threeN != NULL) 
	threeN -> prev = one;
      one->prev = three;
      one->next = threeN;
      
    }
    if (threeN == NULL)
      t = false;
    if (count / 3 == 0)
      head_ = two;
    if (threeN != NULL)
    {
      three = threeN;
      two = threeN -> prev;
      one = threeN -> prev -> prev;
      oneP = threeN -> prev -> prev -> prev;
      threeN = threeN -> next;
    }
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
  if (startPoint == endPoint)
    return;
  ListNode * tempL = startPoint;
  ListNode * nlF = startPoint->prev;
  ListNode * fp = startPoint->prev;
  ListNode * bn = endPoint->next;

  tempL->prev = tempL->next;
  while(tempL->next != bn) {
    tempL->next->prev = tempL->next->next;
    tempL = tempL->next;
  }

  tempL = startPoint;
 
  while(tempL->prev != bn) {
    tempL->prev->next = tempL;
    tempL = tempL->prev;
  }
  startPoint->next = bn;
  if (bn != NULL)
    bn->prev = startPoint;
  endPoint->prev = fp;
  if (fp != NULL)
    fp->next = endPoint;
  ListNode * temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;
  
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(n < 2)
    return;
  if(length_ <= 1)
    return;
  if(n == length_)
    reverse();
  ListNode * tempL = head_;
  ListNode * tempR = tempL;
  ListNode * ogTail = tail_;
  bool check = false;
  while(tempL != NULL) {
    int index = 1;
    while (index < n) {
      if (tempR != ogTail)
	tempR = tempR->next;
      index++;
    }
    reverse(tempL, tempR);
    if (check == false)  {
      head_ = tempL;
      check = true;
    }
    tail_ = tempR;
    tempL = tempR->next;
    tempR = tempL;
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
  if(first == NULL)
    return second;
  if(second == NULL)
    return first;
  ListNode * result = NULL;
  ListNode * res = NULL;

  if (first->data < second->data) {
    result = first;  
    first = first->next;
  } else {
    result = second;
    second = second->next;
  }
  res = result;
  while(first != NULL && second != NULL) {
    if (first->data < second->data) {
      res->next = first;
      first->prev = res;
      first = first->next;
    } else {
      res->next = second;
      second->prev = res;
      second = second->next;
    }
    res = res->next;
  }
  if (first == NULL) {
    res->next = second;
    second->prev = res;
  } else if (second == NULL) {
    res->next = first;
    first->prev = res;
  }

  return result;

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
  if(start == NULL)
    return NULL;
  if(chainLength == 1)
    return start;

  ListNode * temp = split(start, chainLength/2);
  ListNode * l = mergesort(start, chainLength/2);
  ListNode * r = mergesort(temp, chainLength/2 + chainLength%2);
  ListNode * result = merge(l,r);


  return result;
}
