#include <iostream>
#include "Station.hpp"

using std::cout;
using std::cerr;
using std::endl;

//Part 1--------------------------------------------------------------
/**
 * Let another car arrive at the station and become the current car.
 * Do not allow a new car to arrive if any of the following conditions apply:
 * 1.	There is already a current car
 * 2.	The new car's ID already exists in any structure
 * 3.	The new car's ID is negative
 *
 * @param car the ID of the car arriving at the station
 * @return true if the car successfully arrived; false otherwise
 */
bool Station::addToStation(int car)
{
    bool retval = true;

    if(car < 0 || this->current >= 0)
        return false;

    int stackSize = carStack.size();
    int queueSize = carQueue.size();
    int dequeSize = carDeque.size();
    
    stack<int> tmpStack;

    /*********************************/
    /* Check for ID in stack.        */
    /*********************************/
    for(int i = 0; i < stackSize; ++i)
    {
        if(carStack.top() == car)
            retval = false;
        
        tmpStack.push(carStack.top());
        carStack.pop();
    }

    for(int i = 0; i < stackSize; ++i) // push values back onto stack.
    {
        carStack.push(tmpStack.top());
        tmpStack.pop();
    }

    /*********************************/
    /* Check for ID in queue.        */
    /*********************************/
    for(int i = 0; i < queueSize; ++i)
    {
        if(carQueue.front() == car)
            retval = false;

        carQueue.push(carQueue.front());
        carQueue.pop();
    }

    /*********************************/
    /* Check for ID in deque.        */
    /*********************************/
    for(int i = 0; i < dequeSize; ++i)
    {
        if(carDeque.front() == car)
            retval = false;
        
        carDeque.push_front(carDeque.back());
        carDeque.pop_back();
    }
    
    if(retval == true)
    {
        current = car;
    }

    return retval;

}

/**
 * Returns the ID of the current car.
 * Return -1 if there is no current car.
 *
 * @return the ID of the current car; -1 if there is no current car
 */
int Station::showCurrentCar()
{
    return current;
}

/**
 * Removes the current car from the station.
 * Does nothing if there is no current car.
 *
 * @return true if the current car successfully left; false otherwise
 */
bool Station::removeFromStation()
{
    if(current != -1)
    {
        current = -1;
        return true;
    }
    else
    {
        return false;
    }
}

//Part 2--------------------------------------------------------------
/**
 * Adds the current car to the stack.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the stack is already full.
 *
 * @return true if the car is successfully added to the stack; false otherwise
 */
bool Station::addToStack()
{
    if(current >= 0)
    {
        carStack.push(current);
        current = -1;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Removes the first car in the stack and makes it the current car.
 * Does nothing if there is already a current car or if the stack already empty.
 *
 * @return true if the car is successfully removed from the stack; false otherwise
 */
bool Station::removeFromStack()
{
    if(carStack.size() > 0 && current == -1)
    {
        current = carStack.top();
        carStack.pop();
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Returns the ID of the first car in the stack.
 *
 * @return the ID of the first car in the stack; -1 if the stack is empty
 */
int Station::showTopOfStack()
{
    if(carStack.empty())
        return -1;
    else
        return carStack.top();
}

/**
 * Returns the number of cars in the stack.
 *
 * @return the number of cars in the stack
 */
int Station::showSizeOfStack()
{
    return carStack.size();
}

//Part 3--------------------------------------------------------------
/**
 * Adds the current car to the queue.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the queue is already full.
 *
 * @return true if the car is successfully added to the queue; false otherwise
 */
bool Station::addToQueue()
{
    if(current == -1)
    {
        return false;
    }
    else
    {
        carQueue.push(current);
        current = -1;
        return true;       
    }
}

/**
 * Removes the first car in the queue and makes it the current car.
 * Does nothing if there is already a current car or if the queue already empty.
 *
 * @return true if the car is successfully removed from the queue; false otherwise
 */
bool Station::removeFromQueue()
{
    if(current == -1 || carQueue.empty())
    {
        return false;
    }
    else
    {
        current = carQueue.front();
        carQueue.pop();
        return true;
    }
}

/**
 * Returns the ID of the first car in the queue.
 *
 * @return the ID of the first car in the queue; -1 if the queue is empty
 */
int Station::showTopOfQueue()
{
    if(carQueue.empty())
    {
        return -1;
    }
    else
    {
        return carQueue.front();
    }
}

/**
 * Returns the number of cars in the queue.
 *
 * @return the number of cars in the queue
 */
int Station::showSizeOfQueue()
{
    return carQueue.size();
}

//Part 4--------------------------------------------------------------
/**
 * Adds the current car to the deque on the left side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the deque is already full.
 *
 * @return true if the car is successfully added to the deque; false otherwise
 */
bool Station::addToDequeLeft()
{
    if(current == -1)
    {
        return false;
    }
    else
    {
        carDeque.push_front(current);
        current = -1;
        return true;
    }
}

/**
 * Adds the current car to the deque on the right side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the deque is already full.
 *
 * @return true if the car is successfully added to the deque; false otherwise
 */
bool Station::addToDequeRight()
{
    if(current == -1)
    {
        return false;
    }
    else
    {
        carDeque.push_back(current);
        current = -1;
        return true;
    }
}

/**
 * Removes the leftmost car in the deque and makes it the current car.
 * Does nothing if there is already a current car or if the deque already empty.
 *
 * @return true if the car is successfully removed from the deque; false otherwise
 */
bool Station::removeFromDequeLeft()
{
    if(current != -1 || carDeque.empty())
    {
        return false;
    }
    else
    {
        current = carDeque.front();
        carDeque.pop_front();
        return true;
    }
}

/**
 * Removes the rightmost car in the deque and makes it the current car.
 * Does nothing if there is already a current car or if the deque already empty.
 *
 * @return true if the car is successfully removed from the deque; false otherwise
 */
bool Station::removeFromDequeRight()
{
    if(current != -1 || carDeque.empty())
    {
        return false;
    }
    else
    {
        current = carDeque.back();
        carDeque.pop_back();
        return true;
    }
}

/**
 * Returns the ID of the leftmost car in the deque.
 *
 * @return the ID of the leftmost car in the deque; -1 if the deque is empty
 */
int Station::showTopOfDequeLeft()
{
    if(carDeque.empty())
    {
        return -1;
    }
    else
    {
        return carDeque.front();
    }
}

/**
 * Returns the ID of the rightmost car in the deque.
 *
 * @return the ID of the rightmost car in the deque; -1 if the deque is empty
 */
int Station::showTopOfDequeRight()
{
    if(carDeque.empty())
    {
        return -1;
    }
    else
    {
        return carDeque.back();
    }
}

/**
 * Returns the number of cars in the deque.
 *
 * @return the number of cars in the deque
 */
int Station::showSizeOfDeque()
{
    return carDeque.size();
}

