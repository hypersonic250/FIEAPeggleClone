#pragma once

#include <cmath>

struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;

    Vector2() = default;

    Vector2(float xValue, float yValue)
        : x(xValue), y(yValue)
    {
    }

    Vector2 operator+(const Vector2& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vector2 operator-(const Vector2& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vector2 operator*(float scalar) const
    {
        return { x * scalar, y * scalar };
    }

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Normalized() const
    {
        float length = Length();

        if (length == 0.0f)
        {
            return {};
        }

        return { x / length, y / length };
    }
};