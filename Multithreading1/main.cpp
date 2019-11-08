#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "logger.h"

void print(int a)
{
	static std::mutex consoleLock;

	consoleLock.lock();

	std::cout << "Hello Thread, NO. " << a << std::endl;

	consoleLock.unlock();
}

int main()
{
	static int runningThreads = 0;
	// create a thread that will execute the print function
	std::vector<std::thread> threads;

	//for (int i = 0; i < 10; ++i)
	//{
	//	threads.emplace_back(print, i); // variadic function
	//}

	// blocks execution on the main thread until all threads exit
	//for (auto& t : threads)
	//{
	//	t.join();
	//}

	

	std::string filename = "test1.txt";
	logger myLogger1(filename);
	logger myLogger2("test2.txt");
	logger myLogger3("test3.txt");
	myLogger1.aWriteText("A", &runningThreads);
	myLogger2.aWriteText("B", &runningThreads);
	myLogger3.aWriteText("C", &runningThreads);

	std::cout << "End" << std::endl;

	myLogger1.myThread.join();
	myLogger2.myThread.join();
	myLogger3.myThread.join();

	

	return 0;
}