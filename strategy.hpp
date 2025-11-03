#pragma once
#include <string>
#include "utils.hpp"

struct TradeEvent {
    bool opened = false;   // true if a new position was opened
    bool closed = false;   // true if a position was closed (realized)
    int side = 0;          // +1 long, -1 short
    double price = 0.0;    // price at event (entry or exit)
    double entry_price = 0.0;
    double exit_price = 0.0;
    double pnl = 0.0;      // realized PnL for closed trades
};

class MeanReversionStrategy {
public:
    MeanReversionStrategy(size_t window_size, double z_entry, double z_exit, double fee = 0.0);
    // Process a price tick and return an event (open/close) if any
    TradeEvent on_price(double price);

private:
    RollingWindow window_;
    size_t window_size_;
    double z_entry_;
    double z_exit_;
    bool position_open_ = false;
    int position_side_ = 0; // +1 long, -1 short
    double entry_price_ = 0.0;
    double fee_rate_ = 0.0; // fraction per round-trip (applied on both open and close as simple model)
};
