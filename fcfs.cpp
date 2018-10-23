#include "fcfs.h"

Fcfs::Fcfs(std::string fileName, std::string rFileName, int quantum): Scheduler(FCFS, fileName, rFileName, quantum) {
	std::cout << "FCFS" << std::endl;
};

void Fcfs::schedule(Process *process, int time) {
	process->changeState(READY, time);
	this->runQueue.push(process);
}

Process* Fcfs::requestLoad(int time) {
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