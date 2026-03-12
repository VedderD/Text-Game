#pragma once

struct Vec2
{
    float x = 0.0f;
    float y = 0.0f;

    Vec2() = default;
    Vec2(float _s)
    {
        x = _s;
        y = _s;
    }
    Vec2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    Vec2 &operator*=(float s)
    {
        x *= s;
        y *= s;
        return (*this);
    }
    Vec2 &operator/=(float s)
    {
        x /= s;
        y /= s;
        return (*this);
    }
    Vec2 &operator+=(const Vec2 &v)
    {
        x += v.x;
        y += v.y;
        return (*this);
    }
    Vec2 &operator-=(const Vec2 &v)
    {
        x -= v.x;
        y -= v.y;
        return (*this);
    }
};

inline Vec2 operator +(const Vec2& _a, const Vec2& _b) {
    return Vec2(_a.x + _b.x, _a.y + _b.y);
}
inline Vec2 operator -(const Vec2& _a, const Vec2& _b) {
    return Vec2(_a.x - _b.x, _a.y - _b.y);
}
inline Vec2 operator /(const Vec2& _a, const float _b) {
    return Vec2(_a.x / _b, _a.y / _b);
}
inline Vec2 operator *(const Vec2& _a, const float _b) {
    return Vec2(_a.x * _b, _a.y * _b);
}
inline bool operator ==(const Vec2& _a, const Vec2& _b) {
    return (_a.x == _b.x) && (_a.y == _b.y);
}

extern void Print(const Vec2 &_v);
extern float Distance2D(const Vec2 &_v1, const Vec2 &_v2);