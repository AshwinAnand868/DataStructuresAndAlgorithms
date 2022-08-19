#include "wall.h"
#include "maze.h"

// Below is a recursive function which is called inside a wrapper function runMaze(). This function takes the same arguments as runMaze() that is a Maze object reference, path array which stores the correct locations to reach from start to end, starting cell and ending cell. Except there is one more argument which represents the index of the path array which is used to track current location in the path.
int run(Maze& theMaze, int path[], int fromCell, int end, int index)
{
	int pathLength = 0;
	int row = theMaze.getRow(fromCell);
	int col = theMaze.getCol(fromCell);
	int cellUp = theMaze.getCell(row - 1, col);
	int cellLeft = theMaze.getCell(row, col - 1);
	int cellRight = theMaze.getCell(row, col + 1);
	int cellDown = theMaze.getCell(row + 1, col);

	if (!theMaze.isMarked(fromCell))
	{
		theMaze.mark(fromCell);
		path[index] = fromCell;
	}

	if (fromCell == end)
	{
		pathLength = index + 1;
	}
	else
	{
		index++;
		if (!theMaze.isMarked(cellRight) && theMaze.canGo(fromCell, cellRight))
		{
			theMaze.mark(cellRight);

			path[index] = cellRight;
			pathLength = run(theMaze, path, cellRight, end, index);
		}

		if (pathLength == 0 && !theMaze.isMarked(cellDown) && theMaze.canGo(fromCell, cellDown))
		{
			theMaze.mark(cellDown);

			path[index] = cellDown;

			pathLength = run(theMaze, path, cellDown, end, index);
		}

		if (pathLength == 0 && !theMaze.isMarked(cellLeft) && theMaze.canGo(fromCell, cellLeft))
		{
			theMaze.mark(cellLeft);

			path[index] = cellLeft;

			pathLength = run(theMaze, path, cellLeft, end, index);
		}

		if (pathLength == 0 && !theMaze.isMarked(cellUp) && theMaze.canGo(fromCell, cellUp))
		{
			theMaze.mark(cellUp);

			path[index] = cellUp;
			pathLength = run(theMaze, path, cellUp, end, index);
		}

	}
	return pathLength;
}

// Wrapper function for recursive run() function
int runMaze(Maze& theMaze, int path[], int startCell, int endCell)
{

	int end = endCell;
	int pathLength = 0;
	int index = 0;
	

	pathLength = run(theMaze, path, startCell, end, index);
	return pathLength;
}