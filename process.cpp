#include <string>
#include <vector>
#include <iostream>
#include "process.h"

static const int debug = 0;

Process::Process(int AT_, int TC_, int CB_, int IO_, int prio): AT(AT_), TC(TC_),  CB(CB_), IO(IO_), priority(prio), state(CREATED) {};

void Process::changeState(int newState) {
	 if(debug == 1) {
	 	std::cout << "process state changed from " << this->state << " to " << newState << std::endl;
	 }
	 this->state = newState;
}

void Process::print() {
	std::cout <<"AT: " << this->AT << std::endl;
	std::cout <<"TC: " << this->TC << std::endl;
	std::cout <<"CB: " << this->CB << std::endl;
	std::cout <<"IO: " << this->IO << std::endl;
	std::cout <<"PRIO: " << this->priority << std::endl;
}