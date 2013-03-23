#pragma once
#include "JosephusInterface.h"

using namespace std;

/*
	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/
//=======================================================================================
/*
	getGame()

	Creates and returns an object whose class extends JosephusInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "Circle", you might say, "return new Circle();".
*/
class Factory
{
	public:
		static 	JosephusInterface * getGame();
};
//=======================================================================================
