#include "solve.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "city.h"
#include "map.h"

// ランダムに生成する初期解の個数
#define NUM_INIT_ANS 50

double solve(const City *city, int n, int *route) {
    // 複数の初期解に対して探索を行う
    double best_sum_d = INFINITY;
    // 解の保存場所
    int *final_route = (int *)malloc(sizeof(int) * n);
    for (int a_id = 0; a_id < NUM_INIT_ANS; ++a_id) {
        route[0] = 0;  // 循環した結果を避けるため、常に0番目からスタート
        for (int i = 0; i < n; i++) {
            route[i] = i;
        }

        // ランダムに並べ替える
        for (int i = 0; i < n; ++i) {
            const int a = rand() % (n - 1) + 1;
            const int b = rand() % (n - 1) + 1;
            const int tmp = route[a];
            route[a] = route[b];
            route[b] = tmp;
        }

        // 局所解を探索
        double sum_d = search(city, n, route);
        printf("trial #%02d: total distance = %f\n", a_id, sum_d);
        if (sum_d < best_sum_d) {
            best_sum_d = sum_d;
            memcpy(final_route, route, sizeof(int) * n);
        }
    }

    memcpy(route, final_route, sizeof(int) * n);
    free(final_route);

    return best_sum_d;
}

double search(const City *city, int n, int *route) {
    // 近傍にある解の最小距離
    double next_sum_d = INFINITY;
    int next[2] = {0, 0};
    // 近傍を探索（ここでは2箇所入れ替えたもの）
    for (int i = 1; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // 逆向きの解を阻止するため2つの町の登場順を固定する
            if (i == 1 && j >= 2) break;
            if (j == 2 && i <= 1) continue;
            // 2箇所入れ替えてみる
            int tmp = route[i];
            route[i] = route[j];
            route[j] = tmp;

            double sum_d = 0;
            for (int i = 0; i < n; i++) {
                const int c0 = route[i];
                const int c1 = route[(i + 1) % n];  // nは0に戻る
                sum_d += distance(get_city(city, c0), get_city(city, c1));
            }

            if (sum_d < next_sum_d) {
                next[0] = i;
                next[1] = j;
                next_sum_d = sum_d;
            }

            // 元に戻す
            tmp = route[i];
            route[i] = route[j];
            route[j] = tmp;
        }
    }

    // もともと与えられた解のトータルの巡回距離を計算する
    double best_sum_d = 0;
    for (int i = 0; i < n; i++) {
        const int c0 = route[i];
        const int c1 = route[(i + 1) % n];  // nは0に戻る
        best_sum_d += distance(get_city(city, c0), get_city(city, c1));
    }

    // もともと与えられた解より近傍で見つけた解のほうが良い場合はさらに探索する
    if (next_sum_d < best_sum_d) {
        int tmp = route[next[0]];
        route[next[0]] = route[next[1]];
        route[next[1]] = tmp;
        return search(city, n, route);
    }

    return best_sum_d;
}