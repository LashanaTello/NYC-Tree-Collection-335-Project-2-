/*******************************************************************************
  Title          : tree_species.h
  Author         : Stewart Weiss
  Created on     : February 28, 2018
  Description    : The header file for the TreeSpecies class
  Purpose        : Encapsulates the container that represent the set of trees
                   and the methods that interact with that set
  Usage          : 
  Build with     : 
  Modifications  : 


  Matching Rules
  string tree_to_find matches the species common name tree_type if any of the 
  following conditions are true:

  tree_to_find is exactly the same string as tree_type, ignoring case.

  If tree_to_find has no whitespace or hyphen characters (it is one word) then 
  if tree_type contains white space characters or hyphens and consists of the
  words 
      w_{1}, w_{2}, ..., w_{k}
  then tree_to_find is exactly one of the words 
      w_{1}  , w_{2} , ..., w_{k}.
  For example if tree_to_find is "Japanese", and tree_type is 
   "Japanese tree lilac", then tree_to_find matches tree_type.

  If tree_to_find has whitespace or hyphen characters, then then if tree_type 
  contains white space characters or hyphens and consists of the words
      w_{1}, w_{2}, ..., w_{k}
  then tree_to_find is some subsequence w_{i}w_{i+1}...w_{j}
  of the sequence of words
      w_{1}, w_{2}, ..., w_{k}
  So "tree lilac" matches "Japanese tree lilac", but "tree lilac" does not 
  match "lilac".

  Otherwise tree_to_find does not match tree_type. 
*******************************************************************************/


#ifndef __Tree_Species_H__
#define __Tree_Species_H__

#include <string>
#include <iostream>
#include <list>
#include <set>
#include <vector>
#define  MAXWORDS  10

using namespace std;

/** class SpeciesName
 *  This class is useful for tree species matching. 
 */
class SpeciesName {
public:
    /** SpeciesName(s) constructs the list of all words in s, to faciliate
     *  matching.
     *  @param string [in] s  is a string containing a species common name
     *  @return   This does not return a value; it constructs the object.
     */
    SpeciesName(string s);

    /** matches(s) checks if s matches the Species_Name
     *  @param string [in] s an initialized string 
     *  @return true if s matches according to the matching rules described
     *                    above.
     */
    bool matches( string s );

    /** print() prints the species common name on the given ostream
        @param ostream& [inout] out  is the output stream to be modified
     */
    void print( ostream & out );

private:
    int num_subwords;         // number of space or hyphen separated word in name
    string subwords[MAXWORDS];// array of words in name
    string name;              // original name
};



class TreeSpecies
{
public:
    /** TreeSpecies()
     *  A default constructor for the class that creates an empty TreeSpecies . 
     */
    TreeSpecies( );	

    /** A destructor for the class. 
     */
    ~TreeSpecies( );

	/** print() prints all stored species names on out, one per line
     *  This writes the set of all common names found in the data set to the 
     *  output stream out, one per line. There is no particular order in which 
     *  they are written.
     *  @param ostream& [inout]  out  the stream to be modified
     */
    void print_all_species(ostream & out) const; 	

    /** number_of_species() returns the number of distinct species names
     *  This returns the total number of distinct species common names found in 
     *  the data set.
     *  @return int  The number of species common names
     */
    int number_of_species() const;	

    /** add_species()  adds given name to the container
     *  This adds the species to the TreeSpecies container. 
     *  @param string s [in]  the string to be added.
     *  @return int It returns a 0 if the species was already in the 
     *              TreeSpecies container and a 1 if it was not.
     */
    int add_species( const string & species);	

    /**
     * This returns a list<string> object containing a list of all of the 
     * actual tree species that match a given parameter string partial_name. 
     * This method should be case insensitive. The list returned by this 
     * function should not contain any duplicate names and may be empty.
     */
    list<string> get_matching_species(const string & partial_name) const; 	

private:
    set<string>    treenames;          // set of all stored tree names
    int            tree_species_count; // number of stored names
};

#endif /* Tree_Species_H__ */

