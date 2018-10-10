#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <fstream>
#include <sstream>
#include "randomNumberGenerator.h"
#include "process.h"
#include "event.h"
#include <queue>

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
		return true;
	}

};

class Scheduler {
	public:
		Scheduler(int algo, std::string fileName, std::string rFileName);
		virtual Event* getNextEvent() = 0;
		void processEvent(Event* event);
		void simulate();
		int nextProcessTime();
		int algorithm;
		std::ifstream file;
		RandomNumberGenerator rng;
		int currentTime;
		std::priority_queue<Event*, std::vector<Event*>, EventCompare> eventQueue; 

};

#endif