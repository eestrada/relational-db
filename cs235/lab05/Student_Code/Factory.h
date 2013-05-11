#include "MazeInterface.h"
#pragma once
/*
	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/
//=======================================================================================
/*
	getMaze()

	Creates and returns an object whose class extends MazeInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "Maze", you might say, "return new Maze();".
*/
class Factory
{
public:
	static MazeInterface * getMaze();
};

//=======================================================================================
