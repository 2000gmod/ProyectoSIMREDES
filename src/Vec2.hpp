#pragma once

#include "Util.hpp"


struct Vec2 {
    FPType x, y;

    Vec2(FPType x, FPType y) : x(x), y(y) { }
    Vec2() : x(0), y(0) { }

    Vec2(const Vec2& other) : x(other.x), y(other.y) { }

    static FPType distance(const Vec2& a, const Vec2& b);
};

Vec2 operator+ (const Vec2& lhs, const Vec2& rhs);
Vec2 operator- (const Vec2& vec);
Vec2 operator- (const Vec2& lhs, const Vec2& rhs);
Vec2 operator* (FPType lhs, const Vec2& rhs);
Vec2 operator* (const Vec2& lhs, FPType rhs);