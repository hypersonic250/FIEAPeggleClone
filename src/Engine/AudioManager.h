#pragma once

#include <SDL_mixer.h>
#include <string>

class AudioManager
{
public:

    // initializes the audio system; prepares SDL_mixer for playback
    bool Initialize();

	// loads a WAV sound file from disk
    Mix_Chunk* LoadSound(
        const std::string& path);

	// plays a sound effect on the first available audio channel
    void PlaySound(
        Mix_Chunk* sound);

    void Shutdown();
};