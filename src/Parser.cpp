#include "Parser.hpp"
#include "Scanner.hpp"
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <vector>


struct Parser {
    int current = 0;
    std::vector<Token> tokens;

    Parser(const std::vector<Token>& tokens) : tokens(tokens) { }

    std::shared_ptr<MathNode> Parse() {
        auto root = std::make_shared<GroupNode>(nullptr);

        root->subnode = Addition();
        
        return root;
    }

    std::shared_ptr<MathNode> Addition() {
        auto expr = Multiplication();

        while (Match({TokenType::PLUS, TokenType::MINUS})) {
            auto op = Previous().type;
            auto rhs = Multiplication();

            expr = std::make_shared<BinaryOp>(expr, rhs, op);
        }
        return expr;
    }

    std::shared_ptr<MathNode> Multiplication() {
        auto expr = Power();

        while (Match({TokenType::STAR, TokenType::SLASH})) {
            auto op = Previous().type;
            auto rhs = Power();

            expr = std::make_shared<BinaryOp>(expr, rhs, op);
        }
        return expr;
    }

    std::shared_ptr<MathNode> Power() {
        auto expr = Unary();

        while (Match({TokenType::POW})) {
            auto op = Previous().type;
            auto rhs = Unary();

            expr = std::make_shared<BinaryOp>(expr, rhs, op);
        }
        return expr;
    }

    std::shared_ptr<MathNode> Unary() {
        if (Match({TokenType::MINUS, TokenType::PLUS})) {
            auto op = Previous().type;
            auto rhs = Unary();
            auto expr = std::make_shared<UnaryOp>(rhs, op);
            return expr;
        }
        return Call();
    }

    std::shared_ptr<MathNode> Call() {
        return Primary();
    }

    std::shared_ptr<MathNode> Primary() {
        if (Match({TokenType::NUMBER})) {
            return std::make_shared<Number>(Previous().number);
        }
        if (Match({TokenType::IDENTIFIER})) {
            return std::make_shared<Identifier>(Previous().identifier);
        }
        if (Match({TokenType::PAREN_L})) {
            auto expr = Addition();
            Consume(TokenType::PAREN_R);
            return std::make_shared<GroupNode>(expr);
        }

        throw std::runtime_error("Expected expression.");
    }

    Token& Consume(TokenType t) {
        if (Check(t)) return Advance();
        throw std::runtime_error("Unexpected token.");
    }

    bool Match(const std::initializer_list<TokenType>& list) {
        for (const auto& i : list) {
            if (Check(i)) {
                Advance();
                return true;
            }
        }
        return false;
    }

    Token& Advance() {
        return tokens.at(current++);
    }

    Token& Previous() {
        return tokens.at(current - 1);
    }

    bool Check(TokenType t) {
        if (current >= (int) tokens.size()) return false;
        return tokens.at(current).type == t;
    }

};


std::shared_ptr<MathNode> ParseExpr(const std::string& exprStr) {
    auto scanner = Scanner(exprStr);
    auto tokens = scanner.Tokenize();
    return Parser(tokens).Parse();
}