#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "RandomNumberGenerator.h"

int main(int argc, char *argv[])
{
	std::string rFileName = argv[1];
	RandomNumberGenerator rng(rFileName);
	return 0;
}