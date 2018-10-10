#ifndef EVENT_H
#define EVENT_H

#include "process.h"

typedef enum {
	CREATED_TO_READY,
	READY_TO_BLOCKED,
	BLOCKED_TO_READY,
	READY_TO_RUNNING,
} Trans;

struct Event {
	Event(Process *process_, Trans trans_, int time, int timePrev): process(process_), trans(trans_), timeStamp(time), timeDiff(timePrev) {};
	Process *process;
	Trans trans;
	int timeStamp;
	int timeDiff;
};

#endif