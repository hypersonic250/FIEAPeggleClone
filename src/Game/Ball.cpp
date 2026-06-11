#include "Ball.h"

#include "Engine/Renderer.h"
#include "Engine/Time.h"

#include <iostream>

Ball::Ball()
{
    //spawn the ball at the launcher position, keep it stationary until launched
    m_position = Vector2(640.0f, 80.0f);

    m_velocity = Vector2(0.0f, 0.0f);
}

void Ball::Update()
{
    // doesn't simulate physics until the player launches the ball
    if (!m_isLaunched)
    {
        return;
    }

    float gravity = 500.0f;

	// apply gravity to the vertical velocity; update ball's position using delta time
    m_velocity.y += gravity * Time::DeltaTime();

    m_position += m_velocity * Time::DeltaTime();

    // ball bounces off left wall
    if (m_position.x - m_radius < 0)
    {
        m_position.x = m_radius;
        m_velocity.x *= -1.0f;
    }

	//ball bounces off right wall
    if (m_position.x + m_radius > 1280)
    {
        m_position.x = 1280 - m_radius;
        m_velocity.x *= -1.0f;
    }

	// ball bounces off of the ceiling
    if (m_position.y - m_radius < 0)
    {
        m_position.y = m_radius;
        m_velocity.y *= -1.0f;
    }

}

//draw the ball as a white circle; called from the main render loop
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
	//calulate the collision normal from the peg to the ball; reflect the velocity across this normal to create a bounce effect
    Vector2 normal =
        (m_position - pegPosition).Normalized();

    //computes the velocity projected onto the collision normal
    float dot =
        m_velocity.x * normal.x +
        m_velocity.y * normal.y;

    //reflect the velocity vector to create a bounce response
    m_velocity =
        m_velocity - normal * (2.0f * dot);

	//reduce upward velocity to prevent excessively high bounces; creates a more controlled feel when hitting pegs
    if (m_velocity.y < 0.0f)
    {
        m_velocity.y *= 0.4f;
    }
}

bool Ball::IsOutOfBounds() const
{
	// checks if the ball has fallen below the bottom of the screen, which would indicate it has been lost
    return m_position.y - m_radius > 720;
}

void Ball::Reset()
{
	//resets the ball to the launch position and stops its movement; called after a turn ends or when the player loses a ball
    m_position = Vector2(640.0f, 80.0f);

    m_velocity = Vector2(200.0f, 0.0f);

    m_isLaunched = false;
}

void Ball::Launch(const Vector2& velocity)
{
	//launch the ball with the specified starting velocity; called when the player clicks to shoot the ball from the launcher
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
	// allows external code to directly set the ball's velocity, which can be useful for events like multiball that modify the ball's movement
    m_velocity = velocity;
    m_isLaunched = true;
}
Vector2 Ball::GetVelocity() const
{
    return m_velocity;
}