#include "Window.h"

#include <stdexcept>

Window::Window(const std::string& title, int width, int height)
{
    m_window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

	// check if the window was created successfully
    if (m_window == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
}

SDL_Window* Window::GetNativeWindow() const
{
    return m_window;
}