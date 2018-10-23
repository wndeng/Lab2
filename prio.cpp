#include "prio.h"

Prio::~Prio() {
	delete runQueue;
	delete expiredQueue;
}

Prio::Prio(std::string fileName, std::string rFileName, int quantum): Scheduler(PRIO, fileName, rFileName, quantum) {
	std::cout << "PRIO" << " " << quantum << std::endl;
	this->runQueue = new SpecialQueue();
	this->expiredQueue = new SpecialQueue();
};

void Prio::schedule(Process *process, int time) {
	process->changeState(READY, time);
	if(process->priority >= 0) {
		this->runQueue->push(process);
	}
	else {
		process->priority = process->static_priority - 1;
		this->expiredQueue->push(process);
	}
}

Process* Prio::requestLoad(int time) {
	if(this->runQueue->empty()) {
		if(this->expiredQueue->empty()) {return NULL;}
		SpecialQueue *temp; // Swap ready/expired queue
		temp = this->runQueue;
		this->runQueue = this->expiredQueue;
		this->expiredQueue = temp;
	}
	Process *process = this->runQueue->front();
	this->runQueue->pop();
	int timeDiff = time - process->stateStartTime;
	Event *event = new Event(process, TO_RUNNING, time, timeDiff, this->eventOrder);
	this->eventQueue.push(event);
	this->eventOrder++;
	return process;
}