#include "preprio.h"

Preprio::~Preprio() {
	delete runQueue;
	delete expiredQueue;
}

Preprio::Preprio(int algo, std::string fileName, std::string rFileName, int quantum): Scheduler(algo, fileName, rFileName, quantum) {
	std::cout << "PREPRIO" << std::endl;
	this->runQueue = new SpecialQueue();
	this->expiredQueue = new SpecialQueue();
	this->currentProcess = NULL;
};

void Preprio::schedule(Process *process, int time) {
	process->changeState(READY, time);
	if(process->priority >= 0) {
		if(this->currentProcess != NULL && process->priority > this->currentProcess->priority) {
			if(this->debug) {std::cout << "Current process has lower priority than incoming process" << std::endl;}
			if(this->validateEventQueue(time)) {
				Event *event = new Event(this->currentProcess, TO_PREEMPT, time, time, this->eventOrder);
				this->eventOrder++;
				this->eventQueue.push(event);
			}
		}
		this->runQueue->push(process);
	}
	else {
		process->priority = process->static_priority - 1;
		this->expiredQueue->push(process);
	}
}

Process* Preprio::requestLoad(int time) {
	if(this->runQueue->empty()) {
		if(this->expiredQueue->empty()) {return NULL;}
		SpecialQueue *temp;
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

bool Preprio::validateEventQueue(int time) {
	std::queue<Event*> temp;
	Event *event;
	while((event = this->getNextEvent())) {
		if(event->timeStamp == time && event->process == this->currentProcess) {
			if(this->debug) {std::cout << "Current process will preempt at current time, no forced preemption necessary" << std::endl;}
			
			temp.push(event);

			while(!temp.empty()) {
				this->eventQueue.push(temp.front());
				temp.pop();
			}

			return false;
		}
		else if(event->process == this->currentProcess) {
			if(this->debug) {std::cout << "Current process will preempt, later event removed" << std::endl;}
			while(!temp.empty()) {
				this->eventQueue.push(temp.front());
				temp.pop();
			}
			return true;
		}
		temp.push(event);
	}
	if(this->debug) {std::cout << "No other events found for current process, proceed to preempt" << std::endl;}
	while(!temp.empty()) {
		this->eventQueue.push(temp.front());
		temp.pop();
	}
	return true;
}