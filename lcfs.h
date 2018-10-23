#ifndef LCFS_H
#define LCFS_H
#include <iostream>
#include <stack>
#include "scheduler.h"
#include "process.h"

class Lcfs: public Scheduler {
	public:
		Lcfs(std::string fileName, std::string rFileName, int quantum);
		void schedule(Process *process, int time);
		Process* requestLoad(int time);
		std::stack <Process*> runStack; // Ready queue
		std::string name;
};

#endif