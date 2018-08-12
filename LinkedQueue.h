/*******************************************************************************
  Title          : LinkedQueue.h
  Author         : Lashana Tello
  Created on     : March 1, 2017
  Description    : The interface file for the LinkedQueue class
  Purpose        : To represent a queue using a linked list of items with a FIFO 
                   organization
  Usage          : Include this file with client code
  Build with     : This class is templated. Do not build file individually. 
									 Only compile the file this class is used in.
  Modifications  : February 26, 2018
									 Added a class description
 
*******************************************************************************/


#ifndef __LINKEDQUEUE_H_
#define __LINKEDQUEUE_H_

#include "Node.cpp"

/*******************************************************************************

		The LinkedQueue class is a linked list representation of a queue, so it has 
		a FIFO (first-in, first-out) organization. Meaning, the first element 
		inserted is the first element to be removed from the queue and new elements 
		are always added to the back of the queue. The LinkedQueue class is 
		templated to be used with any kind of data. This class uses nodes to 
		represent an element in the queue and abstracts away the number of elements
		in the queue and the node pointer to head_ (the front of the queue) and 
		tail_ (the back of the queue)

*******************************************************************************/

template<class T>
class LinkedQueue {
 public:
	//	Creates an empty queue with size_ = 0 and head_ and tail_ set to nullptr
	LinkedQueue();

	//	Destroys this queue object
	~LinkedQueue();

	//	Returns a queue object that is an exact copy of the right_side object
	LinkedQueue<T>& operator=(const LinkedQueue<T>& right_side);

	//	Returns true if this queue's elements and right_side's elements are equal
	//	to each other and are in the same order in both queues
	bool operator==(const LinkedQueue<T>& right_side);

	//	Removes all elements in queue and makes head_ and tail_ point to nullptr
	//	Sets size_ to 0
	void clear();

	//	Returns number of elements in the queue
	int size() const { return size_; };

	//	Returns true if queue object is empty
	bool is_empty() const { return (size() == 0); };

	//	Adds element to the back of the queue. Returns true if successful
	bool enqueue(const T& data);

	//	Removes element at front of queue. Returns true if successful
	bool dequeue();

	//	Returns element at the front of the queue
	//	Precondition: Queue is not empty
	//	Postcondition: Element at front of queue is returned and queue is
	//	unchanged
	T peek() const;

 private:
	Node<T>* head_;
	Node<T>* tail_;
	int size_;
};

#include "LinkedQueue.cpp"

#endif
