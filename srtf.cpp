#include "srtf.h"

Srtf::Srtf(std::string fileName, std::string rFileName, int quantum): Scheduler(SRTF, fileName, rFileName, quantum) {
	std::cout << "SRTF" << std::endl;
};

void Srtf::schedule(Process *process, int time) {
	process->changeState(READY, time);
	this->runQueue.push(process);
}

Process* Srtf::requestLoad(int time) {
	if(runQueue.empty()) {
		return NULL;
	}
	Process *process = this->runQueue.top();
	this->runQueue.pop();
	int timeDiff = time - process->stateStartTime;
	Event *event = new Event(process, TO_RUNNING, time, timeDiff, this->eventOrder);
	this->eventQueue.push(event);
	this->eventOrder++;
	return process;
}