#pragma once
#ifndef MULTI_THREADED_APPLICATION_H
#define MULTI_THREADED_APPLICATION_H
#include <mutex>
#include <atomic>

#include "base_application.h"

class multi_threaded_application : public base_application
{
public:
	multi_threaded_application();
	void tick() override;

private:
	std::thread m_render_thread;
	std::mutex m_render_data_mutex;
	std::atomic<bool> m_waiting_to_write;
	int pathfindingFrequency;
	int pathfindingTickCount;
};
#endif // !MULTI_THREADED_APPLICATION_H