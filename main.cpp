/*******************************************************************************
  Title          : main.cpp
  Author         : Lashana Tello
  Created on     : March 4, 2018
  Description    : Given two input files from the command line (the first is a 
		   						 csv document containing a tree and its information on each 
		   						 line from the 2015 NYC Tree Census and the other is a list 
		   					   of commands to execute with one command on each line), a 
		   						 TreeCollection object will be created and each tree from the 
		   						 census file will be inserted into the TreeCollection object. 
		   						 The TreeCollection object will then execute each command in 
		   						 the command file. A Command object is used to parse the file 
		   						 containing the list of commands, and get each command and its 
		   						 arguments from each line. The arguments are then given to the 
		   						 TreeCollection object method that corresponds to each command 
		   						 and the command is executed.									 
  Purpose        : To store the contents of a 2015 NYC Tree Census file in an 
		   						 object that represents a database and answer specific user 
		   						 queries pertaining to the database 
  Usage          : When running, provide two input files, the NYC Tree Census 
		   						 file and a file with a list of commands, respectively
  Build with     : g++ -std=c++11 -o main main.cpp tree.cpp avl.cpp 
		  						 tree_collection.cpp tree_species.o command.o
  Modifications  : 
 
*******************************************************************************/


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "tree.h"
#include "command.h"
#include "tree_collection.h"


int main(int argc, char* argv[]) {
	if(3 == argc) {
		std::ifstream tree_file;
		std::ifstream command_file;
		tree_file.open(argv[1]);
		command_file.open(argv[2]);
		if (tree_file.fail()) {
			std::cerr << "Unable to open tree census file: " << argv[1] << std::endl;
			exit(1);
		}
		if (command_file.fail()) {
			std::cerr << "Unable to open commands file: " << argv[2] << std::endl;
			exit(1);
		}

		std::string line;
		TreeCollection tree_collection;

		while(tree_file.is_open()) {
			std::getline(tree_file, line);
			if (tree_file.eof()) {
				break;
			}
			Tree new_tree(line);
			tree_collection.insert_tree(new_tree);
		}

		Command command;
    std::string treename;
    int zipcode;
    double latitude, longitude, distance;
    bool result;

		while (!command_file.eof()) {
			if (!command.get_next(command_file)) {
				if (!command_file.eof()) {
					std::cerr << "Could not get next command.\n";
				}
				return 1;
			}
			command.get_args(treename, zipcode, latitude, longitude, distance,
											 result);

			switch (command.type_of()) {
				case tree_info_cmmd:
					tree_collection.tree_info(treename);
					break;
				case listall_names_cmmd:
					tree_collection.list_all_names();
					break;
				case list_near_cmmd:
					tree_collection.list_all_near(latitude, longitude, distance);
					break;
				case listall_inzip_cmmd:
					tree_collection.list_all_in_zip(zipcode);
					break;
				case bad_cmmd:
					std::cout << "Invalid command." << std::endl;
					std::cout << std::endl;
					break;
				default:
					break;
			}
		}

		tree_file.close();
		command_file.close();
    
	} else if (3 < argc) {
		std::cerr << "ERROR: Too many arguments provided. ";
		std::cerr << "You must provide one input file and one command file, ";
		std::cerr << "respectively." << std::endl;
		exit(1);
	} else {
		std::cerr << "ERROR: Too few arguments. You must provide one input file ";
		std::cerr << "and one command file, respectively" << std::endl;
		exit(1);
	}
	return 0;
}
