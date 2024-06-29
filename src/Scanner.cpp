#include "Scanner.hpp"
#include "Util.hpp"
#include <array>
#include <exception>
#include <stdexcept>
#include <string_view>


typedef std::array<bool, 256> CharLUT;

static constexpr CharLUT CreateLUT(const std::string_view& str) {
    CharLUT out;
    for (char c : str) {
        out.at(c) = true;
    }
    return out;
}

static const auto Digits = CreateLUT("0123456789");
static const auto Idents = CreateLUT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

Scanner::Scanner(const std::string& src) : src(src) { }

std::vector<Token> Scanner::Tokenize() {
    while (current < (int) src.length()) {
        start = current;
        ScanToken();
    }
    return tokens;
}

void Scanner::ScanToken() {
    char c = Advance();

    switch (c) {
        case ' ':
            break;
        case '(':
            tokens.push_back({TokenType::PAREN_L});
            break;
        case ')':
            tokens.push_back({TokenType::PAREN_R});
            break;
        case '+':
            tokens.push_back({TokenType::PLUS});
            break;
        case '-':
            tokens.push_back({TokenType::MINUS});
            break;
        case '*':
            tokens.push_back({TokenType::STAR});
            break;
        case '/':
            tokens.push_back({TokenType::SLASH});
            break;
        case '^':
            tokens.push_back({TokenType::POW});
            break;
        default:
            if (Digits.at(c)) ScanNumber();
            else if (Idents.at(c)) ScanIdentifier();

    }
}

char Scanner::Advance() {
    current++;
    return src.at(current - 1);
}

char Scanner::Peek() {
    if (current >= (int) src.length()) return '\0';
    return src.at(current);
}

void Scanner::ScanNumber() {
    while (Digits.at(Peek())) Advance();
    Token tok({TokenType::NUMBER});

    if (Peek() == '.' && Digits.at(src.at(current + 1))) {
        Advance();
        while (Digits.at(Peek())) Advance();
    } 
    //else throw std::runtime_error("Hey");
    
    tok.number = (FPType) std::stod(src.substr(start, current - start));

    tokens.push_back(tok);
}

void Scanner::ScanIdentifier() {
    while (Idents.at(Peek())) Advance();

    auto text = src.substr(start, current - start);
    Token tok({TokenType::IDENTIFIER});
    tok.identifier = text;
    tokens.push_back(tok);
}