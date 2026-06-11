#include "Peg.h"

#include "Engine/Renderer.h"

Peg::Peg(float x, float y, PegType type)
{
	//store the peg's position and type; initialize it as unlit
    m_position = Vector2(x, y);
    m_type = type;
}

void Peg::Render(Renderer& renderer)
{
	//pegs marked as hit have been removed from the board and should not be rendered
    if (m_hit)
    {
        return;
    }

    //determine the peg's color based on both its type and whether it has been struck during the current turn
    switch (m_type)
    {
    case PegType::Blue:

		// lit pegs are brighter than unlit ones to show that they have been hit during the current turn
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

	//draw the peg as a filled circle at its position; called from the main render loop
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
    // marks a peg as permanently removed from the board 
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
	// allows gameplay systems to change a peg's role (e.g., turning a blue peg into an orange one); also used to place special pegs like the purple and green ones
    m_type = type;
}

bool Peg::IsLit() const
{
    return m_isLit;
}

void Peg::SetLit(bool lit)
{
	// marks a peg as lit, which visually indicates that it has been hit during the current turn; this is reset at the end of each turn
    m_isLit = lit;
}