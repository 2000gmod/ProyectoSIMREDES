#pragma once

#include "Obstacle.hpp"
#include "Receptor.hpp"
#include "Util.hpp"
#include <nlohmann/json.hpp>
#include <vector>


class Simulator {
public:
    struct DataRes {
        unsigned long size;
        std::vector<Receptor>& receptors;
        std::vector<FPType>& probCache;
    };
private:
    FPType pFall;
    unsigned int substepNum;
    std::vector<Obstacle> obstacles;
    std::vector<Receptor> receptors;
    std::vector<FPType> probCache;
public:
    Simulator(const nlohmann::json& config);
    DataRes GetResults();
private:
    FPType GetReceptorProb(const Receptor& rec);
};