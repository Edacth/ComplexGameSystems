/* @brief base_application.h
	Abstract class containing a list of task, and a thread handle
	Simulates a single game, by executing imposter tasks.
   @note Child classes must implement tick()
*/
#pragma once
#ifndef BASE_APPLICATION_H
#define BASE_APPLICATION_H

#include <thread>
#include <vector>

#include "task.h"

class base_application
{
public:
	/* @brief Default constructor initialises tasks and starts single thread.
	*/
	base_application();

	/* @brief Derived applications implement their own tick, executing tasks
	*/
    virtual void tick() = 0;

protected:
	// kept separate rather than a container of task
	// as to allow distribution of tasks to multiple threads.

    task m_culling;
    task m_renderer;
    task m_input;
    task m_game_logic;
    task m_physics;
    task m_pathfinding;
    task m_update_render_data;

private:
	/* @brief Thread for querying task statistics
	*/
    std::thread m_display_time_thread;
};
#endif // !BASE_APPLICATION_H
