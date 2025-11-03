#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "strategy.hpp"
#include "market_simulator.hpp"
#include "portfolio.hpp"

int main(int argc, char** argv) {
    std::string data_path = "data\\sample_data.csv";
    if (argc > 1) data_path = argv[1];

    std::vector<double> prices;
    if (!read_csv_prices(data_path, prices)) {
        std::cerr << "Failed to read data file: " << data_path << "\n";
        return 1;
    }

    // parameters (these can be tuned)
    size_t window = 20;
    double z_entry = 1.0;
    double z_exit = 0.5;
    double fee = 0.0001; // 0.01% per leg

    MeanReversionStrategy strat(window, z_entry, z_exit, fee);
    Portfolio port(100000.0);

    std::ofstream trade_log("trades.csv");
    trade_log << "index,timestamp,side,entry_price,exit_price,pnl\n";

    double total_realized = 0.0;
    size_t idx = 0;
    for (double p : prices) {
        TradeEvent ev = strat.on_price(p);
        if (ev.opened) {
            port.open(ev.side, ev.entry_price);
            // we log open with empty exit
            trade_log << idx << "," << idx << "," << ev.side << "," << std::fixed << std::setprecision(6) << ev.entry_price << "," << "" << "," << "" << "\n";
        }
        if (ev.closed) {
            double pnl = port.close(ev.exit_price);
            // port.close returns pnl computed by portfolio logic; but the strategy already computed pnl with fees.
            // We prefer strategy.pnl (which includes fee model). Use that for reporting and aggregate.
            total_realized += ev.pnl;
            trade_log << idx << "," << idx << "," << ev.side << "," << std::fixed << std::setprecision(6) << ev.entry_price << "," << ev.exit_price << "," << ev.pnl << "\n";
        }
        ++idx;
    }

    std::cout << "Backtest complete. Total realized PnL = " << total_realized << "\n";
    std::cout << "Trades: " << port.trades() << ", Portfolio cash: " << port.cash() << "\n";
    std::cout << "Written trade log to trades.csv\n";
    return 0;
}
