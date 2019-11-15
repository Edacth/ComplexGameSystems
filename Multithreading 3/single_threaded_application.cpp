/* @brief single_threaded_application.cpp
	Custome tick() implementation.
*/
#include "single_threaded_application.h"

/* @brief Ordered custome tick() implementation.
*/
void single_threaded_application::tick()
{

	// Game mechanics
    m_input.execute();
    m_game_logic.execute();
    m_physics.execute();
    m_pathfinding.execute();

    //Must be called before rendering can occur!
    m_update_render_data.execute();

	// Rendering
    m_culling.execute();
    m_renderer.execute();
}
