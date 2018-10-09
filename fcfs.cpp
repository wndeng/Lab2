#include "fcfs.h"

Fcfs::Fcfs(int algo, std::string fileName, std::string rFileName): Scheduler(algo, fileName, rFileName) {};

Event* Fcfs::getNextEvent() {
	Event *event = new Event(this->processQueue.front(), READY_TO_RUNNING);
	return event;
}