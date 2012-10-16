#ifndef __STATION_HPP__
#define __STATION_HPP__

#include <iostream>
#include <string>
#include "StationInterface.h"
#include "ede_stack.hpp"
#include "ede_queue.hpp"
#include "ede_deque.hpp"

using namespace std;

using ede::stack;
using ede::queue;
using ede::deque;

/*
	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/
class Station : public StationInterface
{
    private:
        stack<int> carStack;
        queue<int> carQueue;
        deque<int> carDeque;
        int current;

	public:
		Station(): current(-1) {};
		virtual ~Station(){};

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
		virtual bool addToStation(int car);

		/**
		 * Returns the ID of the current car.
		 * Return -1 if there is no current car.
		 *
		 * @return the ID of the current car; -1 if there is no current car
		 */
		virtual int showCurrentCar();

		/**
		 * Removes the current car from the station.
		 * Does nothing if there is no current car.
		 *
		 * @return true if the current car successfully left; false otherwise
		 */
		virtual bool removeFromStation();

		//Part 2--------------------------------------------------------------
		/**
		 * Adds the current car to the stack.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the stack is already full.
		 *
		 * @return true if the car is successfully added to the stack; false otherwise
		 */
		virtual bool addToStack();

		/**
		 * Removes the first car in the stack and makes it the current car.
		 * Does nothing if there is already a current car or if the stack already empty.
		 *
		 * @return true if the car is successfully removed from the stack; false otherwise
		 */
		virtual bool removeFromStack();

		/**
		 * Returns the ID of the first car in the stack.
		 *
		 * @return the ID of the first car in the stack; -1 if the stack is empty
		 */
		virtual int showTopOfStack();

		/**
		 * Returns the number of cars in the stack.
		 *
		 * @return the number of cars in the stack
		 */
		virtual int showSizeOfStack();

		//Part 3--------------------------------------------------------------
		/**
		 * Adds the current car to the queue.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the queue is already full.
		 *
		 * @return true if the car is successfully added to the queue; false otherwise
		 */
		virtual bool addToQueue();

		/**
		 * Removes the first car in the queue and makes it the current car.
		 * Does nothing if there is already a current car or if the queue already empty.
		 *
		 * @return true if the car is successfully removed from the queue; false otherwise
		 */
		virtual bool removeFromQueue();

		/**
		 * Returns the ID of the first car in the queue.
		 *
		 * @return the ID of the first car in the queue; -1 if the queue is empty
		 */
		virtual int showTopOfQueue();

		/**
		 * Returns the number of cars in the queue.
		 *
		 * @return the number of cars in the queue
		 */
		virtual int showSizeOfQueue();

		//Part 4--------------------------------------------------------------
		/**
		 * Adds the current car to the deque on the left side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the deque is already full.
		 *
		 * @return true if the car is successfully added to the deque; false otherwise
		 */
		virtual bool addToDequeLeft();

		/**
		 * Adds the current car to the deque on the right side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the deque is already full.
		 *
		 * @return true if the car is successfully added to the deque; false otherwise
		 */
		virtual bool addToDequeRight();

		/**
		 * Removes the leftmost car in the deque and makes it the current car.
		 * Does nothing if there is already a current car or if the deque already empty.
		 *
		 * @return true if the car is successfully removed from the deque; false otherwise
		 */
		virtual bool removeFromDequeLeft();

		/**
		 * Removes the rightmost car in the deque and makes it the current car.
		 * Does nothing if there is already a current car or if the deque already empty.
		 *
		 * @return true if the car is successfully removed from the deque; false otherwise
		 */
		virtual bool removeFromDequeRight();

		/**
		 * Returns the ID of the leftmost car in the deque.
		 *
		 * @return the ID of the leftmost car in the deque; -1 if the deque is empty
		 */
		virtual int showTopOfDequeLeft();

		/**
		 * Returns the ID of the rightmost car in the deque.
		 *
		 * @return the ID of the rightmost car in the deque; -1 if the deque is empty
		 */
		virtual int showTopOfDequeRight();

		/**
		 * Returns the number of cars in the deque.
		 *
		 * @return the number of cars in the deque
		 */
		virtual int showSizeOfDeque();
};

#endif //__STATION_HPP__
