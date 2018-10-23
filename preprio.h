#ifndef PREPRIO_H
#define PREPRIO_H
#include <iostream>
#include <queue>
#include "scheduler.h"
#include "process.h"
#include "prio.h"


class Preprio: public Scheduler {
	public:
		Preprio(std::string fileName, std::string rFileName, int quantum);
		~Preprio(); // Deallocate memory for run/expired queue
		void schedule(Process *process, int time);
		Process* requestLoad(int time);
		bool validateEventQueue(int time); // Check and potentially remove future event of current process should it be preempted
		SpecialQueue *runQueue; // Run queue
		SpecialQueue *expiredQueue; // Expired queue
		std::string name;
};

#endif