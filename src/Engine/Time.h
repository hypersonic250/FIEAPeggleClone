#pragma once

class Time
{
public:
    static void Initialize();

    static void Update();

    static float DeltaTime();

private:
    static float s_deltaTime;
    static unsigned int s_lastTick;
};