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
	Event(Process *process_, Trans trans_): process(process_), trans(trans_) {};
	Process *process;
	Trans trans;
};

#endif