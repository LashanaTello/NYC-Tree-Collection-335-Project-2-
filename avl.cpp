/*******************************************************************************
  Title          : avl.cpp
  Author         : Lashana Tello
  Created on     : March 1, 2018
  Description    : The implementation file for the AVL_Tree class
  Purpose        : To provide a means of representing a single tree in New York
                   City
  Usage          : Use to store data from NYC Tree Census
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#include "avl.h"
#include <algorithm>
#include <cctype>
#include "haversine.cpp"
#include "LevelOrderIterator.h"

AVL_Tree::AVL_Tree() {
	root_ = nullptr;
	std::map<std::string, int> species_count_;
}

AVL_Tree::AVL_Tree(const AVL_Tree& tree) {
	copy_tree(tree.root_);
	species_count_ = tree.species_count_;
}

AVL_Tree::~AVL_Tree() {
	clear();
}

bool AVL_Tree::empty() const {
	if (root_ == nullptr) {
		return true;
	}
	return false;
}

int AVL_Tree::get_number_of_trees() const {
	return get_number_of_trees(root_);
}

int AVL_Tree::height() const {
	return height(root_);
}

const Tree& AVL_Tree::find(const Tree& x) const {
	if (find(x, root_) == x) {
		return x;
	} else {
		return kNotFound.data;
	}
}

const Tree& AVL_Tree::findMin() const {
	if (root_ == nullptr) {
		return kNotFound.data;
	}
	return findMin(root_);
}

const Tree& AVL_Tree::findMax() const {
	if (root_ == nullptr) {
		return kNotFound.data;
	}
	return findMax(root_);
}

std::list<Tree> AVL_Tree::findallmatches(const Tree& x) const {
	std::list<Tree> match_list;
	if (root_ == nullptr) {
		return match_list;
	}
	std::string spc = x.common_name();
	for (char& c : spc) {
		if (isupper(c)) {
			c = tolower(c);
		}
	}
	//	first check if x's spc in all lowercase exists in AVL_Tree
	//	then check if x's spc with the first letter capitalized exists in AVL_Tree
	//	if neither exist, return an empty list
	if (species_count_.find(spc) == species_count_.end()) {
		change_case(spc);
		if (species_count_.find(spc) == species_count_.end()) {
			return match_list;
		}
	}
	int spec_count = species_count_.at(spc);
	Tree z(0, 0, "", "", spc, 0, "", "", 0, 0);
	return findallmatches(z, spec_count, match_list, root_);
}

int AVL_Tree::count_species(const std::string& species_name) const {
	if (root_ == nullptr) {
		return 0;
	}
	std::string spc = species_name;
	for (char& c : spc) {
		if (isupper(c)) {
			c = tolower(c);
		}
	}
	if (species_count_.find(spc) == species_count_.end()) {
		change_case(spc);
		if (species_count_.find(spc) == species_count_.end()) {
			return 0;
		}
	}
	return species_count_.at(spc);
}

std::list<std::string> AVL_Tree::all_in_zipcode(const int& zip) const {
	std::list<std::string> match_list;
	//	check if zip is a possible zipcode
	if (root_ == nullptr || 99999 < zip) {
		return match_list;
	}
	return all_in_zipcode(zip, root_, match_list);
}
	
std::list<std::string> AVL_Tree::all_nearby(const double& latitude, 
																						const double& longitude,
																						const double& distance) const {
	std::list<std::string> match_list;
	if (root_ == nullptr) {
		return match_list;
	}
	return all_nearby(latitude, longitude, distance, root_, match_list);
}

void AVL_Tree::print(std::ostream& out) const {
	print(out, root_);
}

void AVL_Tree::clear() {
	species_count_.clear();
	clear(root_);
}

void AVL_Tree::insert(const Tree& x) {
	insert(x, root_);
}

void AVL_Tree::remove(const Tree& x) {
	remove(x, root_);
}

void AVL_Tree::change_case(std::string& species) const {
	char c = species[0];
	if (islower(c)) {
		species[0] = toupper(c);
	} else if (ispunct(c)) {
		c = species[1];
		species[1] = toupper(c);
	}
}

/*******************************************************************************

																	PROTECTED

*******************************************************************************/

void AVL_Tree::copy_tree(BinaryNode<Tree>* node) {
	if (node == nullptr) {
		return;
	}
	insert(node->data);
	copy_tree(node->left_child);
	copy_tree(node->right_child);
}

int AVL_Tree::get_number_of_trees(BinaryNode<Tree>* node) const {
	if (node == nullptr) {
		return 0;
	}
	return 1 + get_number_of_trees(node->left_child) + 
             get_number_of_trees(node->right_child);
}

int AVL_Tree::height(BinaryNode<Tree>* node) const {
	if (node == nullptr) {
		return -1;
	} else if (node->is_leaf()) {
		return 0;
	}
	return node->height;
	//	this line is responsible for tree creation taking so long before
	//return std::max(height(node->left_child), height(node->right_child)) + 1;
}

const Tree& AVL_Tree::find(const Tree& x, BinaryNode<Tree>* node) const {
	if (node == nullptr) {
		return kNotFound.data;
	} else if (x == node->data) {
		return x;
	} else if (x < node->data) {
		find(x, node->left_child);
	} else if (node->data < x) {
		find(x, node->right_child);
	}
}

const Tree& AVL_Tree::findMin(BinaryNode<Tree>* node) const {
	if (node->left_child == nullptr) {
		return node->data;
	}
	findMin(node->left_child);
}

const Tree& AVL_Tree::findMax(BinaryNode<Tree>* node) const {
	if (node->right_child == nullptr) {
		return node->data;
	}
	findMax(node->right_child);
}

std::list<Tree>& AVL_Tree::findallmatches(const Tree& z, const int& spec_count,
																					std::list<Tree>& match_list,
																					BinaryNode<Tree>* node) const {
	if (node == nullptr) {
		return match_list;
	} else if (samename(z, node->data)) {
		//	do a levelorder traversal from first match to find the other matches
		LevelOrderIterator<Tree> tree_it(node);
		match_list.push_back(node->data);
		++tree_it;
		int count = 1;
		while (!tree_it.end() && (count < spec_count)) {
			Tree current(*tree_it);
			if (samename(z, current)) {
				match_list.push_back(current);
				++count;
			}
			++tree_it;
		}
	} else if (islessname(z, node->data)) {
		findallmatches(z, spec_count, match_list, node->left_child);
	} else if (islessname(node->data, z)) {
		findallmatches(z, spec_count, match_list, node->right_child);
	}
	return match_list;
}

std::list<std::string>& AVL_Tree::all_in_zipcode(
    const int& zip, BinaryNode<Tree>* node, std::list<std::string>& match_list)
    const {
	if (node == nullptr) {
		return match_list;
	}
	all_in_zipcode(zip, node->left_child, match_list);
	if (zip == node->data.zip()) {
		match_list.push_back(node->data.common_name());
	}
	all_in_zipcode(zip, node->right_child, match_list);
	return match_list;
}

std::list<std::string>& AVL_Tree::all_nearby(const double& latitude, 
																						 const double& longitude, 
																						 const double& distance,
																						 BinaryNode<Tree>* node,
																						 std::list<std::string>& match_list) 
																						 const {
	if (node == nullptr) {
		return match_list;
	}
	all_nearby(latitude, longitude, distance, node->left_child, match_list);
	double tree_lat, tree_lon;
	node->data.get_position(tree_lat, tree_lon);
	if (distance >= haversine(latitude, longitude, tree_lat, tree_lon)) {
		match_list.push_back(node->data.common_name());
	}
	all_nearby(latitude, longitude, distance, node->right_child, match_list);
	return match_list;
}

void AVL_Tree::print(std::ostream& out, BinaryNode<Tree>* node) const {
	if (node == nullptr) {
		return;
	}
	print(out, node->left_child);
	out << node->data;
	print(out, node->right_child);
}

void AVL_Tree::clear(BinaryNode<Tree>*& node) {
	if (node == nullptr) {
		return;
	}
	clear(node->left_child);
	clear(node->right_child);
	delete node;
	node = nullptr;
}

void AVL_Tree::insert(const Tree& x, BinaryNode<Tree>*& node) {
	if (node == nullptr) {
		node = new BinaryNode<Tree>(x);
		//	add species to species_count_
		if (species_count_.find(x.common_name()) == species_count_.end()) {
			species_count_[x.common_name()] = 1;
		} else {
			++species_count_[x.common_name()];
		}
		return;
	} else if (x < node->data) {
		insert(x, node->left_child);
		if ((height(node->left_child) - height(node->right_child)) == 2) {
			if (x < node->left_child->data) {
				LL_rotate(node);
			} else {
				LR_rotate(node);
			}
		}
	} else if (node->data < x) {
		insert(x, node->right_child);
		if ((height(node->right_child) - height(node->left_child)) == 2) {
			if (node->right_child->data < x) {
				RR_rotate(node);
			} else {
				RL_rotate(node);
			}
		}
	} else {
		return;
	}
	node->height = std::max(height(node->left_child), height(node->right_child)) +
													1;
}

void AVL_Tree::remove(const Tree& x, BinaryNode<Tree>*& node) {
	if (node == nullptr) {
		return;
	} else if (x == node->data) {
		remove_node(node);
		--species_count_[x.common_name()];
	} else if (x < node->data) {
		remove(x, node->left_child);
		if (height(node->right_child) - height(node->left_child) == 2) {
			if (height((node->right_child)->right_child) >=
					height((node->right_child)->left_child)) {
				RR_rotate(node);
			} else {
				RL_rotate(node);
			}
		}
	} else if (node->data < x) {
		remove(x, node->right_child);
		if (height(node->left_child) - height(node->right_child) == 2) {
			if (height((node->left_child)->left_child) >=
					height((node->left_child)->right_child)) {
				LL_rotate(node);
			} else {
				LR_rotate(node);
			}
		}
	}
	if (node != nullptr) {
		node->height = std::max(height(node->left_child),
														height(node->right_child)) + 1;
	}
}

void AVL_Tree::remove_node(BinaryNode<Tree>*& node) {
	if (node->is_leaf()) {
		delete node;
		node = nullptr;
	} else if (node->left_child != nullptr && node->right_child != nullptr) {
		node->data = inorder_successor(node->right_child);
	} else {
		BinaryNode<Tree>* node_to_delete = node;
		if (node->left_child != nullptr) {
			node = node->left_child;
		} else if (node->right_child != nullptr) {
			node = node->right_child;
		}
		delete node_to_delete;
	}
}

Tree AVL_Tree::inorder_successor(BinaryNode<Tree>*& node) {
	if (node->left_child == nullptr) {
		Tree tree(node->data);
		remove_node(node);
		return tree;
	}
	inorder_successor(node->left_child);
}


void AVL_Tree::LL_rotate(BinaryNode<Tree>*& node) {
	BinaryNode<Tree>* new_root = node->left_child;
	node->left_child = new_root->right_child;
	new_root->right_child = node;
	node->height = std::max(height(node->left_child), height(node->right_child)) +
													1;
	new_root->height = std::max(node->height, height(new_root->right_child)) + 1;
	node = new_root;
}

void AVL_Tree::LR_rotate(BinaryNode<Tree>*& node) {
	RR_rotate(node->left_child);
	LL_rotate(node);
}

void AVL_Tree::RR_rotate(BinaryNode<Tree>*& node) {
	BinaryNode<Tree>* new_root = node->right_child;
	node->right_child = new_root->left_child;
	new_root->left_child = node;
	node->height = std::max(height(node->left_child), height(node->right_child)) +
													1;
	new_root->height = std::max(height(new_root->left_child), node->height) + 1;
	node = new_root;
}

void AVL_Tree::RL_rotate(BinaryNode<Tree>*& node) {
	LL_rotate(node->right_child);
	RR_rotate(node);
}

