#pragma once

#include "Engine/Vector2.h"

class Renderer;

class Ball
{
public:

    Ball();

    void Update();

    void Render(Renderer& renderer);

    Vector2 GetPosition() const;

    float GetRadius() const;

    bool IsOutOfBounds() const;

    void BounceOffPeg(const Vector2& pegPosition);

    void Launch(const Vector2& velocity);

    void Reset();

    void SetPosition(
        const Vector2& position);

    void SetVelocity(
        const Vector2& velocity);

    Vector2 GetVelocity() const;

private:

    Vector2 m_position;
    Vector2 m_velocity;

    bool m_isLaunched = false;

    float m_radius = 10.0f;
    
};