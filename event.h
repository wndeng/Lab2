#ifndef EVENT_H
#define EVENT_H

#include "process.h"

typedef enum { // Transition types
	TO_READY,
	TO_PREEMPT,
	TO_RUNNING,
	TO_BLOCK,
} Trans;

struct Event {
	Event(Process *process_, Trans trans_, int time, int timePrev, int order_): process(process_), trans(trans_), timeStamp(time), timeDiff(timePrev), prevState(process_->state), order(order_) {};
	Process *process; // Process related to event
	Trans trans; // Transition
	int timeStamp; // Event time
	int timeDiff; // Time since last event of this process
	State prevState; // Previous state of process
	int order; // Order of this event's insertion into event queue
};

#endif