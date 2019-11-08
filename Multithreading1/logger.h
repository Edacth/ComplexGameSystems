#pragma once
#include <thread>
#include <string>
#include <fstream>
#include <vector>

class logger
{
	std::string filename;
	std::ofstream myfile;
	time_t myTime = time(NULL);

	
public:

	std::thread myThread;

	logger(std::string _filename);
	~logger();

	// Threaded
	void aWriteText(std::string text, int* runningThreads);

	void writeText(std::string text, int* runningThreads);

	void closeFile();
};