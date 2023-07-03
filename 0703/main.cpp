#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOTAL 2000 // total number of steps
#define OUTSTEP 10 // output position data every OUTSTEP
int NSITE;

typedef struct
{
  double x;
  double y;
} SITE; // 構造体 SITE を定義する

SITE sdata[] = { // SITE構造体の配列 sdata を宣言，初期化する
    {0.0000, 0.0000},
    {35.3832, 7.7535},
    {25.7485, 9.2398},
    {72.2587, 17.4157},
    {47.9476, 9.2770},
    {66.8752, 6.2362},
    {91.3694, 2.0472},
    {29.1208, 14.9303},
    {95.5290, 3.6940},
    {69.0359, 16.1571},
    {40.3027, 14.4267},
    {11.4566, 8.2260},
    {2.8748, 6.8520},
    {33.5490, 15.0859},
    {20.3436, 10.9085},
    {53.2670, 15.7341},
    {11.1209, 3.5267},
    {46.9771, 16.1608},
    {58.2476, 1.1426},
    {24.2500, 6.9601},
    {7.7425, 3.1843},
    {38.0444, 19.7290},
    {85.1253, 4.6644},
    {58.3331, 5.3786},
    {83.2118, 5.9963},
    {87.3775, 7.4886},
    {24.3385, 18.1610},
    {44.6760, 13.8218},
    {50.1236, 11.3541},
    {99.7986, 19.1290},
    {41.8867, 5.2333},
    {100.0000, 20.0000}};

void output(int step) // == 途中データをファイルに出力
{
  int i;
  char cfile[100];
  FILE *fout;

  sprintf(cfile, "%7.7d.dat", step);
  fout = fopen(cfile, "w");
  for (i = 0; i < NSITE; i++)
  {
    fprintf(fout, "%8.3f %8.3f\n", sdata[i].x, sdata[i].y);
  }
  fclose(fout);

  return;
}

double calc_dist() //======= 経路の全長を求める
{
  int i;
  double x1, y1;
  double x2, y2;
  double dx, dy;
  double dsum = 0.0;

  for (i = 1; i < NSITE; i++)
  {
    x1 = sdata[i - 1].x;
    y1 = sdata[i - 1].y;
    x2 = sdata[i].x;
    y2 = sdata[i].y;
    dx = x1 - x2;
    dy = y1 - y2;
    dsum += sqrt(dx * dx + dy * dy);
  }
  return dsum;
}

double myrand() //======================== [0,1] の一様乱数生成
{
  return rand() / (double)(RAND_MAX);
}

void exchange(int i, int j) //=====================================
{
  SITE stemp; // SITE型の一時変数 stemp を使ってサイト i と j を交換

  stemp.x = sdata[i].x;
  stemp.y = sdata[i].y;
  sdata[i].x = sdata[j].x;
  sdata[i].y = sdata[j].y;
  sdata[j].x = stemp.x;
  sdata[j].y = stemp.y;

  return;
}

int main() //=====================================================
{
  int step = 0;
  int i, j, n;
  double T = 10000;
  double distance, dtemp;
  FILE *fdist;

  NSITE = sizeof sdata / sizeof sdata[0]; // サイト数
  printf("NSITE = %d\n", NSITE);

  fdist = fopen("sd_distance.dat", "w"); // 距離を出力するファイル
  distance = calc_dist();
  // printf("%10d %12.6f\n", step, distance);
  fprintf(fdist, "%10d %12.6f\n", step, distance);
  output(step);

  for (step = 1; step <= TOTAL; step++)
  {
  PICKUP_I: // ランダムに２つのサイトを選ぶ，ただしstartとgoalは固定
    i = (NSITE - 1) * myrand();
    if ((i == 0) || (i == NSITE - 1))
      goto PICKUP_I;
  PICKUP_J:
    j = (NSITE - 1) * myrand();
    if ((j == 0) || (j == NSITE - 1))
      goto PICKUP_J;
    if (i == j)
      goto PICKUP_J; // i と j が同じなら選び直し

    exchange(i, j);      // ２つのサイトを交換
    dtemp = calc_dist(); // 新しい経路での距離を計算

    if (dtemp < distance)
    { // 交換すると距離が減少したので新経路を採用（Steepest Descent）
      distance = dtemp;
    }
    else
    { // 交換すると距離が増加したので元に戻す
      if (myrand() < exp(-(dtemp - distance) / T))
      {
        distance = dtemp;
      }
      else
      {
        exchange(i, j);
      }
    }
    if (step % 1000 == 0)
    {
      T *= 0.5;
    }

    // printf("%10d %12.6f\n", step, distance);
    fprintf(fdist, "%10d %12.6f\n", step, distance);
    if (step % OUTSTEP == 0)
    { // OUTSTEP ごとに経路データを出力
      output(step);
    }
  }

  fclose(fdist);
  return 0;
}