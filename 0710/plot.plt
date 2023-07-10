#!/usr/bin/gnuplot

# 入力と出力の設定
set datafile separator ","
set terminal pngcairo enhanced font "arial,10" size 800,600
set output 'output.png'

# グラフの設定
set title "Rank vs Rmax"
set xlabel "Rank"
set ylabel "Rmax"
set grid
set logscale xy

# データのプロット
plot "data.csv" using 1:14 with linespoints title 'Rank vs Rmax'
