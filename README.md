# libindicators

A lightweight and fast implementation of a number of technical indicators.

**THIS IS A WORK IN PROGRESS**

## Supported Indicators

- SMA
- EMA
- MACD
- RSI
- MFI
- CCI
- ATR
- OBV
- Keltner Channel
- Bollinger Bands
- Williams %R
- Stochastic %K and %D
- Supertrend
- Slope of Linear Regression

## Planned Indicators

- A/D
- Chaikin Oscillator
- ROC

... _And Many More_ (Suggestions welcome)

## Performance

This library aims to target applications which keep these indicators for a long time in memory and require high performance. Wherever possible, each indicator has been designed to work with rolling windows so that each update works in O(1) time. So, if you are calculating SMA 5 or SMA 200, the performance is the same.

A basic performance benchmarking script is included in the source. The script reads kline data from a CSV file and calculates every indicator supported. The data is calculated one line at a time as if replaying real time data. Note that it is important to run the current benchmarking script with `-O0` flag to prevent the compiler from optimising away the `get` functions.

The included `downloader.sh` can be used to download sample data from Binance.

A simple run of the benchmarking script tells that it can process **16992 data points in 11.916ms, or less than a microsecond per data point**. Note that in each iteration we calculate _every single_ indicator supported.
