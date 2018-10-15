#ifndef EVENT_H
#define EVENT_H

#include "process.h"

typedef enum {
	TO_READY,
	TO_PREEMPT,
	TO_RUNNING,
	TO_BLOCK,
} Trans;

struct Event {
	Event(Process *process_, Trans trans_, int time, int timePrev, int order_): process(process_), trans(trans_), timeStamp(time), timeDiff(timePrev), prevState(process_->state), order(order_) {};
	Process *process;
	Trans trans;
	int timeStamp;
	int timeDiff;
	State prevState;
	int order;
};

#endif