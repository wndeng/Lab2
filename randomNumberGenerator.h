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
        ~RandomNumberGenerator();
        int get(int burst);

    private:
        int fileNumCount;
        int *fileArray;
        int ofs;
};

#endif