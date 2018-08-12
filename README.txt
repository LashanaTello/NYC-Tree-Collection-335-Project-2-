/*******************************************************************************
  Title          : README.txt
  Author         : Lashana Tello
  Created on     : March 1, 2018
  Description    : Text file documenting my roadblocks working on Project 2
  Purpose        : To document my struggles
  Usage          : To learn from my previous mistakes when writing code in the
									 future
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

3/1: Adding new Tree class methods and testing them. They work with no problems.

3/5: Starting to write AVL_Tree class.

3/12: Finished AVL_Tree class. Starting TreeCollection class.

3/15: Finished TreeCollection. Testing AVL_Tree. Everything but the 
findallmatches method is working.

3/17 10:13 am: Testing the commandtester.cpp file to see how it works. I don't 
think we could find trees with the empty string for an spc_common because when 
I type tree_info and press enter, I get an error. When I type tree_info with 
just a space right after it, it prints all the trees in the TreeSpecies 
container. If I decide to let that space character mean that the user wants to 
know about trees with no spc_common, then I could give the user information 
about all the trees with no spc_common.

3/19 11:16 am: I'm adding a map that will store how many times each tree species
appears in the AVL Tree. This will tell me when to stop searching for matches 
and I don't have to go through the entire AVL Tree. I'm going to make the AVL 
Tree keep track of how many times each species appears in its tree. If 
TreeCollection keeps track of it, then I have to give the AVL Tree the count of 
that species for its findallmatches method and I'm not allowed to change its 
parameters.

3/19 12:30 pm: In the AVL Tree's findallmatches, I'm trying to use a level order 
traversal from the first node with a matching spc_common. But, I keep getting a 
"segmentation fault (core dumped)" error once I do two to five iterations 
through the while loop. I added cout statements to keep track of how far the 
program gets and figure out where exactly the error is. The segmentation fault 
occurs when I check the while loop condition, which checks if the level order 
iterator is not at the end and if the current number of matches is less than the 
number of trees whose spc_common is equal to the one I need to find matches for. 
I had to stop because I had to go to work.

3/20 3:47 pm: Still stuck on that error. Since I created a level order iterator 
class, perhaps my error is in the prefix operator++() method. So I will use a 
linked queue directly in the AVL findallmatches method to do a level order 
traversal. I still get a segmentation fault (core dumped) error. The error is 
occurring in the same spot as before. That spot is the while loop, which checks 
if the queue is empty and if current count is less than spec_count. I always 
check if the node is a nullptr before I enqueue it, so I'm not understanding 
what the issue is.

3/22 2:32 pm: This doesn't make any sense. I don't know what's happening between
the end of the while loop and before it checks the condition again. I decided to 
look at my LinkedQueue class because the error could be there but I didn't find 
any errors. My peek() method can definitely cause problems if you call it on an 
empty queue but the queue is never empty when I call peek(), so I really have no 
clue what's going on.

3/23 6:37 pm: I decided to create a separate function in the AVL tree that 
prints out the trees in level order. If this function gives me an error, then I 
know it's my code. This function gave me no error. It printed all the trees just 
fine. After thoroughly looking through my level order iterator class, I don't 
see any bugs. I would say that maybe it could be the way I'm deciding to find 
out if a node's tree's spc_common matches the given tree. But, I don’t think 
that's it because it always segment faults at the end of the while loop or when 
it evaluates the while loop condition. I'll probably have to approach finding 
tree matches differently. Once I find a node with a matching tree, I'll do a 
preorder traversal until I find the correct number of matches. I hope it works.

3/23 11:44 pm: Tried a preorder traversal in findallmatches and I'm still 
getting a segmentation fault (core dumped) error. The rest of the AVL Tree 
methods work with no problems.

3/24 11:25 am: I finally fixed findallmatches and the error was that I didn't 
put a return value at the end of the function. I googled "searching tree gives 
segmentation fault" and someone on stackoverflow.com had the same problem. Wow. 
Testing TreeCollection. TreeCollection works fine. Building main.

3/26: Adding comments where necessary.

3/28: Adding method prologues. Testing entire program.
