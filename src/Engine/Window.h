#pragma once

#include <SDL.h>
#include <string>

class Window
{
public:

    Window(const std::string& title, int width, int height);

    ~Window();
    // Allows other systems to access the SDL window safely:
    SDL_Window* GetNativeWindow() const;

 // Stores SDL window internally:
private:

    SDL_Window* m_window = nullptr;
};