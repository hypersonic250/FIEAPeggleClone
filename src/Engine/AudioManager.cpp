#include "AudioManager.h"

bool AudioManager::Initialize()
{
    if (Mix_OpenAudio(
        44100,
        MIX_DEFAULT_FORMAT,
        2,
        2048) < 0)
    {
        return false;
    }

    return true;
}

// loads a WAV sound file from disk 
// returns a pointer that can be played later
Mix_Chunk* AudioManager::LoadSound(
    const std::string& path)
{
    return Mix_LoadWAV(
        path.c_str());
}

// plays a sound effect on the first available audio channel 
// used for gameplay feedbacksuch as peg hits, launcher shots, and free balls
void AudioManager::PlaySound(
    Mix_Chunk* sound)
{
    Mix_PlayChannel(
        -1,
        sound,
        0);
}

void AudioManager::Shutdown()
{
    Mix_CloseAudio();
}