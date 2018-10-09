#include <string>
#include <vector>
#include <iostream>
#include "process.h"

static const int debug = 0;

Process::Process(int PID_, int AT_, int TC_, int CB_, int IO_, int prio): PID(PID_), AT(AT_), TC(TC_),  CB(CB_), IO(IO_), priority(prio), state(CREATED), FT(AT_), IT(0), CW(0) {};

void Process::changeState(State newState) {
	 this->state = newState;
}

void Process::print() {
	std::cout <<"PID: "<< this->PID << std::endl;
	std::cout <<"AT: " << this->AT << std::endl;
	std::cout <<"TC: " << this->TC << std::endl;
	std::cout <<"CB: " << this->CB << std::endl;
	std::cout <<"IO: " << this->IO << std::endl;
	std::cout <<"PRIO: " << this->priority << std::endl;
}