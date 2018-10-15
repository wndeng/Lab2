#include "scheduler.h"

Scheduler::Scheduler(int algo, std::string fileName, std::string rFileName): algorithm(algo), file(fileName), rng(rFileName) {
	if(!this->file.is_open()) {
		std::cout << "file not found!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line, num;
	std::stringstream ss;
	int processCount = 0;

	this->eventOrder = 0;

	while(getline(this->file, line)) {
		ss << line;
		ss >> num;
		int AT = std::stoi(num);
		ss >> num;
		int TC = std::stoi(num);
		ss >> num;
		int CB = std::stoi(num);
		ss >> num;
		int IO = std::stoi(num);
		int priority = this->rng.get(4);
		Process *process = new Process(processCount, AT, TC, CB, IO, priority);
		processCount++;

		Event *event = new Event(process, TO_READY, process->AT, 0, this->eventOrder);
		this->eventQueue.push(event);
		this->eventOrder++;
	}
}

void Scheduler::printEvent(Event *event) {
	std::string action = "";

	switch (event->prevState) {
		case READY:
			action = "READY";
			break;
		case CREATED:
			action = "CREATED";
			break;
		case RUNNING:
			action = "RUNNING";
			break;
		case BLOCKED:
			action = "BLOCKED";
			break;
	}

	action += " -> ";

	switch (event->trans) {
		case TO_READY:
			action += "READY";
			break;
		case TO_RUNNING:
			action += "RUNNING";
			break;
		case TO_BLOCK:
			action += "BLOCK";
			break;
		case TO_PREEMPT:
			action += "PREEMPT";
			break;
	}
	std::cout << event->timeStamp << " " << event->process->PID << " " << event->timeDiff << " " << action;
	if(event->trans == TO_READY || event->trans == TO_PREEMPT) {std::cout << std::endl;}
}

Event* Scheduler::getNextEvent() {
	if(this->eventQueue.empty()) {
		return NULL;
	}
	Event *event = this->eventQueue.top();
	this->eventQueue.pop();
	return event;
}

void Scheduler::simulate() {

	Event *event = NULL;
	Process *currentProcess = NULL;
	Process *process = NULL;

	while((event = this->getNextEvent())) {
		int currentTime = event->timeStamp;
		process = event->process;
		this->printEvent(event);

		switch(event->trans) {
			case TO_READY:
				this->schedule(process, currentTime);
				break;
			case TO_BLOCK:
				process->changeState(BLOCKED, currentTime);
				if(process->rem == 0) {
					std::cout << " Done" << std::endl;
					currentProcess = NULL;
					break;
				}
				else {
					this->ready(process, currentTime);
					currentProcess = NULL;
					break;
				}
			case TO_PREEMPT:
				// this->schedule(currentProcess);
				// CALL_SCHEDULER = true;
				break;
			case TO_RUNNING:
				process->changeState(RUNNING, currentTime);
				this->block(process, currentTime);
				currentProcess = process;
				//this->stop(currentProcess, currentTime);
				break;
		}

		if(currentProcess == NULL) {
			this->requestLoad(currentTime);
		}

		delete [] event;
		event = NULL;
	}
}

void Scheduler::block(Process *process, int time) {
	int waitTime = std::min(this->rng.get(process->CB), process->rem);
	std::cout << " cb = " << waitTime << " rem = " << process->rem << " prio = " << process->priority << std::endl;
	Event *event = new Event(process, TO_BLOCK, time + waitTime, waitTime, this->eventOrder);
	this->eventQueue.push(event);
	this->eventOrder++;
}

void Scheduler::ready(Process *process, int time) {
	int waitTime = this->rng.get(process->IO);
	std::cout << " ib = " << waitTime << " rem = " << process->rem << " prio = " << process->priority << std::endl;
	Event *event = new Event(process, TO_READY, time + waitTime, waitTime, this->eventOrder);
	this->eventQueue.push(event);
	this->eventOrder++;
}