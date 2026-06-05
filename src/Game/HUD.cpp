#include "HUD.h"

#include <iostream>
#include <filesystem>

#include "Engine/Renderer.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

HUD::HUD()
{
}

HUD::~HUD()
{
    if (m_font)
    {
        TTF_CloseFont(m_font);
    }
}

bool HUD::Initialize()
{
    std::cout << "Current path: "
        << std::filesystem::current_path()
        << std::endl;

    if (TTF_Init() != 0)
    {
        return false;
    }

    std::cout
        << std::filesystem::exists(
            "../../../assets/Fonts/UbuntuSans-VariableFont_wdth,wght.ttf")
        << std::endl;

    m_font = TTF_OpenFont(
        "../../../Assets/Fonts/UbuntuSans-VariableFont_wdth,wght.ttf",
        24
    );

    if (m_font == nullptr)
    {
        std::cout
            << "Font failed: "
            << TTF_GetError()
            << std::endl;

        return false;
    }

    std::cout
        << "Font loaded successfully!"
        << std::endl;


    return true;
}

void HUD::RenderCenterMessage(
    Renderer& renderer,
    const std::string& message)
{
    SDL_Color white =
    {
        255,
        255,
        255,
        255
    };

    SDL_Surface* surface =
        TTF_RenderText_Blended_Wrapped(
            m_font,
            message.c_str(),
            white,
            600
        );

    if (surface == nullptr)
    {
        return;
    }

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(
            renderer.GetNativeRenderer(),
            surface);

    SDL_Rect destination;

    destination.w = surface->w;
    destination.h = surface->h;
    destination.x = 640 - destination.w / 2;
    destination.y = 360 - destination.h / 2;

    SDL_RenderCopy(
        renderer.GetNativeRenderer(),
        texture,
        nullptr,
        &destination);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void HUD::Render(
    Renderer& renderer,
    int score,
    int turnScore,
    int ballsRemaining,
    int orangeRemaining)

{
    SDL_Color white =
    {
        255,
        255,
        255,
        255
    };

std::string text =
"SCORE: " +
std::to_string(score) +
"\nTURN: " +
std::to_string(turnScore) +
"\nBALLS: " +
std::to_string(ballsRemaining) +
"\nORANGE PEGS: " +
std::to_string(orangeRemaining) +
"\n(PRESS R TO RESET)";

    SDL_Surface* surface =
        TTF_RenderText_Blended_Wrapped(
            m_font,
            text.c_str(),
            white,
            300
        );

  
    if (surface == nullptr)
    {
        std::cout
            << "TTF Error: "
            << TTF_GetError()
            << std::endl;

        return;
    }


    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(
            renderer.GetNativeRenderer(),
            surface);

    SDL_Rect destination;

    destination.x = 10;
    destination.y = 10;
    destination.w = surface->w;
    destination.h = surface->h;

    SDL_RenderCopy(
        renderer.GetNativeRenderer(),
        texture,
        nullptr,
        &destination);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}