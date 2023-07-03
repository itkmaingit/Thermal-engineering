set terminal pngcairo
set output 'distance.png'

unset label
# グラフのタイトルと軸ラベルの設定
set title "SD vs SA"
set xlabel "Step"
set ylabel "Distance"
set yrange [0:1000]

# データをプロット
plot "sd_distance.dat" using 1:2 with lines title "SD", \
     "sa_distance.dat" using 1:2 with lines title "SA"
