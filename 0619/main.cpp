#include <stdio.h>
#include <math.h>

#define DFILE "StyleOfPollock2021_large" // 入力用画像ファイル名（拡張子 .bmp は自動的に付加）
#define DMAX 65536                       // Maximum header size
#define IMAX 4800                        // Maximum image size

int Width, Height;
int Image[IMAX][IMAX];
int Threshold;

int read_image(char *INPUT_FILE) //=====================================================
{
  FILE *fin;
  unsigned char cdata[DMAX];
  unsigned int Offset, HeaderSize;
  unsigned short int NBit, NByte, dummy;
  unsigned int Cmprs;
  unsigned int idata;
  int x, y, xmax, r, g, b;

  fin = fopen(INPUT_FILE, "rb");
  if (fin == NULL)
  {
    printf("Error: no input file: %s\n", INPUT_FILE);
    return -1;
  }
  printf("Analyzing %s\n", INPUT_FILE);

  // Bitmap File Header             画像ファイルのヘッダ情報を調べる
  fread(cdata, 10, 1, fin);
  printf("File Type = %c%c\n", cdata[0], cdata[1]);
  if (cdata[0] != 'B' || cdata[1] != 'M')
  {
    printf("Error: file is not BMP\n");
    fclose(fin);
    return -1;
  }
  fread(&Offset, 4, 1, fin);

  // Bitmap Info Header
  fread(&HeaderSize, 4, 1, fin);
  printf("Header Size = %d byte\n", HeaderSize);
  printf("Offset = %d byte\n", Offset);
  fread(&Width, 4, 1, fin);
  fread(&Height, 4, 1, fin);
  fread(&dummy, 2, 1, fin);
  fread(&NBit, 2, 1, fin);
  fread(&Cmprs, 4, 1, fin);
  printf("Image Size = %d X %d\n", Width, Height);
  printf("Image = %2d bit/pixel\n", NBit);
  NByte = NBit / 8;
  printf("Compress Mode = %d\n", Cmprs);
  if (Cmprs != 0)
  { // このプログラムは無圧縮 bitmap (Mode=0) のみに対応している
    printf("Sorry, this program does not support this compression type\n");
    fclose(fin);
    return -1;
  }
  if (NBit <= 4)
  {
    printf("Sorry, this program does not support this Pixel Bit type\n");
    return -1;
  }
  if ((Width > IMAX) || (Height > IMAX))
  {
    printf("Sorry, the image is too large\n");
    fclose(fin);
    return -1;
  }
  fclose(fin);

  //   return 9;   // For Debugging

  fin = fopen(INPUT_FILE, "rb"); // 画像ファイルを開き直して，画像データを読み込む
  fread(cdata, Offset, 1, fin);

  // Read Image
  for (y = 0; y < Height; y++)
  {
    for (x = 0; x < Width; x++)
    {
      idata = (unsigned int)0;
      int status = fread(&idata, NByte, 1, fin); // ピクセルデータ読み込み
      if (status != 1)
      {
        printf("Error at %d %d: data end while reading\n", x, y);
        return -1;
      }
      b = idata % 256;
      idata /= 256; // NByteの画素データをrgb値に変換
      g = idata % 256;
      idata /= 256;
      r = idata;
      // printf("%5d %5d | %3d %3d %3d\n",x,y,r,g,b);
      if (r + g + b < 3 * Threshold)
      {
        Image[y][x] = 0;
      } // Threshold で２値化
      else
      {
        Image[y][x] = 1;
      }
    }
    xmax = (Width * NByte) % 4;
    for (x = 0; x < xmax; x++)
      fread(&idata, 1, 1, fin);
    // 水平方向のバイト数が4の倍数でない場合は，0x0 で埋められているので読み飛ばす
  }

  fclose(fin);
  return 0;
}

int fractal() //=============================
{
  int x, y, xtile, ytile;
  int resolution; // Tile Size
  int sum;        // Number of Tiles
  int res_max;
  bool exists_black_bit = false;
  char cname[100];
  FILE *fout;

  sprintf(cname, "%s_%3.3d.dat", DFILE, Threshold); // 出力用ファイル名
  fout = fopen(cname, "w");

  if (Height < Width)
    res_max = Height / 2; // タイルの最大サイズを設定
  else
    res_max = Width / 2;

  for (resolution = 1; resolution <= res_max; resolution *= 2)
  {          // タイルサイズを２倍ずつ大きくする
    sum = 0; // 「条件」に合致するタイルの枚数 sum を初期化

    // --------------------------------------------------------------------
    for (ytile = 0; ytile < Height / resolution; ytile++)
    {
      for (xtile = 0; xtile < Width / resolution; xtile++)
      {
        exists_black_bit = false;
        for (int j = ytile * resolution; j < ((ytile + 1) * resolution) && !exists_black_bit; j++)
        {
          for (int i = xtile * resolution; i < ((xtile + 1) * resolution) && !exists_black_bit; i++)
          {
            if (Image[j][i] == 0)
            {
              sum++;
              exists_black_bit = true;
            }
          }
        }
      }
    }
    // --------------------------------------------------------------------

    fprintf(fout, "%5d %10d\n", resolution, sum); // タイルの枚数を出力
    printf("%5d %10d\n", resolution, sum);
  }

  fclose(fout);
  return 0;
}

int main() //=================================================
{
  int ret;
  char cfile[100];
  FILE *fout;

  printf("Input Threshold (<=255):"); // この値以下を「黒」と判定する
  scanf("%d", &Threshold);

  sprintf(cfile, "%s.bmp", DFILE);
  ret = read_image(cfile);
  if (ret != 0)
    return -1;

  fractal();

  return 0;
}