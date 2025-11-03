#include "market_simulator.hpp"
#include <fstream>
#include <sstream>

bool read_csv_prices(const std::string& path, std::vector<double>& out_prices) {
    std::ifstream ifs(path);
    if (!ifs) return false;
    std::string line;
    // header
    if (!std::getline(ifs, line)) return false;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string ts, price_str;
        if (!std::getline(ss, ts, ',')) continue;
        if (!std::getline(ss, price_str, ',')) continue;
        try {
            double price = std::stod(price_str);
            out_prices.push_back(price);
        } catch (...) {
            continue;
        }
    }
    return true;
}
