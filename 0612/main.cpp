#include <stdio.h>
#include <math.h>

#define MAX_DATA 10000
#define PI (4 * atan(1.0))

int main()
{
  int ndata, i, j;
  double indata[MAX_DATA];
  double omega, iomega, cdata, sdata, power;
  FILE *fin, *fout;

  fin = fopen("melody.dat", "r"); // File for Input Data
  if (fin == NULL)
  {
    printf("No INPUT File\n");
    return -1;
  }
  fout = fopen("sample_power.dat", "w"); // File for Output Data

  ndata = 0;
  while ((ndata < MAX_DATA) && (fscanf(fin, "%lf", &indata[ndata]) == 1))
    ndata++;
  fclose(fin);
  printf("Number of data =%5d\n", ndata);

  omega = 2.0 * PI / ndata;

  for (i = 0; i < ndata; i++)
  {
    cdata = 0.0;
    sdata = 0.0;
    iomega = omega * i;
    for (j = 0; j < ndata; j++)
    {
      cdata += indata[j] * cos(iomega * j);
      sdata += indata[j] * sin(iomega * j);
    }
    power = cdata * cdata + sdata * sdata;
    fprintf(fout, "%5d %10.4lf\n", i, power);
  }

  fclose(fout);
  return 0;
}