#pragma once

template<typename T>
struct Vec2
{
    Vec2() = default;
    Vec2(T inX, T inY) : x(inX),y(inY) {};
    Vec2(const ImVec2& in) : x(in.x),y(in.x) {};


    T x {};
    T y {};
};

using Vec2i = Vec2<int>;