#include "strategy.hpp"
#include <cmath>

MeanReversionStrategy::MeanReversionStrategy(size_t window_size, double z_entry, double z_exit, double fee)
: window_(window_size), window_size_(window_size), z_entry_(z_entry), z_exit_(z_exit), fee_rate_(fee) {}

TradeEvent MeanReversionStrategy::on_price(double price) {
    TradeEvent ev;
    window_.add(price);
    if (window_.size() < window_size_) return ev; // not enough data

    double mu = window_.mean();
    double s = window_.stddev();
    if (s == 0.0) return ev; // no volatility

    double z = (price - mu) / s;

    if (!position_open_) {
        if (z > z_entry_) {
            // open short
            position_open_ = true;
            position_side_ = -1;
            entry_price_ = price;
            ev.opened = true;
            ev.side = position_side_;
            ev.price = price;
            ev.entry_price = price;
        } else if (z < -z_entry_) {
            // open long
            position_open_ = true;
            position_side_ = +1;
            entry_price_ = price;
            ev.opened = true;
            ev.side = position_side_;
            ev.price = price;
            ev.entry_price = price;
        }
    } else {
        if (std::abs(z) < z_exit_) {
            // close position
            double pnl = (price - entry_price_) * static_cast<double>(position_side_);
            // apply fees as simple fraction of notional both sides
            double fee = std::abs(entry_price_) * fee_rate_ + std::abs(price) * fee_rate_;
            pnl -= fee;

            ev.closed = true;
            ev.side = position_side_;
            ev.price = price;
            ev.entry_price = entry_price_;
            ev.exit_price = price;
            ev.pnl = pnl;

            // reset
            position_open_ = false;
            position_side_ = 0;
            entry_price_ = 0.0;
        }
    }

    return ev;
}
