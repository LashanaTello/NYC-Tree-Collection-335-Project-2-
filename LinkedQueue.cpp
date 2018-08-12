/*******************************************************************************
  Title          : LinkedQueue.cpp
  Author         : Lashana Tello
  Created on     : March 1, 2017
  Description    : The implementation file for the LinkedQueue class
  Purpose        : To represent a queue using a linked list of items with a FIFO
									 organization 
  Usage          : Include this file in templated header file for this class
  Build with     : No building 
  Modifications  : Added comments
 
*******************************************************************************/


#include "LinkedQueue.h"

template<class T>
LinkedQueue<T>::LinkedQueue() {
	head_ = nullptr;
	tail_ = nullptr;
	size_ = 0;
}

template<class T>
LinkedQueue<T>::~LinkedQueue() {
	clear();
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& right_side) {
	if (this == &right_side) {
		return *this;
	} else {
		Node<T>* current = right_side.head_;
		clear();
		while (current != nullptr) {
			enqueue(current->data);
			current = current->next;
		}
		return *this;
	}
}

template<class T>
bool LinkedQueue<T>::operator==(const LinkedQueue<T>& right_side) {
	if (size() == right_side.size()) {
		Node<T>* right = right_side.head_;
		Node<T>* left = head_;
		//	Since both queues are the same size, we only need to check if one of 
		//	them reaches nullptr
		while (left != nullptr) {
			if (left->data != right->data) {
				return false;
			}
			left = left->next;
			right = right->next;
		}
		return true;
	} else {
		return false;
	}
}

template<class T>
void LinkedQueue<T>::clear() {
	while (!is_empty()) {
		dequeue();
	}
}

template<class T>
bool LinkedQueue<T>::enqueue(const T& data) {
	Node<T>* new_node = new Node<T>(data);
	if (is_empty()) {
		head_ = new_node;
	} else {
		tail_->next = new_node;
	}
	tail_ = new_node;
	++size_;
	return true;
}

template<class T>
bool LinkedQueue<T>::dequeue() {
	if (!is_empty()) {
		if (head_ == tail_) {
			delete head_;
			--size_;
			head_ = nullptr;
			tail_ = nullptr;
			return true;
		}
		Node<T>* node_to_delete = head_;
		head_ = head_->next;
		node_to_delete->next = nullptr;
		delete node_to_delete;
		node_to_delete = nullptr;
		--size_;
		return true;
	} else {
		return false;
	}
}

template<class T>
T LinkedQueue<T>::peek() const {
		return head_->data;
}
