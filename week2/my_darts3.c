#include "my_darts3.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
    Board board;
    int scores[MAX_PLAYERS][MAX_ROUNDS] = {0};

    srand((unsigned int)time(NULL));

    double stddev = 15.0;
    int num_players = 1;
    int num_rounds = 8;

    int c;
    opterr = 0;  // エラーを表示しない
    while ((c = getopt(argc, argv, "v:n:r:")) != -1) {
        if (c == 'v') {
            stddev = atof(optarg);
        } else if (c == 'n') {
            num_players = atoi(optarg);
            if (num_players < 1 || MAX_PLAYERS < num_players) {
                printf("Number of players must be between 1 and %d.\n",
                       MAX_PLAYERS);
                return 1;
            }
        } else if (c == 'r') {
            num_rounds = atoi(optarg);
            if (num_rounds < 1 || MAX_ROUNDS < num_rounds) {
                printf("Number of rounds must be between 1 and %d.\n",
                       MAX_ROUNDS);
                return 1;
            }
        } else if (c == '?') {
            printf("Unknown argument: %c\n", optopt);
            return 1;
        }
    }
    printf("stddev: %f\n", stddev);
    printf("Number of rounds: %d\n", num_rounds);
    printf("Number of players: %d\n", num_players);

    // ラウンド数ループ
    for (int r = 1; r <= num_rounds; ++r) {
        // プレイヤー数ループ
        for (int player = 0; player < num_players; ++player) {
            my_init_board(&board);
            // 3回投げる
            for (int k = 1; k <= 3; ++k) {
                char type = '_';
                int area = 0;
                system("clear");
                my_print_score(num_rounds, player, scores);
                printf("[Round %d][Player %d][%d/3] Input target: ", r, player,
                       k);
                scanf("%c", &type);
                if (type != 'B') {
                    scanf("%d", &area);
                }
                getchar();  // 改行をバッファから削除

                Point target = my_calculate_target(type, area);
                Point p = my_iso_gauss_rand(target, stddev);

                my_plot_throw(&board, p, k, r, player, scores);
                my_print_board(&board);
                printf("-------\n");
                my_print_point(p);
                if (!my_is_valid_point(&board, p)) printf(" miss!");
                printf("\n");
                sleep(1);
            }
        }
    }
    return 0;
}

void my_print_board(Board *b) {
    int height = my_get_board_height(b);
    int width = my_get_board_width(b);
    for (int i = 0; i < height; ++i) {
        int plus_count = 0;
        for (int j = 0; j < width; ++j) {
            if (b->space[i][j] == '+') {
                plus_count++;
            }

            if (b->space[i][j] != ' ') {
                printf("%c", b->space[i][j]);
            } else if (plus_count == 1 && i != 0 && i != height - 1) {
                Point p = {.x = j / 2.0 - 20, .y = i - 20};
                double r = sqrt(pow(p.x, 2) + pow(p.y, 2));
                bool is_single = false;
                if (r <= 1) {
                    // インブル（黒色）
                    printf("#");
                    continue;
                } else if (r <= 3) {
                    // 外ブル（赤）
                    printf("\e[31m#\e[0m");
                    continue;
                } else if (r <= 11) {
                    // 内シングル（白or黒）
                    is_single = true;
                } else if (r <= 13) {
                    // トリプル（赤or青）
                    is_single = false;
                } else if (r <= 18) {
                    // 外シングル（白or黒）
                    is_single = true;
                } else if (r <= 20) {
                    // ダブル（赤or青）
                    is_single = false;
                } else {
                    printf("+");
                    continue;
                }

                double theta = atan(p.y / p.x);
                bool is_large = true;
                if (theta <= -1 * PI * 0.5 / 10 * 9) {
                    is_large = true;
                } else if (theta <= -1 * PI * 0.5 / 10 * 7) {
                    is_large = false;
                } else if (theta <= -1 * PI * 0.5 / 10 * 5) {
                    is_large = true;
                } else if (theta <= -1 * PI * 0.5 / 10 * 3) {
                    is_large = false;
                } else if (theta <= -1 * PI * 0.5 / 10) {
                    is_large = true;
                } else if (theta <= PI * 0.5 / 10) {
                    is_large = false;
                } else if (theta <= PI * 0.5 / 10 * 3) {
                    is_large = true;
                } else if (theta <= PI * 0.5 / 10 * 5) {
                    is_large = false;
                } else if (theta <= PI * 0.5 / 10 * 7) {
                    is_large = true;
                } else if (theta <= PI * 0.5 / 10 * 9) {
                    is_large = false;
                }

                if (is_single) {
                    // シングルの場合
                    if (is_large) {
                        printf("\e[48;5;232m#\e[0m");  // 黒色
                    } else {
                        printf("\e[48;5;231m#\e[0m");  // 白色
                    }
                } else {
                    // ダブル・トリプルの場合
                    if (is_large) {
                        printf("\e[31;48;5;232m#\e[0m");  // 赤色
                    } else {
                        printf("\e[34;48;5;232m#\e[0m");  // 青色
                    }
                }
            } else {
                printf("%c", b->space[i][j]);
            }
        }
    }
}

size_t my_get_board_height(Board *b) {
    return sizeof(b->space) / sizeof(b->space[0]);
}

size_t my_get_board_width(Board *b) {
    return sizeof(b->space[0]) / sizeof(char);
}

void my_plot_throw(Board *b, Point p, int i, int r, int player,
                   int scores[MAX_PLAYERS][MAX_ROUNDS]) {
    if (my_is_in_board(b, p)) {
        int h = round(p.y + 20);
        int w = round(2 * (p.x + 20));
        b->space[h][w] = i + '0';
    }

    // スコアを計算し、反映する
    scores[player][r] += my_calculate_score(b, p);
}

bool my_is_in_board(Board *b, Point p) {
    // 描画範囲[-20, 20]に含まれるならtrueを返す
    if (-20 <= p.x && p.x <= 20 && -20 <= p.y && p.y <= 20) {
        return true;
    }

    return false;
}

bool my_is_valid_point(Board *b, Point p) {
    if (sqrt(pow(p.x, 2) + pow(p.y, 2)) <= RADIUS) return true;

    return false;
}

void my_init_board(Board *b) {
    int height = my_get_board_height(b);
    int width = my_get_board_width(b);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width - 2; ++j) {
            b->space[i][j] = ' ';
        }
        b->space[i][width - 2] = '\n';
        b->space[i][width - 1] = '\0';
    }

    for (int i = 0; i < height; ++i) {
        int w_center = (width - 2) / 2;
        int h_center = height / 2;
        double dx =
            w_center * sqrt((1 - pow((i - h_center) * 1.0 / h_center, 2)));
        int x1 = w_center - dx;
        int x2 = w_center + dx;
        b->space[i][x1] = '+';
        b->space[i][x2] = '+';
    }
}

Point my_iso_gauss_rand(Point mu, double stddev) {
    double u1 = rand() * 1.0 / RAND_MAX;
    double u2 = rand() * 1.0 / RAND_MAX;
    double x = sqrt(-2 * log(u1)) * cos(2 * PI * u1) * stddev + mu.x;
    double y = sqrt(-2 * log(u2)) * sin(2 * PI * u2) * stddev + mu.y;
    return (Point){.x = x, .y = y};
}

void my_print_point(Point p) { printf("(%f %f)", p.x, p.y); }

int my_calculate_score(Board *b, Point p) {
    // 範囲外のときは0点
    if (!my_is_valid_point(b, p)) return 0;

    double r = sqrt(pow(p.x, 2) + pow(p.y, 2));
    int times = 0;
    if (r <= 1) {
        // インブル
        return 50;
    } else if (r <= 3) {
        // アウターブル
        return 25;
    } else if (r <= 11) {
        // 内シングル
        times = 1;
    } else if (r <= 13) {
        // トリプル
        times = 3;
    } else if (r <= 18) {
        // 外シングル
        times = 1;
    } else if (r <= 20) {
        // ダブル
        times = 2;
    }

    double theta = atan(p.y / p.x);
    int base_score = 0;
    if (p.x >= 0) {
        // 右側にあるとき
        if (theta <= -1 * PI * 0.5 / 10) {
            base_score = 20;
        } else if (theta <= -1 * PI * 0.5 / 10 * 3) {
            base_score = 1;
        } else if (theta <= -1 * PI * 0.5 / 10 * 5) {
            base_score = 18;
        } else if (theta <= -1 * PI * 0.5 / 10 * 7) {
            base_score = 4;
        } else if (theta <= -1 * PI * 0.5 / 10 * 9) {
            base_score = 13;
        } else if (theta <= PI * 0.5 / 10) {
            base_score = 6;
        } else if (theta <= PI * 0.5 / 10 * 3) {
            base_score = 10;
        } else if (theta <= PI * 0.5 / 10 * 5) {
            base_score = 15;
        } else if (theta <= PI * 0.5 / 10 * 7) {
            base_score = 2;
        } else if (theta <= PI * 0.5 / 10 * 9) {
            base_score = 17;
        } else {
            base_score = 3;
        }
    } else {
        // 左側にあるとき
        if (theta < -1 * PI * 0.5 / 10) {
            base_score = 3;
        } else if (theta < -1 * PI * 0.5 / 10 * 3) {
            base_score = 19;
        } else if (theta < -1 * PI * 0.5 / 10 * 5) {
            base_score = 7;
        } else if (theta < -1 * PI * 0.5 / 10 * 7) {
            base_score = 16;
        } else if (theta < -1 * PI * 0.5 / 10 * 9) {
            base_score = 8;
        } else if (theta < PI * 0.5 / 10) {
            base_score = 11;
        } else if (theta < PI * 0.5 / 10 * 3) {
            base_score = 14;
        } else if (theta < PI * 0.5 / 10 * 5) {
            base_score = 9;
        } else if (theta < PI * 0.5 / 10 * 7) {
            base_score = 12;
        } else if (theta < PI * 0.5 / 10 * 9) {
            base_score = 5;
        } else {
            base_score = 20;
        }
    }

    return base_score * times;
}

void my_print_score(int num_rounds, int player,
                    int scores[MAX_PLAYERS][MAX_ROUNDS]) {
    printf("|Player|");
    for (int r = 1; r <= num_rounds; ++r) {
        printf("  %02d  |", r);
    }
    printf("Total|\n");

    printf("|");
    for (int r = 0; r <= num_rounds; ++r) {
        printf("------|");
    }
    printf("-----|\n");

    for (int i = 0; i < 4; ++i) {
        int sum = 0;
        printf("|  %02d  |", i);
        for (int r = 1; r <= num_rounds; ++r) {
            printf("%6d|", scores[i][r]);
            sum += scores[i][r];
        }
        printf("%5d|\n", sum);
    }
}

Point my_calculate_target(char type, int area) {
    double r = my_parse_type(type);
    double theta = my_parse_area(area);

    return (Point){.x = r * cos(theta), .y = r * sin(theta)};
}

double my_parse_type(char type) {
    switch (type) {
        case 'T':
            return 12;
        case 'S':
            // シングル
            double p = rand() * 1.0 / RAND_MAX;
            if (p > 0.5) {
                // 内シングル
                return 7;
            } else {
                // 外シングル
                return 15.5;
            }
        case 'D':
            // ダブル
            return 19;
        case 'B':
        default:
            // ブル
            return 0;
    }
}

double my_parse_area(int area) {
    switch (area) {
        case 6:
            return 0;
        case 10:
            return PI * 0.5 / 5 * 1;
        case 15:
            return PI * 0.5 / 5 * 2;
        case 2:
            return PI * 0.5 / 5 * 3;
        case 17:
            return PI * 0.5 / 5 * 4;
        case 3:
            return PI * 0.5;
        case 19:
            return PI * 0.5 / 5 * 6;
        case 7:
            return PI * 0.5 / 5 * 7;
        case 16:
            return PI * 0.5 / 5 * 8;
        case 8:
            return PI * 0.5 / 5 * 9;
        case 11:
            return PI;
        case 14:
            return PI * 0.5 / 5 * 11;
        case 9:
            return PI * 0.5 / 5 * 12;
        case 12:
            return PI * 0.5 / 5 * 13;
        case 5:
            return PI * 0.5 / 5 * 14;
        case 20:
            return PI * 1.5;
        case 1:
            return PI * 0.5 / 5 * 16;
        case 18:
            return PI * 0.5 / 5 * 17;
        case 4:
            return PI * 0.5 / 5 * 18;
        case 13:
            return PI * 0.5 / 5 * 19;
        default:
            // 不正な値の場合はランダムな角度を返す
            return rand() * 1.0 / RAND_MAX * 2 * PI;
    }
}
