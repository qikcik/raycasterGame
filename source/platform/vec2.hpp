#pragma once

template<typename T>
struct Vec2
{
    Vec2() = default;
    Vec2(T inX, T inY) : x(inX),y(inY) {};
    Vec2(const ImVec2& in) : x(in.x),y(in.x) {};

    void operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
    }

    Vec2 operator*(T other)
    {
        return {x*other,y*other};
    }

    T x {};
    T y {};
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;