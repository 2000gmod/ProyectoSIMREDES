#pragma once

#include "Scanner.hpp"
#include "Util.hpp"
#include <cmath>
#include <memory>
#include <stdexcept>

struct MathNode {
    virtual FPType Evaluate(FPType r) = 0;
    virtual ~MathNode() = default;
};

struct GroupNode : public MathNode {
    std::shared_ptr<MathNode> subnode;

    GroupNode(const std::shared_ptr<MathNode>& subn) : subnode(subn) { }

    FPType Evaluate(FPType r) override {
        return subnode->Evaluate(r);
    }
};

struct UnaryOp : public MathNode {
    std::shared_ptr<MathNode> expr;
    TokenType op;

    UnaryOp(const std::shared_ptr<MathNode>& expr, TokenType op) : expr(expr), op(op) { }

    FPType Evaluate(FPType r) override {
        auto exp = expr->Evaluate(r);
        switch (op) {
            case TokenType::PLUS:
                return exp;
            case TokenType::MINUS:
                return -exp;
            default:
                throw std::runtime_error(__PRETTY_FUNCTION__);
        }
    }
};

struct BinaryOp : public MathNode {
    std::shared_ptr<MathNode> left, right;
    TokenType op;

    BinaryOp(const std::shared_ptr<MathNode>& lhs, const std::shared_ptr<MathNode>& rhs, TokenType op) : left(lhs), right(rhs), op(op) { }

    FPType Evaluate(FPType r) override {
        auto lhs = left->Evaluate(r);
        auto rhs = right->Evaluate(r);
        switch (op) {
            case TokenType::PLUS:
                return lhs + rhs;
            case TokenType::MINUS:
                return lhs - rhs;
            case TokenType::STAR:
                return lhs * rhs;
            case TokenType::SLASH:
                return lhs / rhs;
            case TokenType::POW:
                return std::pow(lhs, rhs);
            default:
                throw std::runtime_error(__PRETTY_FUNCTION__);
        }
    }
};

struct Number : public MathNode {
    FPType value;

    Number(FPType value) : value(value) { }

    FPType Evaluate(FPType) override {
        return value;
    }
};

struct Identifier : public MathNode {
    std::string identifier;

    Identifier(const std::string& id) : identifier(id) { }

    FPType Evaluate(FPType r) override {
        if (identifier == "r") return r;
        else throw std::runtime_error("Unkown variable.");
    }
};

struct Function : public MathNode {
    std::string funcName;
    std::shared_ptr<MathNode> argument;

    Function(const std::string& fname, const std::shared_ptr<MathNode>& arg) : funcName(fname), argument(arg) { }

    FPType Evaluate(FPType r) override {
        auto arg = argument->Evaluate(r);

        if (funcName == "sin") return std::sin(arg);
        if (funcName == "cos") return std::cos(arg);
        if (funcName == "ln") return std::log(arg);
        if (funcName == "exp") return std::exp(arg);
        else throw std::runtime_error("Unknown function.");
    }
};

std::shared_ptr<MathNode> ParseExpr(const std::string& exprStr);