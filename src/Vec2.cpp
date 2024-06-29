#include "Vec2.hpp"
#include "Util.hpp"
#include <cmath>

FPType Vec2::distance(const Vec2 &a, const Vec2 &b) {
    auto difx = (a.x - b.x);
    auto dify = (a.y - b.y);
    auto arg = difx * difx + dify * dify;
    return std::sqrt(arg);
}

Vec2 operator + (const Vec2& lhs, const Vec2& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vec2 operator - (const Vec2& vec) {
    return {-vec.x, -vec.y};
}

Vec2 operator - (const Vec2& lhs, const Vec2& rhs) {
    return lhs + (-rhs);
}

Vec2 operator * (FPType lhs, const Vec2& rhs) {
    return {lhs * rhs.x, lhs * rhs.y};
}

Vec2 operator * (const Vec2& lhs, FPType rhs) {
    return rhs * lhs;
}