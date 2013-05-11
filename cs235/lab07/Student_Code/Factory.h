#include "MimicInterface.h"
#pragma once
/*
	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/
//=======================================================================================
/*
	createMimic()

	Creates and returns an object whose class extends MimicInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "Mimic", you might say, "return new Mimic();".
*/
class Factory
{
public:
	static MimicInterface* createMimic();
};

//=======================================================================================
