#include "multi_threaded_application.h"
#include <iostream>

multi_threaded_application::multi_threaded_application() : m_waiting_to_write(false)
{
	pathfindingFrequency = 10;
	pathfindingTickCount = 0;
	m_render_thread = std::thread([&]
	{
		while (true)
		{
			if (!m_waiting_to_write)
			{
				m_render_data_mutex.lock();
				m_culling.execute();
				m_renderer.execute();
				m_render_data_mutex.unlock();
			}
		}
	});
}

void multi_threaded_application::tick()
{
	// Game mechanics
	m_input.execute();
	m_game_logic.execute();
	m_physics.execute();

	pathfindingTickCount++;
	if (pathfindingTickCount >= pathfindingFrequency)
	{
		//std::cout << "Ran " << pathfindingTickCount << ":" << pathfindingFrequency << std::endl;
		m_pathfinding.execute();
		pathfindingTickCount = 0;
	}
	

	//Must be called before rendering can occur!
	m_waiting_to_write = true;
	m_render_data_mutex.lock();

	m_waiting_to_write = false;
	m_update_render_data.execute();
	m_render_data_mutex.unlock();
	
}