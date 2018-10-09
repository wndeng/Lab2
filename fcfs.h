#ifndef FCFS_H
#define FCFS_H
#include <queue>
#include "scheduler.h"
#include "process.h"

class Fcfs: public Scheduler {
	public:
		Fcfs(int algo, std::string fileName, std::string rFileName);
		Event* getNextEvent();

	private:
		std::queue <Process*> processQueue;
};

#endif