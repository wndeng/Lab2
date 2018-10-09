#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <fstream>
#include <sstream>
#include "randomNumberGenerator.h"
#include "process.h"
#include "event.h"

typedef enum {
	FCFS,
	LCFS,
	SRTF,
	RR,
	PRIO,
	PREPRIO,
} schedulingALgorithm;

class Scheduler {
	public:
		Scheduler(int algo, std::string fileName, std::string rFileName);
		Process* getProcess();
		virtual Event* getNextEvent() = 0;
		void processEvent(Event* event);
		void simulate();
		int nextProcessTime();

	private:
		int algorithm;
		std::ifstream file;
		RandomNumberGenerator rng;
		int processCount;
		int currentTime;
		std::string currentLine;
};

#endif