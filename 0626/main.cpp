// ２重井戸中の粘性支配ブラウン運動
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#define gamma 1.0          // 摩擦係数
#define delta_t 0.0002     // 時間刻み
#define TOTAL_STEP 1000000 // 計算ステップ数，もっと増やしてもいい
#define SAVE_STEP 10       // ファイル出力頻度

//---------------------------------------------------------
double fr(double factor) // 一様乱数生成
{
  return (rand() / (double)RAND_MAX * 2 - 1.0) * factor;
}
//---------------------------------------------------------
double potential(double x) // ポテンシャルエネルギー，計算の中では使わない
{
  double x2;
  x2 = x * x;
  return (0.01 * x2 * x2 - 3.0) * x2;
}
//---------------------------------------------------------
double force(double x) // ポテンシャル力
{
  double x2;
  x2 = x * x;
  return (-0.06 * x2 * x2 + 6.0) * x;
}
//---------------------------------------------------------
int main()
{
  double x;
  double prev_x;
  double factor;
  double temperature;
  int step;

  // char file_name[50];
  FILE *fout;
  // printf("Enter a temperature: ");
  // std::cin >> temperature;

  // sprintf(file_name, "calc_%f.dat", temperature);

  fout = fopen("transition_count.dat", "w");

  for (int i = 0; i < 500; i++)
  {
    temperature += 0.01;
    factor = sqrt((3 * 2 * temperature) / delta_t);
    int transition_count;

    x = -4.0; // 初期位置は左の谷の近く -4.0 に固定
    for (step = 0; step <= TOTAL_STEP; step++)
    {
      // if (step % SAVE_STEP == 0)
      // {
      //   // printf("%9d %10.3f\n", step, x);
      //   fprintf(fout, "%9d %10.3f\n", step, x);
      // }
      x += delta_t * (force(x) + fr(factor)) / gamma;

      if (x * prev_x < 0)
      {
        if (prev_x < 0)
        {
          transition_count++;
        }
      }
      prev_x = x;
    }
    fprintf(fout, "%.9f %d\n", 1 / temperature, transition_count);
  }
  fclose(fout);
  return 0;
}