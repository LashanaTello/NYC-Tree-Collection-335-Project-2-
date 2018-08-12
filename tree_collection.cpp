/*******************************************************************************
  Title          : tree_collection.cpp
  Author         : Lashana Tello
  Created on     : March 1, 2018
  Description    : The implementation file for the TreeCollection class
  Purpose        : To provide a means of representing a single tree in New York
                   City
  Usage          : Use to store data from NYC Tree Census
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#include "tree_collection.h"
#include <iostream>
#include <iomanip>
#include <vector>

TreeCollection::TreeCollection() : trees_(), all_species_()
{
	trees_by_borough_.fill(0);
}

TreeCollection::~TreeCollection()
{
}

int TreeCollection::total_tree_count() const {
	return trees_by_borough_[ALLBOROS];
}

int TreeCollection::count_of_tree_species(const std::string& species_name) const
{
	if (trees_.empty()) {
		return 0;
	}
	string_list matches = all_species_.get_matching_species(species_name);
	int total = 0;
	for (string_list::iterator it = matches.begin(); it != matches.end(); ++it) {
		total += trees_.count_species(*it);
	}
	return total;
}

int TreeCollection::count_of_trees_in_boro(const std::string& boro_name) const {	
	std::string boro = boro_name;
	for (char& c : boro) {
		if (isupper(c)) {
			c = tolower(c);
		}
	}

	if ("manhattan" == boro) {
		return trees_by_borough_[MANHATTAN];
	} else if ("bronx" == boro) {
		return trees_by_borough_[BRONX];
	} else if ("brooklyn" == boro) {
		return trees_by_borough_[BROOKLYN];
	} else if ("queens" == boro) {
		return trees_by_borough_[QUEENS];
	} else if ("staten island" == boro) {
		return trees_by_borough_[STATEN];
	} 
	return 0;
}

string_list TreeCollection::get_matching_species(
    const std::string& species_name) const {
	return all_species_.get_matching_species(species_name);
}

string_list TreeCollection::get_all_in_zipcode(int zipcode) const {
	return trees_.all_in_zipcode(zipcode);
}

string_list TreeCollection::get_all_near(double latitude, double longitude,
                                         double distance) const {
	return trees_.all_nearby(latitude, longitude, distance);
}

bool TreeCollection::empty() const {
	if (trees_.empty()) {
		return true;
	}
	return false;
}

void TreeCollection::insert_tree(const Tree& tree) {
	trees_.insert(tree);
	all_species_.add_species(tree.common_name());
	Borough b = convert_to_tree_borough(tree.borough_name());
	++trees_by_borough_[b];
	++trees_by_borough_[ALLBOROS];
	return;
}

//	this method optimizes the running time of comparisons by taking advantage
//	of the uniqueness of the borough words. This method will only be used to
//	convert whole borough names that ALREADY EXIST IN THE AVL_TREE into their 
//	corresponding enumerated values. Seeing if two characters are equal to each 
//	other is faster than seeing if entire strings are equal to each other
//	This function uses the process of elimination to determine a borough's 
//	corresponding enumerated value
Borough TreeCollection::convert_to_tree_borough(const std::string& boro) const {
	if ('M' == boro.front()) {
		return MANHATTAN;
	} else if ('x' == boro.back()) {
		return BRONX;
	} else if ('B' == boro.front()) {
		return BROOKLYN;
	} else if ('Q' == boro.front()) {
		return QUEENS;
	}
	return STATEN;
}

void TreeCollection::tree_info(const std::string& partial_name) const {
	string_list matches;
	//	check if partial name equals " " (a single whitespace character), which 
	//	we consider equal to the empty string
	if (partial_name == " ") {
		matches.push_back("");
	} else {
		matches = all_species_.get_matching_species(partial_name);
		if (matches.empty()) {
			std::cout << "No " << partial_name << " trees were found." << std::endl;
			std::cout << std::endl;
			return;
		}
	}

	
	double total_in_ny = 0, total_in_man = 0, total_in_bx = 0, total_in_bk = 0;
	double total_in_q = 0, total_in_stat = 0;
	double percent_ny = 0, percent_man = 0, percent_bx = 0, percent_bk = 0; 
	double percent_q = 0, percent_stat = 0;

	total_occurrences(matches, total_in_ny, total_in_man, total_in_bx,
                    total_in_bk, total_in_q, total_in_stat, percent_ny,
                    percent_man, percent_bx, percent_bk, percent_q,
                    percent_stat);

	if (partial_name == " ") {
		std::cout << "Unknown" << std::endl;
		std::cout << "All dead trees or stumps:" << std::endl;
	} else {
		std::cout << partial_name << std::endl;
		std::cout << "All matching species:" << std::endl;
		for (string_list::iterator it = matches.begin(); it != matches.end(); ++it) 
		{
			std::cout << *it << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "Frequency by borough:" << std::endl;

	//	output data neatly

	std::cout << std::fixed;
	std::cout << "Total in NYC:";
	std::cout << " ";
	std::cout.width(12);
	std::cout << total_in_ny;
	std::cout << " (" << trees_by_borough_[ALLBOROS] << ")" << "	";
	std::cout.width(15);
	std::cout << std::setprecision(2) << percent_ny << "%" << std::endl;

	std::cout << "Manhattan:";
	std::cout << "	";
	std::cout.width(10);
	std::cout << total_in_man;
	std::cout << " (" << trees_by_borough_[MANHATTAN] << ")" << "	";
	std::cout.width(15);
	std::cout << std::setprecision(2) << percent_man << "%" << std::endl;

	std::cout << "Bronx:";
	std::cout << "	";
	std::cout.width(18);
	std::cout << total_in_bx;
	std::cout << " (" << trees_by_borough_[BRONX] << ")" << "	";
	std::cout.width(15);
	std::cout << std::setprecision(2) << percent_bx << "%" << std::endl;

	std::cout << "Brooklyn:";
	std::cout << "	";
	std::cout.width(10);
	std::cout << total_in_bk;
	std::cout << " (" << trees_by_borough_[BROOKLYN] << ")" << "	";
	std::cout.width(15);
	std::cout << std::setprecision(2) << percent_bk << "%" << std::endl;

	std::cout << "Queens:";
	std::cout << "	";
	std::cout.width(18);
	std::cout << total_in_q;
	std::cout << " (" << trees_by_borough_[QUEENS] << ")" << "	";
	std::cout.width(15);
	std::cout << std::setprecision(2) << percent_q << "%" << std::endl;

	std::cout << "Staten Island:";
	std::cout << "	";
	std::cout.width(10);
	std::cout << total_in_stat;
	std::cout << " (" << trees_by_borough_[STATEN] << ")" << "	";
	std::cout.width(15);
	std::cout << std::setprecision(2) << percent_stat << "%" << std::endl;
	std::cout << std::endl;
}

void TreeCollection::total_occurrences(const string_list& match_list,
                                       double& ny_total, double& man_total, 
                                       double& bx_total, double& bk_total, 
                                       double& q_total, double& stat_total,
                                       double& ny_percent, double& man_percent, 
                                       double& bx_percent, double& bk_percent, 
                                       double& q_percent, double& stat_percent)
																			 const {
	for (auto it1 = match_list.begin(); it1 != match_list.end(); 
       ++it1) {
		Tree tree(0, 0, "", "", *it1, 0, "", "", 0, 0);
		std::list<Tree> tree_matches = trees_.findallmatches(tree);
		ny_total += tree_matches.size();

		for (std::list<Tree>::iterator it2 = tree_matches.begin(); 
         it2 != tree_matches.end(); ++it2) {
			Tree t(*it2);
			Borough b = convert_to_tree_borough(t.borough_name());
			switch (b) {
				case MANHATTAN:
					++man_total;
					break;
				case BRONX:
					++bx_total;
					break;
				case BROOKLYN:
					++bk_total;
					break;
				case QUEENS:
					++q_total;
					break;
				case STATEN:
					++stat_total;
					break;
				default:
					break;
			}
		}
	}

	ny_percent = (ny_total / trees_by_borough_[ALLBOROS]) * 100;

	if (0 != trees_by_borough_[MANHATTAN]) {
		man_percent = (man_total / trees_by_borough_[MANHATTAN]) * 100;
	}

	if (0 != trees_by_borough_[BRONX]) {
		bx_percent = (bx_total / trees_by_borough_[BRONX]) * 100;
	}

	if (0 != trees_by_borough_[BROOKLYN]) {
		bk_percent = (bk_total / trees_by_borough_[BROOKLYN]) * 100;
	}

	if (0 != trees_by_borough_[QUEENS]) {
		q_percent = (q_total / trees_by_borough_[QUEENS]) * 100;
	}

	if (0 != trees_by_borough_[STATEN]) {
		stat_percent = (stat_total / trees_by_borough_[STATEN]) * 100;
	}
}

void TreeCollection::list_all_names() const {
	all_species_.print_all_species(std::cout);
	std::cout << std::endl;
}
	
void TreeCollection::list_all_in_zip(int& zipcode) const {
	string_list matches = get_all_in_zipcode(zipcode);
	if (matches.empty()) {
		std::cout << "No trees found in zipcode: ";
		std::cout << std::setfill('0') << std::setw(5) << zipcode << std::endl;
		std::cout.copyfmt(std::ios(nullptr));	//	reset cout stream manipulators
		std::cout << std::endl;
		return;
	}
	std::vector<string_int_pair> zip_matches = count_duplicates(matches);

	std::cout << "Trees found in zipcode ";
	std::cout << std::setfill('0') << std::setw(5) << zipcode << ":" << std::endl;
	for (unsigned int i = 0; i < zip_matches.size(); ++i) {
		if (zip_matches[i].first == "") {
			std::cout << "Unknown: ";
		} else {
			std::cout << zip_matches[i].first << ": ";
		}
		std::cout << zip_matches[i].second << std::endl;
	}
	std::cout.copyfmt(std::ios(nullptr));
	std::cout << std::endl;
}

void TreeCollection::list_all_near(double& latitude, double& longitude,
                                   double& distance) const {
	string_list matches = get_all_near(latitude, longitude, distance);
	if (matches.empty()) {
		std::cout << "No trees found within " << distance << " kilometers of ";
		std::cout << std::setprecision(10) << latitude << " and ";
		std::cout << std::setprecision(10) << longitude << std::endl;
		std::cout.copyfmt(std::ios(nullptr));
		std::cout << std::endl;
		return;
	}
	std::vector<string_int_pair> nearby = count_duplicates(matches);

	std::cout << "Trees found within " << distance << " kilometers of ";
	std::cout << std::setprecision(10) << latitude << " and ";
	std::cout << std::setprecision(10) << longitude << ":" << std::endl;
	for (unsigned int i = 0; i < nearby.size(); ++i) {
		if (nearby[i].first == "") {
			std::cout << "Unknown: ";
		} else {
			std::cout << nearby[i].first << ": ";
		}
		std::cout << nearby[i].second << std::endl;
	}
	std::cout.copyfmt(std::ios(nullptr));
	std::cout << std::endl;
}

std::vector<string_int_pair> TreeCollection::count_duplicates(
    const string_list& match_list) const {
	std::vector<string_int_pair> match_info;
	string_int_pair pair("random", 1);
	int count = -1;

	for (auto it = match_list.begin(); it != match_list.end();
       ++it) {
		if (pair.first != *it) {
			pair.first = *it;
			match_info.push_back(pair);
			++count;
		} else {
			++match_info[count].second;
		}

	}
	return match_info;
}
