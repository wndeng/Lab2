#include "scheduler.h"

Scheduler::Scheduler(int algo, std::string fileName, std::string rFileName): algorithm(algo), file(fileName), rng(rFileName), processCount(1), currentTime(0), currentLine("") {
	if(!this->file.is_open()) {
		std::cout << "file not found!" << std::endl;
		exit(EXIT_FAILURE);
	}
	if(!std::getline(this->file, this->currentLine)) {
		std::cout << "file error!";
		exit(EXIT_FAILURE);
	}
}

Process* Scheduler::getProcess() {
	if(this->currentLine == "") {
		return NULL;
	}
	else {
		std::stringstream ss;
		ss << this->currentLine;
		std::string num;
		ss >> num;
		int AT = std::stoi(num);
		ss >> num;
		int TC = std::stoi(num);
		ss >> num;
		int CB = std::stoi(num);
		ss >> num;
		int IO = std::stoi(num);
		int priority = this->rng.get(4);
		Process *process = new Process(this->processCount, AT, TC, CB, IO, priority);
		this->processCount++;
		getline(this->file, this->currentLine);
		return process;
	}
}

int Scheduler::nextProcessTime() {
	std::stringstream ss;
	ss << this->currentLine;
	std::string num;
	ss >> num;
	return std::stoi(num);
}

void Scheduler::simulate() {
	Event *event;
	while((event = this->getNextEvent())) {
		this->processEvent(event);
	}
}

void Scheduler::processEvent(Event *event) {
	std::cout << "Processing" << std::endl;
}