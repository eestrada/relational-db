#ifndef _MAZE_HPP_
#define _MAZE_HPP_

#include <string>
#include <iostream>
#include <sstream>

namespace ede
{

class Maze : public MazeInterface
{

public:
	Maze(){}
	virtual ~Maze(){}
	/**
	 * Create and store a random maze with an entry and exit point. (location [0,0,0] and [7,7,7] must have 1's in those spots.  The rest of the spots can be randomly 0 or 1.
	 */
	virtual void createRandomMaze();
	
	/**
	 * Read from the given file (see maze_sample.txt for format) and store it as a maze
	 * 
	 * @param fileName The file name of the file to be imported
	 * 
	 * @return true if the file was successfully read/imported, false if an error occurred when parsing/reading the file
	 */
	virtual bool importMaze(std::std::string fileName);
	
	/**
	 * Traverses the current maze in storage, storing the path taken to solve the maze if the maze was solvable.
	 * 
	 * @return true if the maze was solvable, false if unsolvable
	 */
	virtual bool traverseMaze();
	
	/**
	 * Returns the path from the most recently traversed maze. The string format should be each position taken 
	 * separated by newlines (see format on website).
	 * 
	 * @return the path to the most recent maze traversed
	 * 		if no maze has been solved yet, return an empty string
	 */
	virtual std::string getMazePath();
	
	/**
	 * Get the current maze stored in a single string (see website for format)
	 * 
	 * @return a string representation of your maze
	 */
	virtual std::string getMaze();
}; // End Maze class declaration

}; // End ede namespace

#endif // defined _MAZE_HPP_
