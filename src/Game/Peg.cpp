#include "Peg.h"

#include "Engine/Renderer.h"

Peg::Peg(float x, float y, PegType type)
{
    m_position = Vector2(x, y);
    m_type = type;
}

void Peg::Render(Renderer& renderer)
{
    if (m_hit)
    {
        return;
    }

    switch (m_type)
    {
    case PegType::Blue:

        if (m_isLit)
        {
            renderer.SetColor(100, 180, 255);
        }
        else
        {
            renderer.SetColor(0, 100, 255);
        }
        break;

    case PegType::Orange:
		if (m_isLit)
		{
			renderer.SetColor(255, 220, 0);
		}
        else
        {
        renderer.SetColor(255, 120, 0);
        }
        break;

    case PegType::Green:
        if (m_isLit)
		{
			renderer.SetColor(0, 255, 100);
		}
		else
		{
            renderer.SetColor(0, 255, 0);
		}
        break;

    case PegType::Purple:
        if (m_isLit)
        {
			renderer.SetColor(255, 100, 255);
        }
        else
        {
            renderer.SetColor(200, 0, 255);
        }
        break;
    }

    renderer.DrawCircle(
        static_cast<int>(m_position.x),
        static_cast<int>(m_position.y),
        static_cast<int>(m_radius)
    );
}

bool Peg::IsHit() const
{
    return m_hit;
}

void Peg::SetHit(bool hit)
{
    m_hit = hit;
}

Vector2 Peg::GetPosition() const
{
    return m_position;
}

float Peg::GetRadius() const
{
    return m_radius;
}

PegType Peg::GetType() const
{
    return m_type;
}

void Peg::SetType(PegType type)
{
    m_type = type;
}

bool Peg::IsLit() const
{
    return m_isLit;
}

void Peg::SetLit(bool lit)
{
    m_isLit = lit;
}