#include "portfolio.hpp"

Portfolio::Portfolio(double initial_cash) : cash_(initial_cash) {}

void Portfolio::open(int side, double price) {
    if (position_ != 0) return; // only one unit / single position strategy
    position_ = side;
    entry_price_ = price;
}

double Portfolio::close(double price) {
    if (position_ == 0) return 0.0;
    double pnl = (price - entry_price_) * static_cast<double>(position_);
    cash_ += pnl;
    total_pnl_ += pnl;
    position_ = 0;
    entry_price_ = 0.0;
    ++trades_;
    return pnl;
}
