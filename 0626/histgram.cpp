#include <stdio.h>

#define XMIN -5.0
#define XMAX 5.0
#define NX 100 // ヒストグラム配列サイズ, XMAX-XMIN を NX個に分割する

int main()
{
  int count[NX];
  int i, sum, step;
  double dx = (XMAX - XMIN) / NX;
  double x;

  sum = 0;
  for (i = 0; i < NX; i++)
    count[i] = 0;

  while (scanf("%d %lf", &step, &x) == 2)
  {
    sum++;
    // printf("%7d %5d\n",step,sum);  for debugging

    i = (x - XMIN) / dx;
    if ((0 <= i) && (i < NX))
      count[i]++;
  }

  for (i = 0; i < NX; i++)
    printf("%8.3f %8.5f %5d\n", i * dx + XMIN, count[i] / (double)sum, count[i]);

  return 0;
}