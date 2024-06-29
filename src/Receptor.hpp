#pragma once

#include <string>
#include "Util.hpp"
#include "Vec2.hpp"

struct Receptor {
    std::string name;
    Vec2 pos;
    FPType probLoss;
};