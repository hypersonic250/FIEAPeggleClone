#pragma once

#include <SDL.h>

class Window;

class Renderer
{
public:

    Renderer(Window& window);

    ~Renderer();

    void Clear();

    void Present();

    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

    void DrawPoint(int x, int y);

    void DrawCircle(int centerX, int centerY, int radius);

    void DrawLine(
        int x1,
        int y1,
        int x2,
        int y2
    );

    SDL_Renderer* GetNativeRenderer() const;

private:

    SDL_Renderer* m_renderer = nullptr;
};