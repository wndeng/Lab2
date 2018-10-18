#include "lcfs.h"

Lcfs::Lcfs(int algo, std::string fileName, std::string rFileName, int quantum): Scheduler(algo, fileName, rFileName, quantum) {
	std::cout << "LCFS" << std::endl;
};

void Lcfs::schedule(Process *process, int time) {
	process->changeState(READY, time);
	this->runStack.push(process);
}

Process* Lcfs::requestLoad(int time) {
	if(runStack.empty()) {
		return NULL;
	}
	Process *process = this->runStack.top();
	this->runStack.pop();
	int timeDiff = time - process->stateStartTime;
	Event *event = new Event(process, TO_RUNNING, time, timeDiff, this->eventOrder);
	this->eventQueue.push(event);
	this->eventOrder++;
	return process;
}