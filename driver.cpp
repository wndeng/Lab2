#include "fcfs.h"
#include "lcfs.h"
#include "srtf.h"

int main(int argc, char *argv[])
{
	// Fcfs fcfs = Fcfs(0, argv[1], argv[2]);
	// fcfs.setDebug();
	// fcfs.simulate();

	// Lcfs lcfs = Lcfs(0, argv[1], argv[2]);
	// lcfs.setDebug();
	// lcfs.simulate();

	Srtf srtf = Srtf(0, argv[1], argv[2]);
    srtf.setDebug();
	srtf.simulate();
}