#pragma once
#include <string>

class Portfolio {
public:
    Portfolio(double initial_cash = 100000.0);
    double cash() const { return cash_; }
    int position() const { return position_; }
    double entry_price() const { return entry_price_; }
    int trades() const { return trades_; }
    double total_pnl() const { return total_pnl_; }

    // Open position of one unit on given side (+1 long, -1 short) at price
    void open(int side, double price);
    // Close current position at price, return realized pnl
    double close(double price);

private:
    double cash_ = 0.0;
    int position_ = 0;
    double entry_price_ = 0.0;
    int trades_ = 0;
    double total_pnl_ = 0.0;
};
