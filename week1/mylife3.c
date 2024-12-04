#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep()関数を使う
#include <string.h>
#include <time.h>
#define NUM_CELLS 2800

void my_init_cells(const int height, const int width, int cell[height][width], FILE *fp);
void my_print_cells(FILE *fp, int gen, const int height, const int width, int cell[height][width]);
void my_update_cells(const int height, const int width, int cell[height][width]);
int my_count_adjacent_cells(int h, int w, const int height, const int width, int cell[height][width]);
int get_cell_value(int h, int w, const int height, const int width, int cell[height][width]);
float get_live_rate(const int height, const int width, int cell[height][width]);
void dump_cells(int gen, const int height, const int width, int cell[height][width]);
int apply_rle_data(int *x, int *y, int num, char c, const int height, const int width, int cell[height][width]);

int main(int argc, char **argv)
{
    FILE *fp = stdout;
    const int height = 40;
    const int width = 70;

    int cell[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            cell[y][x] = 0;
        }
    }

    /* ファイルを引数にとるか、ない場合はデフォルトの初期値を使う */
    if (argc > 2)
    {
        fprintf(stderr, "usage: %s [filename for init]\n", argv[0]);
        return EXIT_FAILURE;
    }
    else if (argc == 2)
    {
        FILE *lgfile;
        if ((lgfile = fopen(argv[1], "r")) != NULL)
        {
            my_init_cells(height, width, cell, lgfile); // ファイルによる初期化
        }
        else
        {
            fprintf(stderr, "cannot open file %s\n", argv[1]);
            return EXIT_FAILURE;
        }
        fclose(lgfile);
    }
    else
    {
        my_init_cells(height, width, cell, NULL); // デフォルトの初期値を使う
    }

    my_print_cells(fp, 0, height, width, cell); // 表示する
    sleep(1);                                   // 1秒休止
    fprintf(fp, "\e[%dA", height + 3);          // height+3 の分、カーソルを上に戻す(壁2、表示部1)

    /* 世代を進める*/
    for (int gen = 1;; gen++)
    {
        my_update_cells(height, width, cell);         // セルを更新
        my_print_cells(fp, gen, height, width, cell); // 表示する
        sleep(1);                                     // 1秒休止する
        fprintf(fp, "\e[%dA", height + 3);            // height+3 の分、カーソルを上に戻す(壁2、表示部1)
        if (gen < 10000 && gen % 10 == 0)
        {
            dump_cells(gen, height, width, cell);
        }
    }

    return EXIT_SUCCESS;
}

/*
    セルを初期化する
*/
void my_init_cells(const int height, const int width, int cell[height][width], FILE *fp)
{
    if (fp == NULL)
    {
        // ランダムにする
        int num_lives = width * height * 0.1;
        srand((unsigned int)time(NULL));
        for (int i = 0; i < num_lives; ++i)
        {
            int h = rand() % height;
            int w = rand() % width;
            cell[h][w] = 1;
        }
    }
    else
    {
        char buf[1000];
        fgets(buf, 1000, fp);
        if (strcmp(buf, "#Life 1.06\n"))
        {
            // RLE形式
            int x = 0, y = 0;
            while (NULL != fgets(buf, 1000, fp))
            {
                int num, buf_pos = 0;
                char c;
                char *p = buf;
                while (*p != '\n' && *p != '#' && *p != 'x')
                {
                    if (sscanf(p, "%d%c%n", &num, &c, &buf_pos) == 2)
                    {
                        if (apply_rle_data(&x, &y, num, c, height, width, cell))
                            break;
                    }
                    else if (sscanf(p, "%c%n", &c, &buf_pos) == 1)
                    {
                        if (apply_rle_data(&x, &y, 1, c, height, width, cell))
                            break;
                    }
                    p += buf_pos;
                }
            }
        }
        else
        {
            // Life 1.06形式
            while (NULL != fgets(buf, 1000, fp))
            {
                int x, y;
                sscanf(buf, "%d %d\n", &x, &y);
                cell[y][x] = 1;
            }
        }
    }
}

/*
    セルの状態を表示する
*/
void my_print_cells(FILE *fp, int gen, const int height, const int width, int cell[height][width])
{
    printf("generation = %d, live rate = %f\n", gen, get_live_rate(height, width, cell));
    printf("+");
    for (int w = 0; w < width; ++w)
    {
        printf("-");
    }
    printf("+\n");
    for (int h = 0; h < height; ++h)
    {
        printf("|");
        for (int w = 0; w < width; ++w)
        {
            if (cell[h][w])
            {
                printf("\e[31m#\e[0m");
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("+");
    for (int w = 0; w < width; ++w)
    {
        printf("-");
    }
    printf("+\n");
}

/*
    セルの状態を更新する
*/
void my_update_cells(const int height, const int width, int cell[height][width])
{
    int tmp_cell[NUM_CELLS] = {0};

    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            int num_adjacent = my_count_adjacent_cells(h, w, height, width, cell);
            int val = cell[h][w];
            if (val)
            {
                if (num_adjacent != 2 && num_adjacent != 3)
                    val = 0;
            }
            else
            {
                if (num_adjacent == 3)
                    val = 1;
            }
            tmp_cell[width * h + w] = val;
        }
    }

    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            cell[h][w] = tmp_cell[width * h + w];
        }
    }
}

/*
    指定したセルの周囲の生存セル数を数える
*/
int my_count_adjacent_cells(int h, int w, const int height, const int width, int cell[height][width])
{
    int count = 0;
    count += get_cell_value(h - 1, w - 1, height, width, cell);
    count += get_cell_value(h - 1, w + 1, height, width, cell);
    count += get_cell_value(h - 1, w, height, width, cell);
    count += get_cell_value(h, w - 1, height, width, cell);
    count += get_cell_value(h, w + 1, height, width, cell);
    count += get_cell_value(h + 1, w - 1, height, width, cell);
    count += get_cell_value(h + 1, w, height, width, cell);
    count += get_cell_value(h + 1, w + 1, height, width, cell);
    return count;
}

/*
    セル配列から範囲外アクセスに対して安全に値を取得する
*/
int get_cell_value(int h, int w, const int height, const int width, int cell[height][width])
{
    if (h < 0 || height <= h || w < 0 || width <= w)
        return 0;
    return cell[h][w];
}

/*
    セルの生存率を計算する
*/
float get_live_rate(const int height, const int width, int cell[height][width])
{
    int count = 0;
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            if (cell[h][w])
                ++count;
        }
    }
    return count * 1.0 / (height * width);
}

/*
    セルの状態をファイルに保存する
*/
void dump_cells(int gen, const int height, const int width, int cell[height][width])
{
    char filename[20];
    sprintf(filename, "gen%04d.lif", gen);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Unable to create file to dump cells.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "#Life 1.06\n");
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            if (cell[h][w])
            {
                fprintf(fp, "%d %d\n", w, h);
            }
        }
    }
    fclose(fp);
}

/*
    RLE形式のデータを適用する
    終了記号!が見つかった場合は1を返し、それ以外は0を返す
*/
int apply_rle_data(int *x, int *y, int num, char c, const int height, const int width, int cell[height][width])
{
    for (int i = 0; i < num; ++i)
    {
        switch (c)
        {
        case '!': // 終了
            return 1;
        case '$': // 改行
            *x = 0;
            ++*y;
            break;
        case 'o': // live
            cell[*y][*x + i] = 1;
            break;
        default:
            break;
        }
    }

    if (c != '$')
        *x += num;

    return 0;
}