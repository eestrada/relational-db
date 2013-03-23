#include "Factory.h"
#include "Maze.hpp"

//You may add #include statments here
using namespace std;

/*
	Unlike all other documents provided, you may modify this document slightly (but do not change its name)
*/
//=======================================================================================
/*
	getMaze()

	Creates and returns an object whose class extends MazeInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "Maze", you might say, "return new Maze();".
*/
MazeInterface* Factory::getMaze()
{
	return new ede::Maze();//Modify this line
}
//=======================================================================================
