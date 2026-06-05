#pragma once

#include "Engine/Vector2.h"

class Renderer;

class Bucket
{
public:
    Bucket();

    void Update();
    void Render(Renderer& renderer);

    Vector2 GetPosition() const;
    float GetWidth() const;
    float GetHeight() const;

private:
    Vector2 m_position;

    float m_width = 140.0f;
    float m_height = 24.0f;

    float m_speed = 300.0f;
    int m_direction = 1;
};