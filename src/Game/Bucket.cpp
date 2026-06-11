#include <SDL.h>

#include "Bucket.h"

#include "Engine/Renderer.h"
#include "Engine/Time.h"

Bucket::Bucket()
{
	// spawn the bucket at the bottom center of the screen
    m_position = Vector2(640.0f, 690.0f);
}

void Bucket::Update()
{
	//moves the bucket horizontally across the screen at a fixed speed; reverses direction when it reaches the edges of the screen
    m_position.x +=
        m_speed *
        m_direction *
        Time::DeltaTime();

	// reverse direction when hitting the left edge
    if (m_position.x < m_width / 2.0f)
    {
        m_position.x = m_width / 2.0f;
        m_direction = 1;
    }

	// reverse direction when hitting the right edge
    if (m_position.x > 1280 - m_width / 2.0f)
    {
        m_position.x = 1280 - m_width / 2.0f;
        m_direction = -1;
    }
}

void Bucket::Render(Renderer& renderer)
{
    renderer.SetColor(255, 255, 0);

    SDL_Rect rect;

    rect.x =
        static_cast<int>(
            m_position.x - m_width / 2.0f);

    rect.y =
        static_cast<int>(
            m_position.y - m_height / 2.0f);

    rect.w =
        static_cast<int>(m_width);

    rect.h =
        static_cast<int>(m_height);

    SDL_RenderFillRect(
        renderer.GetNativeRenderer(),
        &rect);

	//render side walls to visually ressemble classic peckle bucket design; purely aesthetic
    SDL_Rect leftWall;
    leftWall.x = rect.x;
    leftWall.y = rect.y - 20;
    leftWall.w = 10;
    leftWall.h = 20;

    SDL_Rect rightWall;
    rightWall.x = rect.x + rect.w - 10;
    rightWall.y = rect.y - 20;
    rightWall.w = 10;
    rightWall.h = 20;

    SDL_RenderFillRect(
        renderer.GetNativeRenderer(),
        &leftWall);

    SDL_RenderFillRect(
        renderer.GetNativeRenderer(),
        &rightWall);

}

Vector2 Bucket::GetPosition() const
{
    return m_position;
}

float Bucket::GetWidth() const
{
    return m_width;
}

float Bucket::GetHeight() const
{
    return m_height;
}