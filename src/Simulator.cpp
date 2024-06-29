#include "Simulator.hpp"
#include "Receptor.hpp"
#include "Util.hpp"
#include <thread>


static thread_local uint32_t randState = std::hash<std::thread::id> { } (std::this_thread::get_id());

uint32_t Random() {
    randState ^= (randState << 13);
    randState ^= (randState >> 17);
    randState ^= (randState << 5);
    return randState;
}

FPType RandomFP() {
    return (FPType) Random() / UINT32_MAX;
}

FPType RandomFP(FPType a, FPType b) {
    return a + RandomFP() * (b - a);
}

Simulator::Simulator(const nlohmann::json& config) {
    pFall = config["PFall"];
    substepNum = config["SubSteps"];

    for (auto rec : config["Receptores"]) {
        receptors.emplace_back(
            rec["Nombre"],
            Vec2 {rec["Pos"][0], rec["Pos"][1]},
            rec["PerdidaProb"]
        );
    }

    for (auto obs : config["Obstaculos"]) {
        obstacles.emplace_back(
            obs["Radio"],
            obs["Factor"],
            Vec2 {obs["Pos"][0], obs["Pos"][1]},
            obs["RFunc"]
        );
    }

    for (auto& receptor : receptors) {
        auto prob = GetReceptorProb(receptor);
        probCache.emplace_back(prob);
    }
}

FPType Simulator::GetReceptorProb(const Receptor& receptor) {
    auto prob = 1.0 - receptor.probLoss;
    auto step = receptor.pos * (1 / (FPType) substepNum);

    auto delta = Vec2::distance({}, receptor.pos) / substepNum;

    for (unsigned int i = 1; i <= substepNum; i++) {
        if (prob <= 0.0) return 0.0;

        auto stepPos = step * i;

        auto probDrop = pFall * delta;
        auto probObstacles = 0.0;
        for (auto& obs : obstacles) {
            probObstacles += obs.EvaluateProb(stepPos) * delta;
        }

        prob -= probDrop;
        prob -= probObstacles;
    }

    return prob;
}

Simulator::DataRes Simulator::GetResults() {
    return {receptors.size(), receptors, probCache};
}