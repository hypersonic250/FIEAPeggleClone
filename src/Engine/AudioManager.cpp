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

Mix_Chunk* AudioManager::LoadSound(
    const std::string& path)
{
    return Mix_LoadWAV(
        path.c_str());
}

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