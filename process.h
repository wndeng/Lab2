#ifndef PROCESS_H
#define PROCESS_H

typedef enum { // States of a process
	CREATED,
	READY,
	BLOCKED,
	RUNNING,
} State;

class Process {

    public:

        Process(int PID_, int AT_, int TC_, int CB_, int IO_, int prio);
        void changeState(State newState, int newTime); // Change state
        void print(); // Print process information
    	int PID; // Below are all required as stats or for getting stats of a process per prompt requirement
        int AT;
        int TC;
        int CB;
        int IO;
        int priority; // Dynamic priority
        State state; // Current state
        int FT;
        int IT;
        int CW;
        int static_priority;
        int stateStartTime; // Start time of current state
        int rem; // Remaining CPU time
        int currentCB; // Dynamic CPU burst
};

#endif