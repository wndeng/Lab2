#ifndef LCFS_H
#define LCFS_H
#include <iostream>
#include <stack>
#include "scheduler.h"
#include "process.h"

class Lcfs: public Scheduler {
	public:
		Lcfs(int algo, std::string fileName, std::string rFileName);
		void schedule(Process *process, int time);
		Process* requestLoad(int time);
		std::stack <Process*> runStack;
		std::string name;
};

#endif