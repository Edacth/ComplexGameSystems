/* @brief task.cpp
   Implementation of the task class 
   After initialisation, class will hold up a thread with a while loop that executes
   for a duration but only on at the frequency of the execution chance.
*/
#include "task.h"
#include <random>
#include <iostream>
#include <iterator>

/* @brief Our only constructor for task creation.
   @param Task/system name
   @param How long this task takes to execute in seconds
   @param The chance of this task executing on any given frame as a ratio
*/
task::task(const std::string& a_task_name, float a_execution_time, float a_execution_chance /* = 1.0f */)
    :   m_task_name(a_task_name)
    ,   m_execute_time(a_execution_time)
    ,   m_execute_chance(a_execution_chance)
    ,	m_cumulative_frame_time(0)
    ,	m_cumulative_frame_count(0)
    ,	m_average_frame_time(-1.0f)
    ,	m_frame_time(0)
{
	// Initialise everything and store the time at initialisation.
	m_last_executed = std::chrono::high_resolution_clock::now();
}

/* @brief Runs a loop blocking the thread for the task's duration.
	Updates internals.
*/
void task::execute()
{
	// Store the start time for this function's execution
    auto start_time_point = std::chrono::high_resolution_clock::now();
	// Precalculate and store the tasks finish time.
    auto end_time_point = start_time_point + std::chrono::duration<double>(m_execute_time);
    
	// Uniformly-distributed integer random number generator that produces non-deterministic random numbers.
	// https://en.cppreference.com/w/cpp/numeric/random/random_device
	// Used to initialise the random number engine mt19937
    static std::random_device random_device;

	// The random number generater itself
	// https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    static std::mt19937 generator(random_device());

	// The distribution for the normalised range to randomly determine
	// if this task executes on this call. Range [0,1] inclusive
	// https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

	// This is the time point at any instant during the delay loop... starting now.
    auto current_time_point = start_time_point;

	// If our generated random number is less than the chance... 
    if (distribution(generator) < m_execute_chance)
    {
		// Delay with the loop.
        for ( /* No initial conditions */;
			current_time_point < end_time_point; // While we have not reached duration...
			current_time_point = std::chrono::high_resolution_clock::now()) // Update current_time_point
			{ /* Do nothing */ }
    }

	// Time point count() is a measure of nanoseconds
	// a duration cast to float, then count, returns seconds.
    m_frame_time = std::chrono::duration<float>(current_time_point - m_last_executed).count();

	// Update the finish time point.
    m_last_executed = current_time_point;

	// accumulate frame time...
    m_cumulative_frame_time += m_frame_time;
	// and iterate frame count
    ++m_cumulative_frame_count;

	// This 1.0f represends a 1 second timer. Hard coded.
    if (m_cumulative_frame_time > 1.0f)
    {
		// Calculate average for the last second
        m_average_frame_time = m_cumulative_frame_time / (float)m_cumulative_frame_count;
		// Reset this second's frame count
        m_cumulative_frame_count = 0;
		// reset frame time but preserve any overtime.
		m_cumulative_frame_time -= 1.0f;
    }
}

/* @brief Outputs frame time to console
*/
void task::display_average_frame_time() const
{
	// Output task name
    std::cout << m_task_name << ":";
	// Fill the output stream, using spaces, to 15 characters, using cout
    std::fill_n(std::ostream_iterator<char>(std::cout), 15 - m_task_name.length(), ' ');
	// write the average frame time to stream
    std::cout << get_average_frame_time() << std::endl;
}

/* @brief Outputs frame rate to console
*/
void task::display_average_frame_rate() const
{
	// Output task name
    std::cout << m_task_name << ":";
	// Fill the output stream, using spaces, to 15 characters, using cout
    std::fill_n(std::ostream_iterator<char>(std::cout), 15 - m_task_name.length(), ' ');
	// write the average frame time to stream
    std::cout << get_average_frame_rate() << std::endl;
}

/* @brief Read access to frame time in seconds
   @return frame time in seconds
*/
float task::get_frame_time() const
{
    return m_frame_time;
}

/* @brief Read access to average frame time in seconds
   @return average frame time in seconds
*/
float task::get_average_frame_time() const
{
    return m_average_frame_time;
}

/* @brief Read access to current frames per second
   @return current frames per second
*/
float task::get_frame_rate() const
{
    return 1.0f / m_frame_time;
}

/* @brief Read access to average frames per second
   @return average frames per second
*/
float task::get_average_frame_rate() const
{
    return 1.0f / m_average_frame_time;
}
