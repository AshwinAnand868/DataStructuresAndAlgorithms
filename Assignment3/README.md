In this assignment, I implemented a BST called ThreadedTree along with "const_iterator" and "iterator". This kind of BST assumes pointers that would be normally nullptrs as threads that point at the next smallest (left pointer) or the next biggest node (right pointer) in the tree. This BST allows you to iterate through the tree through an iterator with the use of threads allowing you to go through nodes in an in-order manner. 

Data type of data stored in this tree should support the following operators: ==, !=, =, <, and default construction.

As there is a functionality of threads in this BST, there exists two boolean variables that tells whether a given pointer (either left or right) is a thread or not.
