#ifndef FCFS_H
#define FCFS_H
#include <iostream>
#include <queue>
#include "scheduler.h"
#include "process.h"

class Fcfs: public Scheduler {
	public:
		Fcfs(int algo, std::string fileName, std::string rFileName);
		void schedule(Process *process, int time);
		void requestLoad(int time);
		std::queue <Process*> runQueue;
};

#endif