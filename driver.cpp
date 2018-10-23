#include "scheduler.h"
#include "fcfs.h"
#include "lcfs.h"
#include "srtf.h"
#include "rr.h"
#include "prio.h"
#include "preprio.h"
#include <iostream>
#include <getopt.h>

int main(int argc, char *argv[]) // Driver function for scheduler simulation
{
	char c;
	bool debug = false;
	bool pass = false;
	Scheduler *scheduler = NULL;
	while ((c = getopt (argc, argv, "svFLSR:P:E:")) != -1) { //Parse input
	    switch (c) {
	      	case 's':
	        	pass = true;
	        	break;
	      	case 'v':
	      		debug = true;
	      		break;
	      	case 'F':
	      		scheduler = new Fcfs(argv[argc-2], argv[argc-1], 10000);
	        	break;
	      	case 'L':
	      		scheduler = new Lcfs(argv[argc-2], argv[argc-1], 10000);
	      		break;
	      	case 'S':
	      		scheduler = new Srtf(argv[argc-2], argv[argc-1], 10000);
	      		break;
	      	case 'R':
	      		scheduler = new Rr(argv[argc-2], argv[argc-1], std::stoi(optarg));
	      		break;
	      	case 'P':
	      		scheduler = new Prio(argv[argc-2], argv[argc-1], std::stoi(optarg));
	      		break;
	      	case 'E':
	      		scheduler = new Preprio(argv[argc-2], argv[argc-1], std::stoi(optarg));
	      		break;
	      	default:
	   			return 0;
	    }
	}
    if(pass) {
    	if(debug) { // Enable verbose mode
    		scheduler->setDebug();
    	} // Run simulation
    	scheduler->simulate();
    }

    delete scheduler; // Free memory for scheduler
    scheduler = NULL;
}