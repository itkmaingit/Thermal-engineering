set terminal pngcairo
set output 'output.png'
set xlabel "t"
set ylabel "Distance from Origin"
plot 'brown.dat' using 1:(sqrt($2**2+$3**2)) with lines title 'Distance'