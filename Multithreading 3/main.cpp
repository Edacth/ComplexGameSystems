
/* @brief Application launch point for single threaded game loop
    with imposter tasks.
*/
#include "single_threaded_application.h"
#include "multi_threaded_application.h"

int main()
{
	//single_threaded_application s_application;
	multi_threaded_application m_application;
    while (true)
    {
		m_application.tick();
    }
    return 0;
}


