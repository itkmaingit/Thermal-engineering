#!/bin/bash

# CSVファイルごとにループ
for csv_file in *.csv
do
    # 拡張子を除いたファイル名を取得
    filename=$(basename "$csv_file" .csv)
    # 環境変数としてファイル名をセット
    export FILENAME="$filename"
    # gnuplotスクリプトを実行
    gnuplot plot_country.plt
done
