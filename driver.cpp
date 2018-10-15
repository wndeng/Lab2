#include "fcfs.h"

int main(int argc, char *argv[])
{
	Fcfs fcfs = Fcfs(0, argv[1], argv[2]);
	fcfs.simulate();
}