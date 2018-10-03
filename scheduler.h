#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <fstream>
#include <sstream>
#include "randomNumberGenerator.h"
#include "process.h"
#include "scheduler.h"

#define FCFS 0
#define LCFS 1
#define SRTF 2
#define RR 3
#define PRIO 4
#define PREPRIO 5

class Scheduler {
	public:
		Scheduler(int algo, std::string fileName, std::string rFileName);
		Process* getProcess();

	private:
		int algorithm;
		std::ifstream file;
		RandomNumberGenerator rng;

};

#endif