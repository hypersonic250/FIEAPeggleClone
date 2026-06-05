#pragma once

#include <string>
#include <SDL_ttf.h>

class Renderer;

class HUD
{
public:

    HUD();

    ~HUD();

    bool Initialize();

    void Render(
        Renderer& renderer,
        int score,
        int turnScore,
        int ballsRemaining,
        int orangeRemaining
    );

    void RenderCenterMessage(
        Renderer& renderer,
        const std::string& message
    );

private:

    TTF_Font* m_font = nullptr;
};