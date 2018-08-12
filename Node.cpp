/*******************************************************************************
  Title          : Node.cpp
  Author         : Lashana Tello
  Created on     : March 1, 2017
  Description    : The interface and implementation file for the Node struct
  Purpose        : To provide a representation of an element in a linked data 
									 structure such as a linked list or linked queue or linked 
									 stack 
  Usage          : Include this file in header file of linked data structure
  Build with     : No building 
  Modifications  : February 26, 2018
									 Added description
 
*******************************************************************************/

#ifndef __NODE_H_
#define __NODE_H_

/*******************************************************************************

		The Node struct is used to represent a single element in a linked data 
		structure and connect all the elements in the linked data structure. 
		The Node struct’s data members are the data it stores, and next, which is a 
		Node pointer to the next Node in the linked data structure. The Node struct 
		is templated to be used with any type of data.

*******************************************************************************/

template<class T>
struct Node {
	T data;
	Node* next;
	Node(const T& some_data, Node* next_node) {
		data = some_data;
		next = next_node;
	}

	Node(const T& some_data) {
		data = some_data;
		next = nullptr;
	}

	Node() {
		next = nullptr;
	}
}; 

#endif

