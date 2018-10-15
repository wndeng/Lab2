#ifndef PROCESS_H
#define PROCESS_H

typedef enum {
	CREATED,
	READY,
	BLOCKED,
	RUNNING,
} State;

class Process {

    public:

        Process(int PID_, int AT_, int TC_, int CB_, int IO_, int prio);
        void changeState(State newState, int newTime);
        void print();
    	int PID;
        int AT;
        int TC;
        int CB;
        int IO;
        int priority;
        State state;
        int FT;
        int IT;
        int CW;
        int static_priority;
        int stateStartTime;
        int rem;
};

#endif