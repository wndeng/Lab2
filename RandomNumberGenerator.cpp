#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator(std::string rFileName) {
    std::ifstream file(rFileName);

    if(!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    std::stringstream ss;
    while(std::getline(file, line)) {
        ss << (" " + line);
    }
    file.close();
    std::string count;
    ss >> count;
    this->fileNumCount = std::stoi(count);
    this->fileArray = new int[this->fileNumCount];
    int i = 0;
    while(ss >> count) {
        this->fileArray[i] = std::stoi(count);
        i++;
    }
    this->ofs = 0;
}

RandomNumberGenerator::~RandomNumberGenerator() {
    delete [] this->fileArray;
}

int RandomNumberGenerator::get(int burst) {
    this->ofs++;
    if(this->ofs == this->fileNumCount - 1) {
        this->ofs = 1;
    }
    return 1 + (this->fileArray[this->ofs - 1] % burst);
}