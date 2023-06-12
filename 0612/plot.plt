set terminal pngcairo
set output 'output.png'

set xlabel 'Frequency'
set ylabel 'Power'

set logscale x
set logscale y

plot 'sample_power.dat' using 1:2 title 'Power spector' with lines, \
     'sample_power.dat' using 1:(10000/$1) title '1/f' with lines, \
     'sample_power.dat' using 1:(10000/($1**2)) title '1/f^2' with lines
