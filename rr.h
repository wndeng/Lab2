#ifndef RR_H
#define RR_H
#include <iostream>
#include <queue>
#include "scheduler.h"
#include "process.h"

class Rr: public Scheduler {
	public:
		Rr(int algo, std::string fileName, std::string rFileName, int quantum);
		void schedule(Process *process, int time);
		Process* requestLoad(int time);
		std::queue <Process*> runQueue;
		std::string name;
};

#endif