#ifndef FCFS_H
#define FCFS_H
#include <iostream>
#include <queue>
#include "scheduler.h"
#include "process.h"

class Fcfs: public Scheduler {
	public:
		Fcfs(std::string fileName, std::string rFileName, int quantum);
		void schedule(Process *process, int time);
		Process* requestLoad(int time);
		std::queue <Process*> runQueue; // Ready queue
		std::string name;
};

#endif