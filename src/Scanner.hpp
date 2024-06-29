#pragma once

#include "Util.hpp"
#include <string>
#include <vector>


enum class TokenType {
    NUMBER,
    IDENTIFIER,
    PAREN_L,
    PAREN_R,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    POW
};

struct Token {
    TokenType type;
    FPType number = 0.0;
    std::string identifier = {};
};

class Scanner {
private:
    std::vector<Token> tokens;
    int start = 0, current = 0;
    std::string src;
public:
    explicit Scanner(const std::string& src);
    std::vector<Token> Tokenize();
private:
    void ScanToken();
    char Advance();
    char Peek();

    void ScanNumber();
    void ScanIdentifier();
};