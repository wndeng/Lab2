#ifndef PROCESS_H
#define PROCESS_H

#define CREATED 0
#define READY 1
#define BLOCKED 2
#define RUNNING 3

class Process {

    public:

        Process(int AT_, int TC_, int CB_, int IO_, int prio);
        void changeState(int newState);
        void print();

    private:
        int AT;
        int TC;
        int CB;
        int IO;
        int priority;
        int state;
};

#endif