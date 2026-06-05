#pragma once

#include "Engine/Vector2.h"

class Renderer;

enum class PegType
{
    Blue,
    Orange,
    Green,
    Purple
};

class Peg
{
public:
    Peg(float x, float y, PegType type);

    void Render(Renderer& renderer);

    bool IsHit() const;
    void SetHit(bool hit);

    bool IsLit() const;
    void SetLit(bool lit);

    Vector2 GetPosition() const;
    float GetRadius() const;
    PegType GetType() const;

    void SetType(PegType type);

private:
    Vector2 m_position;

    float m_radius = 12.0f;

    PegType m_type = PegType::Blue;

    bool m_isLit = false;
    bool m_hit = false;

};
