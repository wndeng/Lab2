#include "rr.h"

Rr::Rr(std::string fileName, std::string rFileName, int quantum): Scheduler(RR, fileName, rFileName, quantum) {
	std::cout << "RR" << " " << quantum << std::endl;
};

void Rr::schedule(Process *process, int time) {
	process->changeState(READY, time);
	this->runQueue.push(process);
}

Process* Rr::requestLoad(int time) {
	if(runQueue.empty()) {
		return NULL;
	}
	Process *process = this->runQueue.front();
	this->runQueue.pop();
	int timeDiff = time - process->stateStartTime;
	Event *event = new Event(process, TO_RUNNING, time, timeDiff, this->eventOrder);
	this->eventQueue.push(event);
	this->eventOrder++;
	return process;
}