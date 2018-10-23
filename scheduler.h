#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <list>
#include "randomNumberGenerator.h"
#include "process.h"
#include "event.h"

typedef enum { // Define types of schedulers
	FCFS,
	LCFS,
	SRTF,
	RR,
	PRIO,
	PREPRIO,
} Algo;

struct EventCompare { // Used to enforce order of events per prompt requirements
	bool operator()(Event*& lhs, Event*& rhs) {
		if(lhs->timeStamp < rhs->timeStamp) {
			return false;
		}
		if(lhs->timeStamp == rhs->timeStamp) {
			return lhs->order > rhs->order;
		}
		return true;
	}
};

class Scheduler {
	public:
		Scheduler(Algo algo, std::string fileName, std::string rFileName, int quantum);
		virtual ~Scheduler();  // used to call destructor of inherited class
		Event* getNextEvent(); // Get next event in event queue
		virtual void schedule(Process *process, int time) = 0; // Used to let scheduler know new process arrived, implemented for each scheduler
		void printEvent(Event *event); // Print an event, used for debug
		void simulate(); // Simulate scheduling process
		void block(Process *process, int time); // Handle future blocking when a process is ran
		void ready(Process *process, int time); // Handle future ready when a process finishes its IO
		void setDebug(); // Enable debug (verbose mode)
		virtual Process* requestLoad(int time) = 0; // Request next process from scheduler
		void printSummary(); // Print required output
		Algo algorithm;  // Used to identify scheduler
		std::ifstream file; // Used to read processes
		RandomNumberGenerator rng; // Provides the random numbers from rand file
		std::priority_queue<Event*, std::deque<Event*>, EventCompare> eventQueue; // Event queue
		std::list<Process*> processList; // List of processes to store them so that their data can be printed at the end before being deleted
		int eventOrder; // used to manage order of insertion into event queue
		int ioTime; // used to handle total IO time
		int ioStart; // Used to handle total IO time
		int ioEnd; // Used to handle total IO time
		int cpuTime; // Total CPU time
		bool debug; // Used for verbose mode
		int quantum; // Stores quantum value for selected schedulers.
		Process *currentProcess; // Pointer to current running process
};

#endif