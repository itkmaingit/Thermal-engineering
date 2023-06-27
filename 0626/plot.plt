T = 5.0
filename = sprintf("histogram_%.1f.dat",T)
pngname=sprintf("graph_%.1f.png",T)


set terminal pngcairo
set output pngname


set xlabel "x"
set ylabel "probability distribution"


f(x) = exp(-(0.01*x**6 - 3*x**2)/T)/1000


plot filename using 1:2 with lines title "probability distribution", f(x) with lines title "Boltzmann distribution"