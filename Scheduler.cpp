#include "scheduler.h"

int main(int argc, char *argv[])
{
	Scheduler scheduler = Scheduler(0, argv[1], argv[2]);
	Process *process = scheduler.getProcess();
	while(process != NULL) {
		process->print();
		delete [] process;
		process = scheduler.getProcess();
	}

	return 0;
}

Scheduler::Scheduler(int algo, std::string fileName, std::string rFileName): algorithm(algo), file(fileName), rng(rFileName) {
	if(!this->file.is_open()) {
		std::cout << "file not found!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

Process* Scheduler::getProcess() {
	std::string line;
	if(std::getline(this->file, line)) {
		std::stringstream ss;
		ss << line;
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
		Process *process = new Process(AT, TC, CB, IO, priority);
		return process;
	}
	return NULL;
}

