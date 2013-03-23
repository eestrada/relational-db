#if !defined(CIRCLE_H)
#define CIRCLE_H

#include <iostream>
#include <string>
#include <vector>
#include "JosephusInterface.h"

using namespace std;

class Circle : public JosephusInterface
{
private:
	vector<string> players, deados;
    vector<int> dindex;
    int safespot;

public:
	Circle(void)
	{
        players.reserve(20);
        deados.reserve(20);
		dindex.reserve(20);

        players.push_back("Abraham");       //0
        players.push_back("Belshazzar");    //1
        players.push_back("Cain");          //2
        players.push_back("Dan");           //3
        players.push_back("Ethan");         //4
        players.push_back("Frankincense");  //5
        players.push_back("Gideon");        //6
        players.push_back("Habakkuk");      //7
        players.push_back("Isaiah");        //8
        players.push_back("Josephus");      //9
        players.push_back("Kohath");        //10
        players.push_back("Lamech");        //11
        players.push_back("Malachi");       //12
        players.push_back("Nathanael");     //13
        players.push_back("Obadiah");       //14
        players.push_back("Paul");          //15
        players.push_back("Quaternion");    //16
        players.push_back("Rachel");        //17
        players.push_back("Samuel");        //18
        players.push_back("Tamar");         //19

        safespot = -1;
	}
	virtual ~Circle(void){}
	/*
		getNames

		Returns a list of names in the order in which the people will be standing for the "game".
		Although fewer people may be playing, you must return 20 names here. Do not provide
		duplicate names.

		For the sake of the test driver, this method must return the list of 20 names in the
		same order every time it is called, and this list of 20 names in this order must be used
		to play the "game".

		This method will be called repeatedly.
	*/
	virtual vector<string> getNames();
	/*
		playGame

		Plays a "game" with the first n people from the list (above) counting forward every m. An
		explanation for how the "game" works can be found in the exam specs.

		This method should return a list of names in the order in which the lot fell upon them (including
		the survivor, who should be last).  If n is not between 10 and 20 or if m is non-positive,
		return an empty vector.

		This method will be called repeatedly.
	*/
	virtual vector<string> playGame(int n, int m);
	/*
		reportSafeIndex

		Returns the "safe index", the last index/location in the circle that will be chosen when
		the "game" is played. The point of this method is to permit someone to cheat the system
		by finding the safe location ahead of time.

		If n is not between 10 and 20 or if m is non-positive, return -1.

		This method may be called repeatedly.
	*/
	virtual int reportSafeIndex(int n, int m);
    
};

#endif
