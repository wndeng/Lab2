#include <string>
#include <vector>
#include <iostream>
#include "process.h"

Process::Process(int PID_, int AT_, int TC_, int CB_, int IO_, int prio): PID(PID_), AT(AT_), TC(TC_),  CB(CB_), IO(IO_), priority(prio-1), state(CREATED), FT(AT_), IT(0), CW(0), static_priority(prio), stateStartTime(AT), rem(TC_), currentCB(0) {};

void Process::changeState(State newState, int newTime) {

	if(newState == BLOCKED && this->state == RUNNING) { // Adjust remaining CPU time and current burst if process is being blocked
		this->rem -= (newTime - this->stateStartTime);
		this->currentCB -= (newTime - this->stateStartTime);
	}
	if(newState == READY && this->state == BLOCKED) { // Adjust IO time and reset dynamic priority when process exits IO
		IT += (newTime - this->stateStartTime);
		this->priority = this->static_priority - 1;
	}
	if(newState == RUNNING) { // Adjust CPU waiting time when going into running
		CW += (newTime - this->stateStartTime);
	}
	if(this->state == RUNNING && newState == READY) { // Preemption, adjust remaining time, current cpu burst, and downgrade priority
		this->rem -= (newTime - this->stateStartTime);
		this->currentCB -= (newTime - this->stateStartTime);
		this->priority -= 1;
	}
	this->state = newState;
	this->stateStartTime = newTime;
}

void Process::print() {
	std::cout <<"PID: "<< this->PID << std::endl;
	std::cout <<"AT: " << this->AT << std::endl;
	std::cout <<"TC: " << this->TC << std::endl;
	std::cout <<"CB: " << this->CB << std::endl;
	std::cout <<"IO: " << this->IO << std::endl;
	std::cout <<"PRIO: " << this->priority << std::endl;
}