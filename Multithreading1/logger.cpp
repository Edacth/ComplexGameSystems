#include <mutex>
#include <iostream>
#include <ctime>
#include <chrono>

#include "logger.h"

logger::logger(std::string _filename)
{
	filename = _filename;
	myfile.open(filename);
}

logger::~logger()
{
//	myfile.close();
}

void logger::aWriteText(std::string text, int* runningThreads)
{
	myThread = std::thread(&logger::writeText, this, text, runningThreads);
	
}

void logger::writeText(std::string text, int* runningThreads)
{
	static std::mutex consoleLock;

	consoleLock.lock();
	*runningThreads += 1;
	std::cout << "# of running threads:" << *runningThreads << std::endl;
	consoleLock.unlock();

	std::this_thread::sleep_for(std::chrono::seconds(5));
	
	myfile << "# of running threads:" << *runningThreads << " ";
	
	for (int i = 0; i < 100; i++)
	{
		myfile << text;
	}
	myfile << "\n";

	consoleLock.lock();
	*runningThreads -= 1;
	consoleLock.unlock();
	
}

void logger::closeFile()
{
	myfile.close();
}