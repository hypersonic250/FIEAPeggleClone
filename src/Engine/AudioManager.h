#pragma once

#include <SDL_mixer.h>
#include <string>

class AudioManager
{
public:

    bool Initialize();

    Mix_Chunk* LoadSound(
        const std::string& path);

    void PlaySound(
        Mix_Chunk* sound);

    void Shutdown();
};