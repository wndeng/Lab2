#include <string>
#include <vector>
#include <iostream>
#include "process.h"

static const int debug = 0;

Process::Process(int PID_, int AT_, int TC_, int CB_, int IO_, int prio): PID(PID_), AT(AT_), TC(TC_),  CB(CB_), IO(IO_), priority(prio-1), state(CREATED), FT(AT_), IT(0), CW(0), static_priority(prio), stateStartTime(AT), rem(TC_), ioFlag(false) {};

void Process::changeState(State newState, int newTime) {
	if(newState == BLOCKED && this->state == RUNNING) {
		this->ioFlag = true;
		this->rem -= (newTime - this->stateStartTime);
	}
	if(newState == READY && this->ioFlag) {
		IT += (newTime - this->stateStartTime);
	}
	if(newState == RUNNING) {
		CW += (newTime - this->stateStartTime);
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