#include <string>
#include <iostream>
#include <sstream>
#pragma once

using namespace std;

class MazeInterface{

public:
	MazeInterface(){}
	virtual ~MazeInterface(){}
	/**
	 * Create and store a random maze with an entry and exit point. (location [0,0,0] and [7,7,7] must have 1's in those spots.  The rest of the spots can be randomly 0 or 1.
	 */
	virtual void createRandomMaze() = 0;
	
	/**
	 * Read from the given file (see maze_sample.txt for format) and store it as a maze
	 * 
	 * @param fileName The file name of the file to be imported
	 * 
	 * @return true if the file was successfully read/imported, false if an error occurred when parsing/reading the file
	 */
	virtual bool importMaze(string fileName) = 0;
	
	/**
	 * Traverses the current maze in storage, storing the path taken to solve the maze if the maze was solvable.
	 * 
	 * @return true if the maze was solvable, false if unsolvable
	 */
	virtual bool traverseMaze() = 0;
	
	/**
	 * Returns the path from the most recently traversed maze. The string format should be each position taken 
	 * separated by newlines (see format on website).
	 * 
	 * @return the path to the most recent maze traversed
	 * 		if no maze has been solved yet, return an empty string
	 */
	virtual string getMazePath() = 0;
	
	/**
	 * Get the current maze stored in a single string (see website for format)
	 * 
	 * @return a string representation of your maze
	 */
	virtual string getMaze() = 0;
};