# グラフィクス端末と出力ファイル名の設定
set term pngcairo size 800,200
set output "output.png"
set size ratio -1
set key outside bottom right

# データファイルの名前（ここでは"data.dat"と仮定）
datafile = "0002000.dat"

# 座標の取得
stats datafile using 1:2 nooutput
x_start = STATS_min_x
y_start = STATS_min_y
x_goal = STATS_max_x
y_goal = STATS_max_y

set lmargin at screen 0.15  # 左の余白
set rmargin at screen 0.85  # 右の余白
set bmargin at screen 0.15  # 下の余白
set tmargin at screen 0.85  # 上の余白


# ラベルの設定
set label "Start" at x_start, y_start textcolor rgb "black"
set label "Goal" at x_goal, y_goal textcolor rgb "black"

# プロットの設定
plot datafile using 1:2 with linespoints pointtype 7 pointsize 1 lc rgb "black" title "Path", \
     datafile every ::0::0 using 1:2 with points pointtype 7 pointsize 2 lc rgb "red" title "", \
     datafile every ::31::31 using 1:2 with points pointtype 7 pointsize 2 lc rgb "red" title ""
