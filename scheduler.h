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

typedef enum {
	FCFS,
	LCFS,
	SRTF,
	RR,
	PRIO,
	PREPRIO,
} algo;

struct EventCompare {
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
		Scheduler(int algo, std::string fileName, std::string rFileName, int quantum);
		Event* getNextEvent();
		virtual void schedule(Process *process, int time) = 0;
		void printEvent(Event *event);
		void simulate();
		int nextProcessTime();
		void block(Process *process, int time);
		void ready(Process *process, int time);
		void setDebug();
		virtual Process* requestLoad(int time) = 0;
		void printSummary();
		int algorithm;
		std::ifstream file;
		RandomNumberGenerator rng;
		std::priority_queue<Event*, std::deque<Event*>, EventCompare> eventQueue;
		std::list<Process*> processList;
		int eventOrder;
		int ioTime;
		int ioStart;
		int ioEnd;
		int cpuTime;
		bool debug;
		int quantum;
		Process *currentProcess;
};

#endif