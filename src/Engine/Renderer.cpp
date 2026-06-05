#include "Renderer.h"

#include "Window.h"

#include <stdexcept>

Renderer::Renderer(Window& window)
{
    m_renderer = SDL_CreateRenderer(
        window.GetNativeWindow(),
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (m_renderer == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void Renderer::DrawPoint(int x, int y)
{
    SDL_RenderDrawPoint(m_renderer, x, y);
}

void Renderer::DrawCircle(int centerX, int centerY, int radius)
{

    for (int w = -radius; w <= radius; ++w)
    {
        for (int h = -radius; h <= radius; ++h)
        {
            if (w * w + h * h <= radius * radius)
            {
                SDL_RenderDrawPoint(
                    m_renderer,
                    centerX + w,
                    centerY + h
                );
            }
        }
    }
}

SDL_Renderer* Renderer::GetNativeRenderer() const
{
    return m_renderer;
}

void Renderer::DrawLine(
    int x1,
    int y1,
    int x2,
    int y2)
{
    SDL_RenderDrawLine(
        m_renderer,
        x1,
        y1,
        x2,
        y2
    );
}