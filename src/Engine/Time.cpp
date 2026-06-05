#include "Time.h"

#include <SDL.h>

float Time::s_deltaTime = 0.0f;
unsigned int Time::s_lastTick = 0;

void Time::Initialize()
{
    s_lastTick = SDL_GetTicks();
}

void Time::Update()
{
    unsigned int currentTick = SDL_GetTicks();

    s_deltaTime = (currentTick - s_lastTick) / 1000.0f;

    s_lastTick = currentTick;
}

float Time::DeltaTime()
{
    return s_deltaTime;
}