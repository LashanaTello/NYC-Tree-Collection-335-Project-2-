/*******************************************************************************
  Title          : tree_collection.h
  Author         : Lashana Tello
  Created on     : March 1, 2018
  Description    : The interface file for the TreeCollection class
  Purpose        : To store all trees in the NYC Tree Census of 2015
  Usage          : To serve as a database of trees in NYC and allow user to 
									 query about information about a certain tree species, trees 
									 within a user-given distance, latitude, and longitude, and 
									 trees within a zipcode
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/


#ifndef __TREECOLLECTION_H__
#define __TREECOLLECTION_H__

#include "avl.h"
#include "tree_species.h"
#include "tree.h"
#include <utility>
#include <array>

/*******************************************************************************

		The TreeCollection class acts as database for the 2015 NYC Street Tree 
		Census. It encapsulates an AVL Tree, a TreeSpecies object, and an array that
		stores integers. The AVL Tree stores all the Tree objects. The TreeSpecies 
		object stores the common names of all the Tree species, which is the 
		spc_common member of each Tree object, and is responsible for determining 
		if a given string matches any of the species names it stores. The array 
		stores the number of Trees in New York City and the number of Trees in each 
		borough. The TreeCollection class must be used with an enumerated type 
		named Borough. A variable of type Borough can have a value equal to 
		ALLBOROS, MANHATTAN, BRONX, BROOKLYN, QUEENS, or STATEN. These enumerated 
		values will be used to represent the indices in the array. Which means each 
		index represents a borough. ALLBOROS represents data that includes all 5 
		boroughs. So, trees_by_borough_[ALLBOROS] returns the total number of 
		trees in New York City. This way you don't have to remember which spot in 
		the array stores information for which borough. Also, TreeCollection stores
		all dead Trees and stumps, so they will be inlcuded in all information
		that TreeCollection outputs. If the user wants to know about dead Trees 
		and stumps only, give TreeCollection's tree_info method a string 
		consisting of only a space character. When Trees are dead or stumps, they
		have no spc_common member. So, when their spc_common is output, it will be
		shown as "Unknown".

*******************************************************************************/

typedef std::list<std::string> string_list;
typedef std::pair<std::string, int> string_int_pair;

enum Borough {
		ALLBOROS = 0,
		MANHATTAN,
		BRONX,
		BROOKLYN,
		QUEENS,
		STATEN
	};

class TreeCollection {
 public:
	//	Default constructor for TreeCollection object
	TreeCollection();

	//	Destructor for TreeCollection object
	~TreeCollection();

	//	Returns the total number of trees stored in the TreeCollection object
	int total_tree_count() const;

	//	Returns the number of trees whose spc_common equals species_name 
	//	Returns 0 if no trees have species_name for an spc_common
	//	This method is case insensitive
	int count_of_tree_species(const std::string& species_name) const;

	//	Returns the number of trees in boro_name 
	//	Returns 0 if boro_name is not a New York borough
	//	This method is case insensitive
	int count_of_trees_in_boro(const std::string& boro_name) const;

	//	Returns a list containing the spc_common members of Tree objects that 
	//	match species_name. If no Tree objects have an spc_common that matches 
	//	species_name, the list will be empty
	string_list get_matching_species(const std::string& species_name) const;

	//	Returns a list containing the spc_common members of Tree objects in the 
	//	given zipcode. If no trees exist in that zipcode or 
	//	the zipcode is invalid, the list will be empty
	string_list get_all_in_zipcode(int zipcode) const;

	//	Returns a list containing the spc_common members of Tree objects within
	//	the given distance (in kilometers) of the given latitude and longitude 
	//	point. If no trees exist within the given distance of the given 
	//	coordinates, the list will be empty
	string_list get_all_near(double latitude, double longitude, double distance)
											     const;

	//	Returns true if TreeCollection object contains no Trees
	bool empty() const;

	//	Adds the given tree to the TreeCollection object's AVL_Tree
	void insert_tree(const Tree& tree);

	//	Returns the corresponding Borough value for the given boro
	//	This method is only to be used on trees within the TreeCollection since 
	//	those trees are in one of the five boroughs in New York
	Borough convert_to_tree_borough(const std::string& boro) const;

	//	Outputs information about Tree objects whose spc_common matches 
	//	partial_name according to TreeSpecies matching method
	//	Outputs: 
	//	1) the total number of these Trees in NYC versus the number of all Trees 
	//	in NYC, 
	//	2) how many of these Trees are in each borough versus how many total Trees
	//	in the TreeCollection are in each borough, and 
	//	3) the percentage of these Trees in all of NYC and in each borough
	void tree_info(const std::string& partial_name) const;

	//	Goes through match_list (which contains a list of Tree spc_common members)
	//	and for each spc_common, this method gets a list of Trees that have the 
	//	same spc_common member. This method then goes through that list of trees 
	//	and calculates the number of these Trees in New York and in each brorough
	//	Once it's gone through all of match_list, it calculates the percentage of 
	//	all the Tree species in match_list in New York and in each borough
	void total_occurrences(const string_list& match_list, double& ny_total, 
                         double& man_total, double& bx_total, double& bk_total, 
                         double& q_total, double& stat_total, double& ny_percent,
                         double& man_percent, double& bx_percent,
                         double& bk_percent, double& q_percent,
                         double& stat_percent) const;

	//	Outputs all the spc_common members of the Trees in TreeCollection object
	void list_all_names() const;
	
	//	Outputs spc_common member of the Trees found in the given zipcode and 
	//	how many times that spc_common is found in that zipcode
	void list_all_in_zip(int& zipcode) const;

	//	Outputs spc_common member of the Trees found within the given distance 
	//	(in kilometers) of the given latitude and longitude, and how many times 
	//	that spc_common is found within the given distance of the given
	//	coordinates
	void list_all_near(double& latitude, double& longitude, double& distance) 
										 const;
	
	//	Goes through matches (which contains duplicates of various spc_common 
	//	names) and counts how many times each spc_common appears in matches 
	//	This method returns a vector of string and int pairs. Each string is the 
	//	spc_common member of a Tree and the int is how many times that spc_common 
	//	was found in matches
	std::vector<string_int_pair> count_duplicates(const string_list& matches)
																								const;

 private:
	//	Stores all the Tree objects and uses a Tree's spc_common as the primary 
	//	key and its tree_id as the secondary key to order the Tree objects
	AVL_Tree trees_;

	//	Stores a list of the spc_common members of all the Trees found in trees_
	TreeSpecies all_species_;

	//	Contains the number of Trees found in New York City and in each borough 
	//	Each borough is assigned a spot in the array. When you access a value in 
	//	the array using the enumerated type Borough, it will return the number of 
	//	Trees in that borough. For example, trees_by_borough_[QUEENS] returns the 
	//	total number of Trees in Queens. This way you don’t have to remember which
	//	number in the array represents which borough
	std::array<int, 6> trees_by_borough_;
};

#endif
