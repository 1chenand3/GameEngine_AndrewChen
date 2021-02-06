#include "States.h"

bool States::getPauseState()
{
	return paused;
}

void States::setPauseState(bool pause)
{
	paused = pause;
}