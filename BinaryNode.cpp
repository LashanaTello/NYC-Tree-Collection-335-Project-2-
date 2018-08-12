/*******************************************************************************
  Title          : BinaryNode.cpp
  Author         : Lashana Tello
  Created on     : March 1, 2017
  Description    : The interface and implementation file for the BinaryNode
									 struct
  Purpose        : To provide a representation of an element that is linked to 
									 two other elements in a linked data structure such as a 
									 binary tree, binary search tree, or avl tree 
  Usage          : Include this file in header file of linked binary data 
									 structure
  Build with     : No building 
  Modifications  : March 28, 2018
									 Added description
 
*******************************************************************************/


#ifndef __BINARYNODE_H_
#define __BINARYNODE_H_

/*******************************************************************************

		The BinaryNode struct is used to represent a single element in a linked
		binary data structure and connect all the elements in the linked data 
		structure. The BinaryNode struct's data members are the data it stores, the 
		height of the BinaryNode, and its left and right child pointers, which are 
		BinaryNode pointers to the next BinaryNode in the linked data structure. 
		The height member is an int that stores the height of the BinaryNode, which 
		we need in an AVL Tree. There's also a method named is_leaf() that returns 
		true if this BinaryNode has no children. The BinaryNode struct is
		templated to be used with any type of data

*******************************************************************************/


template<class T>
struct BinaryNode {
	T data;
	BinaryNode* left_child;
	BinaryNode* right_child;
	int height;
	BinaryNode(const T& some_data, BinaryNode* left_node, BinaryNode* right_node) 
	{
		data = some_data;
		left_child = left_node;
		right_child = right_node;
		height = 0;
	}

	BinaryNode(const T& some_data) {
		data = some_data;
		left_child = nullptr;
		right_child = nullptr;
		height = 0;
	}

	BinaryNode() {
		left_child = nullptr;
		right_child = nullptr;
		height = 0;
	}

	bool is_leaf() {
		return ((left_child == nullptr) && (right_child == nullptr));
	}
}; 

#endif

