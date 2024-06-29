#include "Simulator.hpp"
#include <fstream>
#include <iostream>
#include <print>

#include <nlohmann/json.hpp>

using nlohmann::json;

json loadConfig() {
    std::ifstream file("config.json");

    try {
        return json::parse(file);
    }
    catch (json::parse_error& e) {
        std::cerr << __PRETTY_FUNCTION__ << ":\n";
        std::cerr << e.what() << "\n";
        std::exit(1);
    }
}

int main() {
    auto config = loadConfig();
    Simulator sim(config);

    auto results = sim.GetResults();

    for (unsigned int i = 0; i < results.size; i++) {
        std::println("Blocking probability for receptor \"{}\" => {}", results.receptors[i].name,  1.0 - results.probCache[i]);
    }
}