#include <stdio.h>
#include <stdlib.h>

void permutation(int *pattern, int *used, size_t number);

int main(int argc, char **argv) {
    size_t number = 7;

    int *pattern = (int *)calloc(number, sizeof(int));
    int *used = (int *)calloc(number, sizeof(int));

    for (int i = 0; i < number; i++) {
        // まだパターンが確定してないことのフラグを立てておく
        pattern[i] = -1;
    }

    permutation(pattern, used, number);

    free(used);
    free(pattern);

    return 0;
}

void permutation(int *pattern, int *used, size_t number) {
    int start = -1;

    // patternをfor文で確認し，未確定の最初のインデックスをstartに入れる

    /* ここにコードをかく */

    // パターンが確定した場合（再帰の終端）
    if (start == -1) {
        printf("[ ");
        for (int i = 0; i < number; i++) {
            printf("%d ", pattern[i]);
        }
        printf("]\n");
        return;
    }

    // パターンが確定してない場合の処理をを以下にかく
    // used と pattern を更新しながらpermutationを呼び出す

    /* ここにコードをかく */

    // 終了
    return;
}
