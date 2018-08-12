/*******************************************************************************
  Title          : LevelOrderIterator.h
  Author         : Lashana Tello
  Created on     : March 1, 2017
  Description    : The interface file for the LevelOrderIterator class
  Purpose        : To traverse through a Binary Tree object in levelorder
  Usage          : To get a Binary Tree’s elements in levelorder
  Build with     : No building 
  Modifications  : March 13, 2018
									 Added class description and method prologues
 
*******************************************************************************/


#ifndef __LEVELORDERITERATOR_H_
#define __LEVELORDERITERATOR_H_

#include <iterator>
#include "LinkedQueue.h"
#include "BinaryNode.cpp"

/*******************************************************************************

		The LevelOrderIterator class is a forward iterator that is used to traverse 
		through a Binary Tree. The LevelOrderIterator class encapsulates two 
		BinaryNode pointers and a LinkedQueue object. The BinaryNode pointer root_ 
		points to the root of a Binary Tree and is where the iterator will start. 
		The BinaryNode pointer current_ points to the BinaryNode where the iterator 
		currently is in the tree, which is the BinaryNode at the front of the queue. 
		The LinkedQueue object stores the children of the BinaryNode that current_ 
		points to if those children are not null. This class is templated to be
		used with different data types

*******************************************************************************/

template<class T>
class LevelOrderIterator : public std::iterator<std::forward_iterator_tag, T> {
 public:
	//	Default constructor for LevelOrderIterator object
  LevelOrderIterator();

	//	Constructor for LevelOrderIterator object that sets root_ equal to 
	//	tree_root
  LevelOrderIterator(BinaryNode<T>* tree_root);

	//	Constructs this LevelOrderIterator object as an exact copy of rhs by 
	//	making this LevelOrderIterator object point to the same BinaryNodes that 
	//	rhs’s root_ and current_ are pointing to and copying rhs’s queue_
  LevelOrderIterator(const LevelOrderIterator& rhs);

	//	Destroys iterator object
  ~LevelOrderIterator();

	//	Sets root_ equal to tree_root
	void set_root(BinaryNode<T>* tree_root);

	//	Returns a reference to this LevelOrderIterator object that is now a 
	//	deep copy of rhs
  LevelOrderIterator<T>& operator=(const LevelOrderIterator& rhs);

	//	Returns a reference to a LevelOrderIterator object that is now pointing 
	//	to the next BinaryNode in the sequence
  LevelOrderIterator<T>& operator++();

	//	Returns a copy of a LevelOrderIterator object that is still pointing the 
	//	same node it was pointing to before the call to this method. 
	//	This LevelOrderIterator object is advanced to the next BinaryNode in the 
	//	sequence but the returned copy is not
  LevelOrderIterator<T> operator++(int);

	//	Returns the data that current_ points to
  T& operator*() { return current_->data; };

	//	Returns true if the data that this iterator's current_ points to and 	
	//	rhs's current_ are equal to each other. This method assumes that
	//	the == operator is defined for the data that current_ points to
  bool operator==(const LevelOrderIterator& rhs) const;

	//	Returns true if the data that this iterator's current_ points to and 	
	//	rhs's current_ are not equal to each other. This method assumes that
	//	the != operator is defined for the data that current_ points to
  bool operator!=(const LevelOrderIterator& rhs) const;

	//	Returns a pointer to the beginning of the tree, which is root_
  BinaryNode<T>* begin() const { return root_; };

	//	Returns a pointer to the end of the tree, which null
  bool end() const;

 private:
	//	The root of the tree, which is where the iterator will start
	BinaryNode<T>* root_;

	//	The current position (or node) in the tree that the iterator is pointing 
	//	to
	BinaryNode<T>* current_;

	//	The queue is used to traverse through the tree in level order. The queue
	//	stores the children of the node that current_ points to if they are not 
	//	null
	LinkedQueue<BinaryNode<T>*> queue_;

};

#include "LevelOrderIterator.cpp"

#endif
