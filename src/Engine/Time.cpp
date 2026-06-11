#include "Time.h"

#include <SDL.h>

float Time::s_deltaTime = 0.0f;
unsigned int Time::s_lastTick = 0;

// initializes the audio system; prepares SDL_mixer for playback
void Time::Initialize()
{
    s_lastTick = SDL_GetTicks();
}

// updates the delta time value; should be called once per frame
void Time::Update()
{
    unsigned int currentTick = SDL_GetTicks();

    s_deltaTime = (currentTick - s_lastTick) / 1000.0f;

    s_lastTick = currentTick;
}

// plays a sound effect on the first available audio channel; used for gameplay feedback such as peg hits, launcher shots, and free balls
float Time::DeltaTime()
{
    return s_deltaTime;
}