#include "States.h"

bool States::paused = false;

bool States::getPauseState()
{
	return States::paused;
}

void States::setPauseState(bool pause)
{
	paused = pause;
}