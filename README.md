# Project 2: NYC Tree Collection
## CSCI 335

This project can be viewed [here](http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/csci335/assignments/project2.pdf).

### Description
For this project, the goal was to create something like a database for all the trees in New York City and allow users to query the database. 

The queries users can make are:
- get the total number of trees in a specific borough
- get the total number of trees that are a certain species
- get the total number of trees in a zipcode
- get all the names of all the tree species in NYC
- get all trees within a specific distance of latitude-longitude coordinates

This project could be useful for environmental groups. Perhaps they want to replace all the dead trees in NYC and plant new ones. This program will tell them how many dead trees are in NYC and will help them find them.

(_**Note**: the data file storing all the trees in NYC is too big to upload here. It can be found [here](https://data.cityofnewyork.us/Environment/2015-Street-Tree-Census-Tree-Data/uvpi-gqnh) and you can export it as a CSV file. But, the data on trees in Manhattan only is small enough to upload so only that is in this repository._)

### How To Use
Download the zip file for this repository. Open a terminal and go to the directory containing all the project files in this zip. Type "make all" to compile the project. Type "./project2 name_of_trees_file.csv name_of_file_with_commands_in_it" to run the project. The name_of_trees_file.csv contains the trees used to create the tree collection. In this repository, there's a file named "2015_trees_MH.csv", which contains all trees in Manhattan only, and there's "test.csv", which contains a very small portion of the tree data and can be used to test the program. The "name_of_file_with_commands_in_it" file will contain commands and their arguments, which the user wants to search for. In this repository, there's "commandtest_MH", "commandtest_QN", and "test.txt", which you can use to test the program or see what the output would be. You can create your own command file using the guidelines listed in the [assignment in Section 4.2](http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/csci335/assignments/project2.pdf#subsection.4.2).
