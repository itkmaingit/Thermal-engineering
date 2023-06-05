set terminal pngcairo
set output 'output.png'
set xlabel "step"
set ylabel "VAF(Velocity auto correation function)"
plot 'vaf.dat' using 1:2 with lines title 'Relationship between step and VAF'