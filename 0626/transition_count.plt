# ファイル名を設定
filename = "transition_count.dat"

# PNG出力の設定
set terminal pngcairo
set output "transition_count.png"

# グラフの設定
set xlabel "1/T"
set ylabel "transition_count"
set xrange [0.2:1]  # x軸の範囲を設定
set logscale y  # y軸を対数軸に設定

# データをプロット
plot filename using 1:2 with lines title "Transition Count"
