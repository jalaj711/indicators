coins=("BTCUSDT")
interval=("5m")
yearmonth=("2025-02" "2025-03")

# Remove old file if any
rm backtest_data.csv

for coin in "${coins[@]}"; do
    for inter in "${interval[@]}"; do
        echo "Downloading coin: $coin"
        mkdir -p data/${inter}
        touch backtest_data.csv
        for year in "${yearmonth[@]}"; do
            wget -O "backtest_data.gz" "https://data.binance.vision/data/spot/monthly/klines/$coin/$inter/$coin-$inter-$year.zip"
            gunzip -c "backtest_data.gz" >> "backtest_data.csv"
            # Remove the temporary gzip file
            rm -f "backtest_data.gz"
        done
    done
done
