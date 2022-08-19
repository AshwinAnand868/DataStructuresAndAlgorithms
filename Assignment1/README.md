
Part 1

Sketching out final results of given operations performed on a linked list with sentinels.

Part 2

Implementing a template for a doubly linked list. This means that nodes in this list will have a pointer not only to the next node but also a pointer to the previous node. The data type that will be stored in this list should support the following operator: ==, !=, =, < and it is the responsibility of the person using this to implement them in their program. Since how the data stored in the linked list will be hidden from the programmer, there is the functionality of iterator that the person can use to traverse through the list. Iterators are available as const_iterator, which does not allow to change the data pointed by it and regular iterator, which makes updates possible.

Part 3

A maze implementation. All the functionality was already provided, just I had to develop runMaze(...) function in runmaze.cpp with a prototype as shown below:
int runMaze(Maze& theMaze, int path[], int startCell, int endCell)

This function will find a path from cell number startCell to cell number endCell. This function will "markup" theMaze with the path and stores that path in the array. It returns the number of cells along the pathway including both the starting cell and ending cell.
