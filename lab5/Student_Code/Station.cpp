#include <iostream>
#include "Station.hpp"

using std::cout;
using std::cerr;
using std::endl;


template <typename T>
inline bool idInStack(stack<T> & carStack, const T & car)
{
    bool instack = false; 
    // Temp stack to push cars onto.
    stack<T> tmpStack;
    
    // Size variable to use in for loop
    int stackSize = carStack.size();
    
    for(int i = 0; i < stackSize; ++i)
    {
        if(carStack.top() == car)
        {
            // This car id already exists in the stack and thus is invalid.
            // Do not add to station and return false.
            instack = true;
        }

        tmpStack.push(carStack.top());
        carStack.pop();
    }
    
    // push values back onto stack from temp stack.
    for(int i = 0; i < stackSize; ++i) 
    {
        carStack.push(tmpStack.top());
        tmpStack.pop();
    }

    return instack;
}

template <typename T>
inline bool idInQueue(queue<T> & carQueue, const T & car)
{
    bool inqueue = false;

    // Size variable to use in for loop
    int queueSize = carQueue.size();
    
    for(int i = 0; i < queueSize; ++i)
    {
        if(carQueue.front() == car)
        {   
            // This car id already exists in the queue and thus is invalid.
            // Do not add to station and return false.
            inqueue = true;
        }

        carQueue.push(carQueue.front());
        carQueue.pop();
    }

    return inqueue;
}

template <typename T>
inline bool idInDeque(deque<T> & carDeque, const T & car)
{
    bool indeque = false;
    
    // Size variable to use in for loop
    int dequeSize = carDeque.size();
    
    for(int i = 0; i < dequeSize; ++i)
    {
        if(carDeque.front() == car)
        {   
            // This car id already exists in the deque and thus is invalid.
            // Do not add to station and return false.
            indeque = true;
        }
       
        carDeque.push_front(carDeque.back());
        carDeque.pop_back();
    }

    return indeque;
}
    
template <typename T>
inline bool idInIrdeque(irdeque<T> & carDeque, const T & car)
{
    bool indeque = false;
    
    // Size variable to use in for loop
    int dequeSize = carDeque.size();
    
    for(int i = 0; i < dequeSize; ++i)
    {
        if(carDeque.left() == car)
        {   
            // This car id already exists in the deque and thus is invalid.
            // Do not add to station and return false.
            indeque = true;
        }
       
        carDeque.push_left(carDeque.right());
        carDeque.pop_right();
    }

    return indeque;
}

template <typename T>
inline bool idInOrdeque(ordeque<T> & carDeque, const T & car)
{
    bool indeque = false;
    
    // Size variable to use in for loop
    int dequeSize = carDeque.size();
    
    for(int i = 0; i < dequeSize; ++i)
    {
        if(carDeque.left() == car)
        {   
            // This car id already exists in the deque and thus is invalid.
            // Do not add to station and return false.
            indeque = true;
        }
       
        carDeque.push_right(carDeque.left());
        carDeque.pop_left();
    }

    return indeque;
}


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
    // If the new car id is less than zero or there is already a current
    // car then we already know that we can't proceed. Don't waste time
    // looking in the structures to see if the car id exists already.
    if(car < 0 || this->current >= 0)
        return false;

    // If we have gotten this far, then we need to check the structures to 
    // see if the new car id exists in any of them.
    if( idInStack(carStack, car) || idInQueue(carQueue, car) ||
        idInDeque(carDeque, car) || idInIrdeque(carIrdeque, car)||
        idInOrdeque(carOrdeque, car))
    {
        return false;
    }

    // If we got through all the structures without finding the car id
    // then it is now safe to make the new car into the current car.
    current = car;

    return true;
}

/**
 * Returns the ID of the current car.
 * Return -1 if there is no current car.
 *
 * @return the ID of the current car; -1 if there is no current car
 */
int Station::showCurrentCar()
{
    // The current value is always set to -1 if there is no current car,
    // so simply returning current will always give the correct value.
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
 * Does nothing if there is already a current car or if the stack is empty.
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
    if(carQueue.size() > 0 && current == -1)
    {
        current = carQueue.front();
        carQueue.pop();
        return true;
    }
    else
    {
        return false;
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
        carDeque.push_left(current);
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
        carDeque.push_right(current);
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
        current = carDeque.left();
        carDeque.pop_left();
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
        current = carDeque.right();
        carDeque.pop_right();
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
        return carDeque.left();
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
        return carDeque.right();
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



//Input-Restricted Deque----------------------------------------------
/**
 * Adds the current car to the IRDeque on the left side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the IRDeque is already full.
 *
 * @return true if the car is successfully added to the IRDeque; false otherwise
 */
bool Station::addToIRDequeLeft()
{
    if(current == -1)
    {
        return false;
    }
    else
    {
        carIrdeque.push_left(current);
        current = -1;
        return true;
    }
}

/**
 * Removes the leftmost car in the IRDeque and makes it the current car.
 * Does nothing if there is already a current car or if the IRDeque already empty.
 *
 * @return true if the car is successfully removed from the IRDeque; false otherwise
 */
bool Station::removeFromIRDequeLeft()
{
    if(current != -1 || carIrdeque.empty())
    {
        return false;
    }
    else
    {
        current = carIrdeque.left();
        carIrdeque.pop_left();
        return true;
    }
}

/**
 * Removes the rightmost car in the IRDeque and makes it the current car.
 * Does nothing if there is already a current car or if the IRDeque already empty.
 *
 * @return true if the car is successfully removed from the IRDeque; false otherwise
 */
bool Station::removeFromIRDequeRight()
{
     if(current != -1 || carIrdeque.empty())
    {
        return false;
    }
    else
    {
        current = carIrdeque.right();
        carIrdeque.pop_right();
        return true;
    }
}

/**
 * Returns the ID of the leftmost car in the IRDeque.
 *
 * @return the ID of the leftmost car in the IRDeque; -1 if the IRDeque is empty
 */
int Station::showTopOfIRDequeLeft()
{
    if(carIrdeque.empty())
    {
        return -1;
    }
    else
    {
        return carIrdeque.left();
    }
}

/**
 * Returns the ID of the rightmost car in the IRDeque.
 *
 * @return the ID of the rightmost car in the IRDeque; -1 if the IRDeque is empty
 */
int Station::showTopOfIRDequeRight()
{
    if(carIrdeque.empty())
    {
        return -1;
    }
    else
    {
        return carIrdeque.right();
    }
}

/**
 * Returns the number of cars in the IRDeque.
 *
 * @return the number of cars in the IRDeque
 */
int Station::showSizeOfIRDeque()
{
    return carIrdeque.size();
}

//Output-Restricted Deque---------------------------------------------
/**
 * Adds the current car to the ORDeque on the left side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the ORDeque is already full.
 *
 * @return true if the car is successfully added to the ORDeque; false otherwise
 */
bool Station::addToORDequeLeft()
{
    if(current == -1)
    {
        return false;
    }
    else
    {
        carOrdeque.push_left(current);
        current = -1;
        return true;
    }
}

/**
 * Adds the current car to the ORDeque on the right side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the ORDeque is already full.
 *
 * @return true if the car is successfully added to the ORDeque; false otherwise
 */
bool Station::addToORDequeRight()
{
    if(current == -1)
    {
        return false;
    }
    else
    {
        carOrdeque.push_right(current);
        current = -1;
        return true;
    }
}

/**
 * Removes the leftmost car in the ORDeque and makes it the current car.
 * Does nothing if there is already a current car or if the ORDeque already empty.
 *
 * @return true if the car is successfully removed from the ORDeque; false otherwise
 */
bool Station::removeFromORDequeLeft()
{
    if(current != -1 || carOrdeque.empty())
    {
        return false;
    }
    else
    {
        current = carOrdeque.left();
        carOrdeque.pop_left();
        return true;
    }
}

/**
 * Returns the ID of the leftmost car in the ORDeque.
 *
 * @return the ID of the leftmost car in the ORDeque; -1 if the ORDeque is empty
 */
int Station::showTopOfORDequeLeft()
{
    if(carOrdeque.empty())
    {
        return -1;
    }
    else
    {
        return carOrdeque.left();
    }
}

/**
 * Returns the number of cars in the ORDeque.
 *
 * @return the number of cars in the ORDeque
 */
int Station::showSizeOfORDeque()
{
    return carOrdeque.size();
}

