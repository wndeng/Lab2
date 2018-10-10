#include "fcfs.h"

Fcfs::Fcfs(int algo, std::string fileName, std::string rFileName): Scheduler(algo, fileName, rFileName) {};

Event* Fcfs::getNextEvent() {
	return NULL;
}

void Fcfs::printEvent(Event *event) {
	std::cout << event->timeStamp << " " << event->process->PID << " " << event->timeDiff << " " << event->trans << " " << std::endl;
}