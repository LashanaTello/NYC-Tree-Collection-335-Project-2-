/*******************************************************************************
  Title          : avl.h
  Author         : Lashana Tello
  Created on     : March 1, 2018
  Description    : The interface file for the AVL_Tree class
  Purpose        : To provide a means of representing all trees in New York City
  Usage          : Use to store all trees from the 2015 NYC Street Tree Census
									 and order the trees by their common species name
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/


#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "BinaryNode.cpp"
#include "tree.h"
#include <list>
#include <map>
const BinaryNode<Tree> kNotFound(Tree(0, 0, "", "", "x", 0, "", "", 0, 0));
//	No Tree objects have "x" for an spc_common member, which is why kNotFound's
//	spc_common member is "x"

/*******************************************************************************

		The AVL_Tree class stores all the trees in the 2015 NYC Street Tree Census 
		and uses the Tree’s common species name (its spc_common member) as the 
		primary key and the Tree’s ID number (its tree_id) as	a secondary key. The 
		AVL_Tree encapsulates a map and a pointer to a BinaryNode that stores a 
		Tree object. The BinaryNode has a left child pointer and a right child 
		pointer. The map uses strings as keys and stores an integer value for each 
		key. The map is used to store the number of Tree objects that have the same 
		spc_common member, which means the spc_common is the key. The AVL_Tree 
		provides a few methods for accessing specific information about the Tree 
		objects it stores. There are methods for finding all Tree objects with a 
		specific spc_common member, for finding all Tree objects within a zipcode, 
		and for finding all Tree objects that are a certain distance within given 
		latitude and longitude coordinates

*******************************************************************************/


class AVL_Tree {
 public:
	//	Default constructor for AVL_Tree object
	AVL_Tree();

	//	Makes this AVL_Tree object a deep copy of tree
	AVL_Tree(const AVL_Tree& tree); 

	//	Destructs AVL_Tree object
	~AVL_Tree();

	//	Returns true if AVL_tree object contains no trees
	bool empty() const;

	//	Returns the number of Tree objects in AVL_Tree object
	int get_number_of_trees() const;

	//	Returns the height of the AVL_Tree
	int height() const;

	//	Returns Tree x if x is found. Otherwise, returns the Tree object stored 
	//	in kNotFound if x is not found  
	const Tree& find(const Tree& x) const;

	//	Returns the minimum Tree object in the AVL_Tree
	//	If called when AVL_Tree is empty, returns kNotFound
	const Tree& findMin() const;

	//	Returns the maximum Tree object in the AVL_Tree
	//	If called when AVL_Tree is empty, returns kNotFound
	const Tree& findMax() const;

	//	Returns a list of Tree objects whose spc_common member is equal to 
	//	x's spc_common member. If x's spc_common member does not exist in the 
	//	AVL_Tree object, the returned list will be empty
	std::list<Tree> findallmatches(const Tree& x) const;

	//	Returns the number of Tree objects whose spc_common member equals 
	//	name_of_species. This method is case insensitive. 
	//	Returns 0 if name_of_species does not exist in the AVL_Tree object 
	int count_species(const std::string& name_of_species) const;

	//	Returns a list of the spc_common members of all the Tree objects found in
	//	the given zipcode. The returned list will contain duplicates. 
	//	If no Tree objects are found in the given zipcode, the list will be empty
	std::list<std::string> all_in_zipcode(const int& zip) const;

	//	Returns a list of the spc_common members of all the Tree objects found 
	//	within the given distance of the given latitude and longitude coordinates
	//	in kilometers. The returned list will contain duplicates. 
	//	If no Tree objects are found within the given distance of 
	//	the given coordinates, the list will be empty
	std::list<std::string> all_nearby(const double& latitude, 
																		const double& longitude,
																		const double& distance) const;

	//	Prints all the Tree objects in the AVL_Tree object
	void print(std::ostream& out) const;

	//	Removes all Tree objects from the AVL_Tree object
	//	After this method is called, root_ will point to null
	void clear(); 

	//	Adds the Tree object x to the AVL_Tree object
	void insert(const Tree& x); 

	//	Removes the Tree object x from the AVL_Tree object
	void remove(const Tree& x);

	//	Changes the case of species to match the case of the spc_common members 
	//	of the Tree objects in the AVL_Tree object
	void change_case(std::string& species) const;

 protected:
	//	Copies the AVL_Tree whose root is node
	void copy_tree(BinaryNode<Tree>* node);

	//	Returns the number of Tree objects in the AVL_Tree whose root is node
	int get_number_of_trees(BinaryNode<Tree>* node) const;

	//	Returns the height of the AVL_Tree whose root is node
	int height(BinaryNode<Tree>* node) const;

	//	Returns Tree x if x is found in the AVL_Tree whose root is node. 
	//	Otherwise, returns the Tree object stored in kNotFound if x is not found  
	const Tree& find(const Tree& x, BinaryNode<Tree>* node) const;

	//	Returns the minimum Tree object in the AVL_Tree whose root is node
	const Tree& findMin(BinaryNode<Tree>* node) const;

	//	Returns the maximum Tree object in the AVL_Tree whose root is node
	const Tree& findMax(BinaryNode<Tree>* node) const;

	//	Adds all Tree objects whose spc_common is equal to Tree z's spc_common 
	//	to match_list and returns match_list
	//	spec_count is the number of Tree objects in this AVL_Tree object whose 
	//	spc_common matches with z's
	//	The Tree object of the BinaryNode that node points to is checked to see if 
	//	its spc_common is equal to z's spc_common
	std::list<Tree>& findallmatches(const Tree& x, const int& spec_count,
																	std::list<Tree>& match_list,
																	BinaryNode<Tree>* node) const;

	//	Adds the spc_common member of all Tree objects found in the given 
	//	zipcode (zip) to match_list and returns match_list 
	//	The Tree object of the BinaryNode that node points to is checked to see if
	//	its zipcode equals the given zipcode
	//	This method uses an inorder traversal
	std::list<std::string>& all_in_zipcode(const int& zip, BinaryNode<Tree>* node,
																				 std::list<std::string>& match_list)
																				 const;

	//	Adds the spc_common member of all Tree objects found within the given 
	//	distance of the given latitude and longitude coordinates to match_list 
	//	and returns match_list
	//	The Tree object of the BinaryNode that node points to is checked to see if 
	//	its latitude and longitude are within the given distance of the given
	//	coordinates
	//	This method uses an inorder traversal
	std::list<std::string>& all_nearby(const double& latitude,
																		 const double& longitude,
																		 const double& distance,
																		 BinaryNode<Tree>* node,
																		 std::list<std::string>& match_list) const;

	//	Prints the Tree object stored in the BinaryNode that node points to
	//	This method uses an inorder traversal
	void print(std::ostream& out, BinaryNode<Tree>* node) const;

	//	Uses a postorder traversal to delete the AVL_Tree whose root is node
	void clear(BinaryNode<Tree>*& node);

	//	Adds x to this AVL_Tree object. The Tree object of the BinaryNode that 
	//	node points to is used to determine where to place x is the AVL_Tree
	void insert(const Tree& x, BinaryNode<Tree>*& node);

	//	Removes x from this AVL_Tree object. The Tree object of the BinaryNode 
	//	that node points to is used to search for x
	void remove(const Tree& x, BinaryNode<Tree>*& node);

	//	Deletes the BinaryNode object pointed to by node
	void remove_node(BinaryNode<Tree>*& node);

	//	Returns a Tree object that is the inorder successor of the Tree object we 
	//	want to remove from the AVL_Tree. The Tree object of the BinaryNode that 
	//	node points to is used to search for the inorder successor
	Tree inorder_successor(BinaryNode<Tree>*& node);

	//	Rotates node and its left child to the right to rebalance AVL_Tree object
	void LL_rotate(BinaryNode<Tree>*& node);

	//	First rebalances node’s left child’s subtree by rotating it to the left 
	//	and then rebalances node by rotating it and its left child to the right
	void LR_rotate(BinaryNode<Tree>*& node);

	//	Rotates node and its right child to the left to rebalance AVL_Tree object
	void RR_rotate(BinaryNode<Tree>*& node);

	//	First rebalances node’s right child’s subtree by rotating it to the right
	//	and then rebalances node by rotating it and its right child to the left
	void RL_rotate(BinaryNode<Tree>*& node);

 private:
	//	Pointer to the root of the AVL_Tree object
	BinaryNode<Tree>* root_;

	//	Map that stores all the spc_common members of the Tree objects and
	//	how many Tree objects have a particular spc_common
	std::map<std::string, int> species_count_;
};

#endif
