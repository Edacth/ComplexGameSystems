/* @brief single_threaded_application.h
	Custome tick() implementation.
*/
#pragma once
#ifndef SINGLE_THREADED_APPLICATION_H
#define SINGLE_THREADED_APPLICATION_H

#include "base_application.h"

class single_threaded_application : public base_application
{
public:
	single_threaded_application() = default;
    void tick() override;
};
#endif // !SINGLE_THREADED_APPLICATION_H

