/*******************************************************************************
  Title          : tree.h
  Author         : Lashana Tello
  Created on     : February 23, 2018
  Description    : The interface file for the Tree class
  Purpose        : To provide a means of representing a single tree in New York
                   City
  Usage          : Use to store data from NYC Tree Census
  Build with     : No building 
  Modifications  : March 1, 2018
									 Added new methods
 
*******************************************************************************/


#ifndef __TREE_H__
#define __TREE_H__

#include <string>

/*******************************************************************************

		The Tree class stores information about a single tree in the New York City 
		area from the 2015 Street Tree Census. Its private member variables all
		store a piece of data from the 2015 NYC Street Tree Census. It doesn't
		store all the data of a tree found in the Tree Census file and it also
		orders the data differently

*******************************************************************************/

class Tree {
 public:
	//	Default constructor for Tree object
	Tree();

	//	Creates Tree object from the data in the string treedata
	Tree(const std::string& treedata);

	//	Creates Tree object
	Tree(int id, int diam, std::string status, std::string health, 
			 std::string spc, int zip, std::string addr, std::string boro, 
			 double latitude, double longitude);

	//	Creates a Tree object that is an exact copy of other_tree
	Tree(const Tree& other_tree);

	//	Destroys Tree object
	~Tree();

	//	Returns true if both Tree objects have the same spc_common_ member and
	//	the same tree_id_ member value
	friend bool operator==(const Tree& t1, const Tree& t2);

	//	Returns true if t1's spc_common_ member is lexicographically less than
	//	t2's spc_common_ member and t1's tree_id_ member is smaller than 
	//	t2's tree_id_ member
	friend bool operator<(const Tree& t1, const Tree& t2);

	//	Prints a Tree object onto the provided ostream byprinting all the object's
	//	member variables in the same order as they appear in the private section
	friend std::ostream& operator<<(std::ostream& os, const Tree& t);

	//	Returns true if both Tree objects have the same spc_common_ member
	friend bool samename(const Tree& t1, const Tree& t2);

	//	Returns true if t1's spc_common_ member is lexicographically less than
	//	t2's spc_common_ member
	friend bool islessname(const Tree& t1, const Tree& t2);

	//	Returns a reference to this Tree object that is now an exact copy of 
	//	other_tree after this method is called
	Tree& operator=(const Tree& other_tree);

	//	Returns true if both Tree objects do not have the same spc_common_ member
	//	and the same tree_id_ member value 
	bool operator!=(const Tree& other_tree);

	//	Returns spc_common_, which is the common name of the tree
	std::string common_name() const;

	//	Returns boroname_, which is the borough in which the tree is located
	std::string borough_name() const;

	//	Returns address_, which is the nearest address to the tree
	std::string nearest_address() const;

	//	Returns tree_dbh_, which is the tree's diameter
	int diameter() const;

	//	Returns zipcode_, which is the zipcode of the tree's address
	int zip() const;

	//	Gives the parameter latitude the same value as the Tree object's latitude_
	//	member. Gives the parameter longitude the same value as the Tree object's
	//	longitude_ member
	void get_position(double& latitude, double& longitude) const;

 private:

	//	The common name of the tree which can be the empty string
	std::string spc_common_;
	
	//	The unique non-negative identification number of the tree
	int tree_id_;

	//	A non-negative integer representing the diameter of the tree
	int tree_dbh_;

	//	The living status of the tree which is either "Alive", "Dead", or "Stump"
	std::string status_;

	//	The condition of the tree which is either "Good", "Fair", "Poor" or the
	//	empty string
	std::string health_;

	//	The address closest to the tree
	std::string address_;

	//	The borough where the tree is located
	std::string boroname_;

	//	The zipcode where the tree is located
	int zipcode_;

	//	The latitude of the tree's location
	double latitude_;

	//	The longitude of the tree's location
	double longitude_;
};

#endif
