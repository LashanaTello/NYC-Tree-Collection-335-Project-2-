/*******************************************************************************
  Title          : tree.cpp
  Author         : Lashana Tello
  Created on     : February 23, 2018
  Description    : The implementation file for the Tree class
  Purpose        : To provide a means of representing a single tree in New York
                   City
  Usage          : Use to store data from NYC Tree Census
  Build with     : g++ -c -std=c++11 tree.cpp 
  Modifications  : March 1, 2018
									 Added new method implementations
 
*******************************************************************************/

#include <iomanip>
#include <sstream>
#include <iostream>
#include "tree.h"
#include <string>

Tree::Tree() {
	spc_common_ = "";
	tree_id_ = 0;
	tree_dbh_ = 0;
	status_ = "";
	health_ = "";
	address_ = "";
	boroname_ = "";
	zipcode_ = 0;
	latitude_ = 0;
	longitude_ = 0;
}

Tree::Tree(const std::string& treedata) {
	std::string data;
	int count = 1;
	std::istringstream line(treedata);
	std::stringstream convert;
	//	Extract the specific information we need from specific columns/spots in
	//	the treedata string using stringstream to convert the string data
	while ((std::getline(line, data, ',')) && (40 > count)) {
		if (1 == count) {
			convert << data << " ";
			convert >> tree_id_;
		} else if (4 == count) {
			convert << data << " ";
			convert >> tree_dbh_;
		} else if (7 == count) {
			status_ = data;
		} else if (8 == count) {
			health_ = data;
		} else if (10 == count) {
			spc_common_ = data;
		} else if (25 == count) {
			if (isdigit(data[0])) {
				address_ = data;
			} else {
				//	The column right before the address column may have more than one
				//	piece of data separated by commas. We need to skip over this data to
				//	get the address. The address always begins with a number so we will 
				//	read until we get data that begins with a number, which will be the 
				//	address
				while (!isdigit(data[0])) {
					std::getline(line, data, ',');
				}
				address_ = data;
			}
		} else if (26 == count) {
			convert << data << " ";
			convert >> zipcode_;
		} else if (30 == count) {
			boroname_ = data;
		} else if (38 == count) {
			convert << data << " ";
			convert >> latitude_;
		} else if (39 == count) {
			convert << data;
			convert >> longitude_;
		}
		convert.str(std::string());	//	clear the stringstream
		++count;
	}
}

Tree::Tree(int id, int diam, std::string status, std::string health,
           std::string spc, int zip, std::string addr, std::string boro, 
           double latitude, double longitude) {
	spc_common_ = spc;
	tree_id_ = id;
	tree_dbh_ = diam;
	status_ = status;
	health_ = health;
	address_ = addr;
	boroname_ = boro;
	zipcode_ = zip;
	latitude_ = latitude;
	longitude_ = longitude;
}

Tree::Tree(const Tree& other_tree) {
	spc_common_ = other_tree.spc_common_;
	tree_id_ = other_tree.tree_id_;
	tree_dbh_ = other_tree.tree_dbh_;
	status_ = other_tree.status_;
	health_ = other_tree.health_;
	address_ = other_tree.address_;
	boroname_ = other_tree.boroname_;
	zipcode_ = other_tree.zipcode_;
	latitude_ = other_tree.latitude_;
	longitude_ = other_tree.longitude_;
}

Tree::~Tree() {
}

bool operator==(const Tree& t1, const Tree& t2) {
	if ((t1.spc_common_ == t2.spc_common_) && (t1.tree_id_ == t2.tree_id_)) {
		return true;
	} else {
		return false;
	}
}

bool operator<(const Tree& t1, const Tree& t2) {
	if (t1.spc_common_ < t2.spc_common_) {
		return true;
	} else if (t1.spc_common_ == t2.spc_common_) {
		if (t1.tree_id_ < t2.tree_id_) {
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Tree& t) {
	os << t.spc_common_ << ", ";
	os << t.tree_id_ << ", ";
	os << t.tree_dbh_ << ", "; 
	os << t.status_ << ", ";
	os << t.health_ << ", ";
	os << t.address_ << ", ";
	os << t.boroname_ << ", ";
	os << std::setfill('0') << std::setw(5) << t.zipcode_ << ", ";
	os << std::setprecision(10) << t.latitude_ << ", ";
	os << std::setprecision(10) << t.longitude_ << std::endl;
	return os;
}

bool samename(const Tree& t1, const Tree& t2) {
	if (t1.spc_common_ == t2.spc_common_) {
		return true;
	} else {
		return false;
	}
}

bool islessname(const Tree& t1, const Tree& t2) {
	if (t1.spc_common_ < t2.spc_common_) {
		return true;
	} else {
		return false;
	}
}

Tree& Tree::operator=(const Tree& other_tree) {
	spc_common_ = other_tree.spc_common_;
	tree_id_ = other_tree.tree_id_;
	tree_dbh_ = other_tree.tree_dbh_;
	status_ = other_tree.status_;
	health_ = other_tree.health_;
	address_ = other_tree.address_;
	boroname_ = other_tree.boroname_;
	zipcode_ = other_tree.zipcode_;
	latitude_ = other_tree.latitude_;
	longitude_ = other_tree.longitude_;
	return *this;
}

bool Tree::operator!=(const Tree& other_tree) {
	if ((spc_common_ != other_tree.spc_common_) && 
			(tree_id_ == other_tree.tree_id_)) {
		return true;
	}
	return false;
}

std::string Tree::common_name() const {
	return spc_common_;
}

std::string Tree::borough_name() const {
	return boroname_;
}

std::string Tree::nearest_address() const {
	return address_;
}

int Tree::diameter() const {
	return tree_dbh_;
}

int Tree::zip() const {
	return zipcode_;
}

void Tree::get_position(double& latitude, double& longitude) const {
	latitude = latitude_;
	longitude = longitude_;
}
