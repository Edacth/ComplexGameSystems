/* @brief base_application.cpp
	Abstract class containing a list of task, and a thread handle
	Simulates a single game, by executing imposter tasks.
	@note Child classes must implement tick()
*/
#include "base_application.h"
#include <iostream>

base_application::base_application() :
	m_culling("Culling", 0.0025f),
	m_renderer("Renderer", 0.0042f),
	m_input("Input", 0.0005f),
	m_game_logic("Game Logic", 0.004f),
	m_physics("Physics", 0.006f),
	m_pathfinding("Pathfinder", 0.2f, 0.1f),
	m_update_render_data("Update Renderer", 0.001f)
{
	// Thread creation through a lambda that simply prints
	// the times per task per thread each second.
	m_display_time_thread = std::thread([&] 
	{
        while(true) 
        {
            system("cls");
            std::cout << "Frame times:" << std::endl;
            std::cout << "-----------" << std::endl;
			m_update_render_data.display_average_frame_time();
            m_culling.display_average_frame_time();
            m_renderer.display_average_frame_time();
            m_input.display_average_frame_time();
            m_game_logic.display_average_frame_time();
            m_physics.display_average_frame_time();
            m_pathfinding.display_average_frame_time();
            std::cout << "\n\n";

            std::cout << "Frame rates" << std::endl;
            std::cout << "-----------" << std::endl;
			m_update_render_data.display_average_frame_rate();
            m_culling.display_average_frame_rate();
            m_renderer.display_average_frame_rate();
            m_input.display_average_frame_rate();
			m_game_logic.display_average_frame_rate();
            m_physics.display_average_frame_rate();
            m_pathfinding.display_average_frame_rate();

			// Wait a second...
            std::this_thread::sleep_for(std::chrono::duration<float>(1.0f));
        }
    });
}
