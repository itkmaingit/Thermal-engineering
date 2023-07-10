#!/usr/bin/gnuplot -persist

set datafile separator ","
set terminal pngcairo enhanced font "arial,10" size 800,600

# 変数をセット
filename=system("echo $FILENAME")

set output filename.".png"

set title filename
set xlabel "Log(Rank)"
set ylabel "Log(Rmax)"
set grid
set logscale xy

plot filename.".csv" using 1:2 with linespoints title filename