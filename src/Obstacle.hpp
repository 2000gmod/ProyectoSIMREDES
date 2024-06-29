#pragma once
#include "Util.hpp"
#include "Vec2.hpp"
#include "Parser.hpp"
#include <memory>

class Obstacle {
private:
    FPType radius, factor;
    Vec2 pos;
    std::shared_ptr<MathNode> expr;
public:
    Obstacle(FPType radius, FPType factor, Vec2 pos, const std::string& exprStr) : radius(radius), factor(factor), pos(pos) {
        expr = ParseExpr(exprStr);
    }

    FPType EvaluateProb(const Vec2& x);
};