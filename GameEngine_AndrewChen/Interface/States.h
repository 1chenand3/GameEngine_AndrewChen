#pragma once
static class States
{
public:
	static bool getPauseState();
	static void setPauseState(bool pause);
private:static bool paused;
};

