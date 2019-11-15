/* @brief task.h
	Task simulates a single game engine sub-system.
    Holds and tracks imposter data for simulating processing time taken
	by a task on a thread.
   @note This will only work in debug mode as the optimise notices the delay loop does nothing
   computationally and removes it.
*/
#pragma once
#ifndef TASK_H
#define TASK_H

#include <chrono>	// To measure time
#include <string>	// For names

/* @brief Type alias for timestamp short hand
*/
using time_point = std::chrono::high_resolution_clock::time_point;

class task
{
public:
	/* @brief Default constructor explicityly unavailable.
	   @note what would be a default task?
	*/
	task() = delete;

	/* @brief Our only constructor for task creation
	   @param Task/system name
	   @param How long this task takes to execute in seconds
	   @param The chance of this task executing on any given frame as a ratio
	*/
	task(const std::string& a_task_name, float a_execution_time, float a_execution_chance = 1.0f);

	/* @brief Runs a loop blocking the thread for the task's duration.
	    Updates internals.
	*/
    void execute();

	/* @brief Outputs frame time to console
	*/
	void display_average_frame_time() const;
	/* @brief Outputs frame rate to console
	*/
    void display_average_frame_rate() const;

	/* @brief Read access to frame time in seconds
	   @return frame time in seconds
	*/
    float get_frame_time() const;
	/* @brief Read access to average frame time in seconds
	   @return average frame time in seconds
	*/
    float get_average_frame_time() const;
	/* @brief Read access to current frames per second
	   @return current frames per second
	*/
    float get_frame_rate() const;
	/* @brief Read access to average frames per second
	   @return average frames per second
	*/
    float get_average_frame_rate() const;

private:
	/* @brief The name of this system / task
	*/
    std::string m_task_name;
	/* @brief How long this task takes to execute in seconds
	*/
    float m_execute_time;
	/* @brief Frequency of this task's execution as a ratio
	*/
    float m_execute_chance;
	/* @brief Current measure of how long it takes to process a
	    frame on this task's thread
	*/
    float m_frame_time;
	/* @brief Current measure of this task's thread's average frame time
	*/
    float m_average_frame_time;
	/* @brief Measures to a second, acts as a marker to caluclate averages
	*/
    float m_cumulative_frame_time;
	/* @brief Accumulates frame count for the last second.
	*/
    int   m_cumulative_frame_count;
	/* @brief Time stamp for the last time this task started
	*/
	time_point m_last_executed;
};

#endif // !TASK_H