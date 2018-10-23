#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#define FALSE 0
#define TRUE 1

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

class RandomNumberGenerator {

    public:

        RandomNumberGenerator(std::string fileName_);
        ~RandomNumberGenerator(); // Deallocate seed storage
        int get(int burst); // Get a random number based on prompt

    private:
        int fileNumCount; // Stores number of seeds
        int *fileArray; // Stores the random seeds
        int ofs; // Current index
};

#endif