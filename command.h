/******************************************************************************
  Title          : command.h
  Author         : Stewart Weiss
  Created on     : March  14, 2018
  Description    : Interface for the command class
  Purpose        : The Command class represents a command object
  Modifications  : 

  Notes:
  This header file provides the interface to the Command class, as well as to
  a few types that are required in order to use this class, specifically the 
  following enumerated type:
    Command_type

  All of the member functions required to utilize this class are here. 
  There is no need to modify this class and it should not be modified!

  The accompanying test driver, commandtester.cpp, show how you can use this 
  class.  In essence, you create a Command object and then repeatedly call
  the get_next() method passing the input stream containing the commands.
  Use type_of() and get_args() to get the command type and its associated
  argument list.

 
******************************************************************************/
#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <iostream>

using namespace std;

/*******************************************************************************   
                                 Exported Types
*******************************************************************************/

/** Command_type: 
    An enumerated type to represent the different types of commands. This is  
    more efficient than storing command types as strings. Notice that the last
    value of the type is num_Command_types, which is simply a count of how many
    values the type contains. It is a useful method of counting, because as long
    as you insert new values before it, it remains valid.
*/
typedef enum   
{
    tree_info_cmmd = 0,
    listall_names_cmmd,
    listall_inzip_cmmd,
    list_near_cmmd,
    bad_cmmd,
    null_cmmd,
    num_Command_types
} Command_type;



/*******************************************************************************   
                              Command Class Interface
*******************************************************************************/

class Command
{
public:
    /** Command()  A default constructor for the class 
     */
    Command ();

    /** get_next(istream & in) resets the values of the command object on
     * which it is called to the values found at the current read pointer of 
     * the istream in, provided in.eof() is false.
     * @param istream in [inout]  an istream already opened for reading
     * @pre   istream in is open for reading and in.eof() is false
     * @post  If in.eof() is false on entry to this constructor, then
     *        the command is re-initialized to the values found in the input
     *        stream in, and the istream pointer is advanced to the next line. 
     *        If the command is invalid, then when typeof() is called on it, 
     *        it will return bad_command. 
     *        If in.eof() is true on entry, then the Command_type is set
     *        to null and the remaining values are undefined.
     * @return true if the command was initialized to something other than a
     *        bad_command, and false otherwise.
     */
    bool get_next (istream & in );

    /** typeof() returns the type of the Command on which it is called.
     * @pre  None
     * @post None, as this is a const method
     * @return A value of Command_type, depending on the type of the command
             object.
     */
    Command_type type_of () const;

    /** args() sets the values of its parameters to the argument values of
     * the Command object on which it is called. If the Command object is a 
     * bad_command or null command then the result is set to false and the 
     * remaining parameter values are undefined. Otherwise, the Command_type 
     * should be one of the valid commands of the Command_type enumeration
     * and the appropriate argument values are retrieved from the current
     * Command object,  meaning:
     * if tree_info_cmmd, then tree_to_find 
     * if listall_names_cmmd, then nothing
     * if listall_inzip_cmmd, then the zipcode
     * if list_near_cmmd, then the latitude,longitude, and distance,
     * @pre  Command_type is initialized to a valid value
     * @post Either result == false or all members are
     *       set to the values in the object.
     */ 
    void  get_args (
                string    & arg_tree_to_find,
                int       & arg_zip,
                double    & arg_latitude, 
                double    & arg_longitude, 
                double    & arg_distance, 
                bool      & result
                ) const;

private:
    Command_type type;       // The type of the Command object
    string       tree_to_find;   
    int          zip;
    double       latitude;
    double       longitude;
    double       distance;
};

#endif /* __COMMAND_H__ */

