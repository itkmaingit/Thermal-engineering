set terminal pngcairo
set output "output.png"

set logscale xy

set xlabel "Resolution"
set ylabel "Number of cells"



plot "Pollock1947_Alchemy_large_200.dat" using 1:2 title "Pollock1947" with linespoints,\
     "Pollock1950_Untitled_After CR_340__large_200.dat" using 1:2 title "Pollock1950" with linespoints,\
     "StyleOfPollock2021_large_200.dat" using 1:2 title "Pollock2021" with linespoints,\
     1000000/x**2 title "1/Resolution^2" with lines