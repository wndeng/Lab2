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
	this->ioStart = 0;
	this->ioEnd = 0;
	this->ioTime = 0;
	this->cpuTime = 0;
	this->debug = false;
	int AT = 0,  TC = 0, CB = 0, IO = 0, priority = 0;

	while(getline(this->file, line)) {
		ss << line;
		ss >> num;
		AT = std::stoi(num);
		ss >> num;
		TC = std::stoi(num);
		ss >> num;
		CB = std::stoi(num);
		ss >> num;
		IO = std::stoi(num);
		priority = this->rng.get(4);
		ss.clear();

		Process *process = new Process(processCount, AT, TC, CB, IO, priority);
		processCount++;
		this->processList.push_back(process);
		Event *event = new Event(process, TO_READY, process->AT, 0, this->eventOrder);
		this->eventQueue.push(event);
		this->eventOrder++;
	}
}

void Scheduler::setDebug() {
	this->debug = true;
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
	int currentTime = 0;

	while((event = this->getNextEvent())) {
		currentTime = event->timeStamp;
		process = event->process;
		if(this->debug) {this->printEvent(event);}
		switch(event->trans) {
			case TO_READY:
				this->schedule(process, currentTime);
				break;
			case TO_BLOCK:
				process->changeState(BLOCKED, currentTime);
				if(process->rem == 0) {
					if(this->debug) {std::cout << " Done" << std::endl;}
					process->FT = currentTime;
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
		if(!this->eventQueue.empty() && this->eventQueue.top()->timeStamp == currentTime) {
			continue;
		}

		else if(currentProcess == NULL) {
			currentProcess = this->requestLoad(currentTime);
		}

		delete [] event;
		event = NULL;
	}

	this->ioTime += (this->ioEnd - this->ioStart);
	this->cpuTime = currentTime;

	this->printSummary();
}

void Scheduler::block(Process *process, int time) {
	int waitTime = std::min(this->rng.get(process->CB), process->rem);
	if(this->debug) {std::cout << " cb = " << waitTime << " rem = " << process->rem << " prio = " << process->priority << std::endl;}
	Event *event = new Event(process, TO_BLOCK, time + waitTime, waitTime, this->eventOrder);
	this->eventQueue.push(event);
	this->eventOrder++;
}

void Scheduler::ready(Process *process, int time) {
	int waitTime = this->rng.get(process->IO);
	if(this->debug) {std::cout << " ib = " << waitTime << " rem = " << process->rem << " prio = " << process->priority << std::endl;}
	if(this->ioEnd < time) {
		if(this->debug) {std::cout << std::endl << "ioTime +" << (this->ioEnd - this->ioStart) << "=";}
		this->ioTime += (this->ioEnd - this->ioStart);
		if(this->debug) {std::cout << ioTime << std::endl;}
		this->ioStart = time;
		this->ioEnd = waitTime + time;
	}
	else if(this->ioEnd < waitTime + time) {
		this->ioEnd = waitTime + time;
		if(this->debug) {std::cout << "iotime end extended to " << this->ioEnd << ", new range =(" << this->ioStart << ", " << this->ioEnd << ")" << std::endl;}

	}

	Event *event = new Event(process, TO_READY, time + waitTime, waitTime, this->eventOrder);
	this->eventQueue.push(event);
	this->eventOrder++;
}

void Scheduler::printSummary() {
	int totalTime = 0;
	int size = (int) processList.size();
	int totalTT = 0;
	int totalCW = 0;

	while(!this->processList.empty()) {
		std::string str = "";
		Process *process = this->processList.front();
		totalTime += process->TC;
		totalTT += (process->FT - process->AT);
		totalCW += process->CW;

		this->processList.pop_front();
		if(process->PID < 10) {
			str += "000";
		}
		else if(process->PID < 100) {
			str += "00";
		}
		else if(process->PID < 1000) {
			str += "0";
		}
		std::cout << str << process->PID << ": " << std::setw(4) << process->AT << " " << std::setw(4) << process->TC << " " << std::setw(4) << process->CB << " " << std::setw(4) << process->IO << " " << std::setw(1) << process->static_priority << " | ";
		std::cout << std::setw(5) << process->FT << " " << std::setw(5) << (process->FT - process->AT) << " " << std::setw(5) << process->IT << " " << std::setw(5) << process->CW << std::endl;
		delete [] process;
		process = NULL;
	}
	std::cout << "SUM: " << this->cpuTime  << " " << std::setprecision(2) << std::fixed << (double)totalTime/this->cpuTime*100 << " " << (double)this->ioTime/this->cpuTime*100 << " " << (double) totalTT/size << " " << (double) totalCW/size << " " << std::setprecision(3) << std::fixed << size/((double)this->cpuTime/100) << std::endl;

}