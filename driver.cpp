#include "fcfs.h"

int main(int argc, char *argv[])
{
	Fcfs fcfs = Fcfs(0, argv[1], argv[2]);
	Process *process = fcfs.getProcess();
	while(process != NULL) {
		process->print();
		delete [] process;
		process = fcfs.getProcess();
	}

	return 0;
}