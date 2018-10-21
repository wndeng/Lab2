#include "fcfs.h"
#include "lcfs.h"
#include "srtf.h"
#include "rr.h"
#include "prio.h"
#include "preprio.h"

int main(int argc, char *argv[])
{
	// Fcfs fcfs(0, argv[1], argv[2], argv[3]);
	// fcfs.setDebug();
	// fcfs.simulate();

	// Lcfs lcfs(0, argv[1], argv[2], argv[3]);
	// lcfs.setDebug();
	// lcfs.simulate();

	// Srtf srtf(0, argv[1], argv[2], argv[3]);
    // srtf.setDebug();
	// srtf.simulate();

	// Rr rr(0, argv[1], argv[2], std::stoi(argv[3]));
    // rr.setDebug();
	// rr.simulate();

	// Prio prio(0, argv[1], argv[2], std::stoi(argv[3]));
	// prio.setDebug();
	// prio.simulate();

	Preprio preprio(0, argv[1], argv[2], std::stoi(argv[3]));
	preprio.setDebug();
	preprio.simulate();
}