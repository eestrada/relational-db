#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "Circle.h"

using namespace std;


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
vector<string> Circle::getNames()
{
	return players;
}
/*
	playGame

	Plays a "game" with the first n people from the list (above) counting forward every m. An
	explanation for how the "game" works can be found in the exam specs.

	This method should return a list of names in the order in which the lot fell upon them (including
	the survivor, who should be last).  If n is not between 10 and 20 or if m is non-positive,
	return an empty vector.

	This method will be called repeatedly.
*/


vector<string> Circle::playGame(int n, int m)
{
    deados.resize(0);
    dindex.resize(0);
    
    if(10 <= n && n <= 20 && m > 0)
    {
        // Use a deque so we can push and pop at both ends.
        deque<int> circledeq;
        
        // Fill the deque with the initial index of positions.
        for (int i = 0; i < n; i++)
        {
            circledeq.push_back(i);
        }

        //Keep removing  people from the deque until only one remains.
        while(circledeq.size() > 1)
        {
            // Move the front to the back the alloted number of steps.
            for(int i = 1; i < m; i++)
            {
                circledeq.push_back(circledeq.front());
                circledeq.pop_front();
            }
            
            // Now "kill" the person left in the front.
            dindex.push_back(circledeq.front());
            circledeq.pop_front();
        }

        // Use the computed index to push strings onto stack in correct order.
        for(int i = 0; i < dindex.size(); i++)
        {
            deados.push_back(players.at(dindex.at(i)));
        }
        
        // Lastly push the safe person onto the stack.
        deados.push_back(players.at(circledeq.front()));
        
        // The safe location should be the only one left in the queue.
        safespot = circledeq.front();
    }
	return deados;
}
/*
	reportSafeIndex

	Returns the "safe index", the last index/location in the circle that will be chosen when
	the "game" is played. The point of this method is to permit someone to cheat the system
	by finding the safe location ahead of time.

	If n is not between 10 and 20 or if m is non-positive, return -1.

	This method may be called repeatedly.
*/
int Circle::reportSafeIndex(int n, int m)
{
    if(10 <= n && n <= 20 && m > 0)
    {
        this->playGame(n, m);
        return safespot;
    }
    
    deados.resize(0);
    dindex.resize(0);
    
    return -1;
}

