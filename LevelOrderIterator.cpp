/*******************************************************************************
  Title          : LevelOrderIterator.cpp
  Author         : Lashana Tello
  Created on     : March 1, 2017
  Description    : The implementation file for the LevelOrderIterator class
  Purpose        : To provide a means of representing a single tree in New York
                   City
  Usage          : Use to store data from NYC Tree Census
  Build with     : No building 
  Modifications  : March 13, 2018
									 Edited destructor
 
*******************************************************************************/


#include "LevelOrderIterator.h"

template<class T>
LevelOrderIterator<T>::LevelOrderIterator() {
	root_ = nullptr;
	current_ = nullptr;
}

template<class T>
LevelOrderIterator<T>::LevelOrderIterator(BinaryNode<T>* tree_root) {
	root_ = tree_root;
	current_ = root_;
	if (root_->left_child != nullptr) {
		queue_.enqueue(root_->left_child);
	}
	if (root_->right_child != nullptr) {
		queue_.enqueue(root_->right_child);
	}
}

template<class T>
LevelOrderIterator<T>::LevelOrderIterator(const LevelOrderIterator<T>& rhs) {
	root_ = rhs.root_;
	current_ = rhs.current_;
	queue_ = rhs.queue_;
}

template<class T>
LevelOrderIterator<T>::~LevelOrderIterator() {
	root_ = nullptr;
	current_ = nullptr;
	queue_.clear();
}

template<class T>
void LevelOrderIterator<T>::set_root(BinaryNode<T>* tree_root) {
	root_ = tree_root;
}

template<class T>
LevelOrderIterator<T>& LevelOrderIterator<T>::operator=(
    const LevelOrderIterator<T>& rhs) {
	root_ = rhs.root_;
	current_ = rhs.current_;
	queue_ = rhs.queue_;
	return *this;
}

template<class T>
LevelOrderIterator<T>& LevelOrderIterator<T>::operator++() {
	if (!queue_.is_empty()) {
		current_ = queue_.peek();
		if (current_->left_child != nullptr) {
			queue_.enqueue(current_->left_child);
		}
		if (current_->right_child != nullptr) {
			queue_.enqueue(current_->right_child);
		}
		queue_.dequeue();
	} else {
		current_ = nullptr;
	}
	return *this;
}

template<class T>
LevelOrderIterator<T> LevelOrderIterator<T>::operator++(int) {
	LevelOrderIterator<T> temp(*this);
	operator++();
	return temp;
}

template<class T>
bool LevelOrderIterator<T>::operator==(const LevelOrderIterator<T>& rhs) const {
	if (current_->data == rhs.current_->data) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool LevelOrderIterator<T>::operator!=(const LevelOrderIterator<T>& rhs) const {
	if (current_->data != rhs.current_->data) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool LevelOrderIterator<T>::end() const {
	if (current_ == nullptr) {
		return true;
	}
	return false;
}

