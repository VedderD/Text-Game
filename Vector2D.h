#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

struct Vector2D
{
    float x;
    float y;

    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }
};

#endif