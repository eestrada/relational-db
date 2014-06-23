//#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Arena.h"

#include "Archer.h"
#include "Cleric.h"
#include "Robot.h"
using namespace std;
	/*
		addFighter(string)

		Adds a new fighter to the collection of fighters in the arena. Do not allow 
		duplicate names.  Reject any string that does not adhere to the format 
		outlined in the lab specs.

		Return true if a new fighter was added; false otherwise.
	*/
    bool Arena::addFighter(string info)
	{
        FighterInterface* fighterPtr;
		stringstream sstrm(info);
		string name;
		char type;
		int maxhp, stren, spd, mgc;
		
		sstrm >> name;
		sstrm >> type;
		sstrm >> maxhp;
		sstrm >> stren;
		sstrm >> spd;
		sstrm >> mgc;
		
        //Check if string is formatted correctly.
		if(sstrm.fail() || !sstrm.eof())
			{return false;}
		
		//Check if values are non-negative
		if(maxhp <= 0 || stren <= 0 || spd <= 0 || mgc <= 0)
			{return false;}
	    
        //Check if fighter already exists in arena.	
        if(fightervec.size()>0)
        {
            for(unsigned int i=0; i < fightervec.size(); i++)
            {
                if(name == fightervec[i]->getName())
                    {return false;}
            }
        }
        
        //Instantiate class based on fighter type.
        switch(type)
        {
            case 'A':
                fighterPtr = new Archer(name, type, maxhp, stren, spd, mgc);
                //cout<<"Creating archer type."<<endl;
                break;
            case 'C':
                fighterPtr = new Cleric(name, type, maxhp, stren, spd, mgc);
                //cout<<"Creating cleric type."<<endl;
                break;
            case 'R':
                fighterPtr = new Robot(name, type, maxhp, stren, spd, mgc);
                //cout<<"Creating robot type."<<endl;
                break;
            default:
                //This Fighter type is not a known type.
                return false;
        }
	
		fightervec.push_back(fighterPtr);
		
		return true;
	}

	/*
		removeFighter(string)

		Removes the fighter whose name is equal to the given name.  Does nothing if 
		no fighter is found with the given name.

		Return true if a fighter is removed; false otherwise.
	*/
	bool Arena::removeFighter(string name)
	{
		for(unsigned int i = 0; i < fightervec.size(); i++)
		{
			if(name == fightervec[i]->getName())
			{
				fightervec.erase(fightervec.begin() + i);
				return true;
			}
		}
		
		return false;
	}
	
	/*
		getFighter(string)

		Returns the memory address of a fighter whose name is equal to the given 
		name.  Returns NULL if no fighter is found with the given name.

		Return a memory address if a fighter is found; NULL otherwise.
	*/
	FighterInterface* Arena::getFighter(string name)
	{
		for	(unsigned int i = 0; i < fightervec.size(); i++)
		{
			if(name == fightervec[i]->getName())
			{
			    return fightervec[i];
			}
		}
		
		return NULL;
	}
	
	/*
		getSize()

		Returns the number of fighters in the arena.

		Return a non-negative integer.
	*/
	int Arena::getSize()
	{
		return fightervec.size();
	}

