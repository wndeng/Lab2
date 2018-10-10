#include "scheduler.h"

Scheduler::Scheduler(int algo, std::string fileName, std::string rFileName): algorithm(algo), file(fileName), rng(rFileName), currentTime(0) {
	if(!this->file.is_open()) {
		std::cout << "file not found!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line, num;
	std::stringstream ss;
	int processCount = 1;

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

		Event *event = new Event(process, CREATED_TO_READY, process->AT, 0);
		this->eventQueue.push(event);
	}

}

void Scheduler::simulate() {
	// Event *event;
	// while((event = this->getNextEvent())) {
	// 	this->processEvent(event);
	// }
	// Event *event = this->getNextEvent();
	// this->processEvent(event);

}

void Scheduler::processEvent(Event *event) {
	std::cout << "Processing" << std::endl;
}