#pragma once
#include <string>
#include <vector>

// Read a simple CSV with header timestamp,price and fill prices vector.
// Returns true on success.
bool read_csv_prices(const std::string& path, std::vector<double>& out_prices);
