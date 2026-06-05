#include "Ball.h"

#include "Engine/Renderer.h"
#include "Engine/Time.h"

#include <iostream>

Ball::Ball()
{
    m_position = Vector2(640.0f, 80.0f);

    m_velocity = Vector2(0.0f, 0.0f);
}

void Ball::Update()
{
    if (!m_isLaunched)
    {
        return;
    }

    float gravity = 500.0f;

    m_velocity.y += gravity * Time::DeltaTime();

    m_position += m_velocity * Time::DeltaTime();

    if (m_position.x - m_radius < 0)
    {
        m_position.x = m_radius;
        m_velocity.x *= -1.0f;
    }

    if (m_position.x + m_radius > 1280)
    {
        m_position.x = 1280 - m_radius;
        m_velocity.x *= -1.0f;
    }

    if (m_position.y - m_radius < 0)
    {
        m_position.y = m_radius;
        m_velocity.y *= -1.0f;
    }

}


void Ball::Render(Renderer& renderer)
{
    renderer.SetColor(255, 255, 255);

    renderer.DrawCircle(
        static_cast<int>(m_position.x),
        static_cast<int>(m_position.y),
        static_cast<int>(m_radius)
    );
}

Vector2 Ball::GetPosition() const
{
    return m_position;
}

float Ball::GetRadius() const
{
    return m_radius;
}

void Ball::BounceOffPeg(const Vector2& pegPosition)
{
    Vector2 normal =
        (m_position - pegPosition).Normalized();

    float dot =
        m_velocity.x * normal.x +
        m_velocity.y * normal.y;

    m_velocity =
        m_velocity - normal * (2.0f * dot);

    if (m_velocity.y < 0.0f)
    {
        m_velocity.y *= 0.4f;
    }
}

bool Ball::IsOutOfBounds() const
{
    return m_position.y - m_radius > 720;
}

void Ball::Reset()
{
    m_position = Vector2(640.0f, 80.0f);

    m_velocity = Vector2(200.0f, 0.0f);

    m_isLaunched = false;
}

void Ball::Launch(const Vector2& velocity)
{
    m_velocity = velocity;
    m_isLaunched = true;
}

void Ball::SetPosition(
    const Vector2& position)
{
    m_position = position;
}

void Ball::SetVelocity(
    const Vector2& velocity)
{
    m_velocity = velocity;
    m_isLaunched = true;
}
Vector2 Ball::GetVelocity() const
{
    return m_velocity;
}