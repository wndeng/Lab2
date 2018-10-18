#ifndef PRIO_H
#define PRIO_H
#include <iostream>
#include <queue>
#include "scheduler.h"
#include "process.h"

class SpecialQueue {
	public:

		void push(Process *process) {
			if(process->priority == 0) {
				this->prio0.push(process);
			}
			else if(process->priority == 1) {
				this->prio1.push(process);
			}
			else if(process->priority == 2) {
				this->prio2.push(process);
			}
			else if(process->priority == 3) {
				this->prio3.push(process);
			}
		}

		Process *front() {
			if(!this->prio3.empty()) {
				return this->prio3.front();
			}
			else if(!this->prio2.empty()) {
				return this->prio2.front();
			}
			else if(!this->prio1.empty()) {
				return this->prio1.front();
			}
			else if(!this->prio0.empty()) {
				return this->prio0.front();
			}
			else {
				return NULL;
			}
		}

		void pop() {
			if(!this->prio3.empty()) {
				this->prio3.pop();
			}
			else if(!this->prio2.empty()) {
				this->prio2.pop();
			}
			else if(!this->prio1.empty()) {
				this->prio1.pop();
			}
			else if(!this->prio0.empty()) {
				this->prio0.pop();
			}
			else {
				std::cout << "A-A-ron" << std::endl;
			}
			return;
		}

		bool empty() {
			if(this->prio3.empty() && this->prio2.empty() && this->prio1.empty() && this->prio0.empty()) {
				return true;
			}
			return false;
		}

	private:
		std::queue<Process*> prio0;
		std::queue<Process*> prio1;
		std::queue<Process*> prio2;
		std::queue<Process*> prio3;

};

class Prio: public Scheduler {
	public:
		Prio(int algo, std::string fileName, std::string rFileName, int quantum);
		~Prio();
		void schedule(Process *process, int time);
		Process* requestLoad(int time);
		SpecialQueue *runQueue;
		SpecialQueue *expiredQueue;
		std::string name;
};

#endif