#ifndef PREPRIO_H
#define PREPRIO_H
#include <iostream>
#include <queue>
#include "scheduler.h"
#include "process.h"
#include "prio.h"


class Preprio: public Scheduler {
	public:
		Preprio(int algo, std::string fileName, std::string rFileName, int quantum);
		~Preprio();
		void schedule(Process *process, int time);
		Process* requestLoad(int time);
		bool validateEventQueue(int time);
		SpecialQueue *runQueue;
		SpecialQueue *expiredQueue;
		std::string name;
};

#endif