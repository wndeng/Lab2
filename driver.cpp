#include "fcfs.h"

int main(int argc, char *argv[])
{
	Fcfs fcfs = Fcfs(0, argv[1], argv[2]);
	Event *event;
	while(!fcfs.eventQueue.empty()) {
		event = fcfs.eventQueue.top();
		fcfs.printEvent(event);
		fcfs.eventQueue.pop();
		delete [] event;
	}
// 	fcfs.newProcess();
// 	fcfs.simulate();
// 	return 0;
}