# Artemis

Artemis is a lightweight quantitative trading engine built in C++ that implements a simple mean reversion strategy with historical backtesting.  
The project focuses on modular design, performance optimization, and clarity — serving as a foundation for exploring algorithmic trading systems.

---

## Overview
Artemis models basic trading strategies using historical price data to identify potential buy and sell opportunities based on short-term price deviations.  
It includes a simple backtesting module to evaluate performance metrics such as returns, drawdown, and win rate.

---

## Features
- **Mean Reversion Strategy:** Executes simulated trades when price deviates significantly from its moving average.  
- **Backtesting Engine:** Loads historical market data (CSV format) and simulates trades over time.  
- **Performance Metrics:** Tracks total returns, accuracy, and volatility of simulated strategies.  
- **Modular Architecture:** Clean separation between data handling, strategy logic, and analysis modules.

---

## Technologies
- **Language:** C++17  
- **Libraries:** STL, `<fstream>`, `<vector>`, `<algorithm>`  
- **Tools:** Git, CMake, g++  
- **Optional:** Python for data preprocessing and visualization
