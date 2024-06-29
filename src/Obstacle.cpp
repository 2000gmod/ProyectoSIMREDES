#include "Obstacle.hpp"
#include "Util.hpp"
#include <cmath>

FPType Obstacle::EvaluateProb(const Vec2& x) {
    auto r = Vec2::distance(x, pos);
    if (r >= radius) return 0.0;

    return factor * expr->Evaluate(r);
}