#ifndef SRTF_H
#define SRTF_H
#include <iostream>
#include <queue>
#include "scheduler.h"
#include "process.h"

struct RemCompare { // Enforce sorting by shortest remaining time and insertion order
	bool operator()(Process*& lhs, Process*& rhs) {
		if(lhs->rem < rhs->rem) {
			return false;
		}
		if(lhs->rem == rhs->rem) {
			return lhs->PID > rhs->PID;
		}
		return true;
	}
};

class Srtf: public Scheduler {
	public:
		Srtf(std::string fileName, std::string rFileName, int quantum);
		void schedule(Process *process, int time);
		Process* requestLoad(int time);
		std::priority_queue <Process*, std::deque<Process*>, RemCompare> runQueue; // Ready queue
		std::string name;
};

#endif