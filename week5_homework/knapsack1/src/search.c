#include "search.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"

// ソルバーは search を index = 0 で呼び出すだけ
Answer solve(const Itemset *list, double capacity) {
    size_t nitem = get_nitem(list);

    // 品物を入れたかどうかを記録するフラグ配列 =>
    // !!最大の組み合わせが返ってくる訳ではない!!
    unsigned char flags[nitem];
    return search(0, list, capacity, flags, 0.0, 0.0);
}

// 再帰的な探索関数
Answer search(int index, const Itemset *list, double capacity,
              unsigned char *flags, double sum_v, double sum_w) {
    size_t max_index = get_nitem(list);
    assert(index >= 0 && sum_v >= 0 && sum_w >= 0);
    const Answer invalid = (Answer){.value = 0, .flags = NULL};  // 解なしを定義

    // 必ず再帰の停止条件を明記する (最初が望ましい)
    if (index == max_index) {
        const char *format_ok = ", total_value = %5.1f, total_weight = %5.1f\n";
        const char *format_ng =
            ", total_value = %5.1f, total_weight = %5.1f NG\n";

        bool is_not_exceed = (sum_w <= capacity);  // 重さ評価のtrue/false

        unsigned char *ans_flags =
            (is_not_exceed) ? (unsigned char *)malloc(max_index) : NULL;

        if (is_not_exceed) {
            for (int i = 0; i < max_index; i++) {
                printf("%d", flags[i]);
                ans_flags[i] = flags[i];
            }
        }

        printf((is_not_exceed) ? format_ok : format_ng, sum_v, sum_w);
        return (is_not_exceed) ? (Answer){.value = sum_v,
                                          .weight = sum_w,
                                          .flags = ans_flags}
                               : invalid;
    }

    // 以下は再帰の更新式: 現在のindex の品物を使う or 使わないで分岐し、index
    // をインクリメントして再帰的にsearch() を実行する

    // index番目を使わない場合
    flags[index] = 0;
    const Answer a0 = search(index + 1, list, capacity, flags, sum_v, sum_w);

    // index番目を使う場合
    flags[index] = 1;
    Item *item = get_item(list, index);
    sum_v += get_itemvalue(item);
    sum_w += get_itemweight(item);
    const bool is_exceed = (sum_w > capacity);
    if (is_exceed) return a0;
    const Answer a1 = search(index + 1, list, capacity, flags, sum_v, sum_w);

    // 使った場合の結果と使わなかった場合の結果を比較して返す
    if (a0.value > a1.value) {
        free(a1.flags);
        return a0;
    } else {
        free(a0.flags);
        return a1;
    }
}
