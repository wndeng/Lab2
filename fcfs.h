#ifndef FCFS_H
#define FCFS_H
#include <iostream>
#include <queue>
#include "scheduler.h"
#include "process.h"

class Fcfs: public Scheduler {
	public:
		Fcfs(int algo, std::string fileName, std::string rFileName);
		Event* getNextEvent();
		void printEvent(Event *event);
		std::priority_queue <Process*> processQueue;
};

#endif