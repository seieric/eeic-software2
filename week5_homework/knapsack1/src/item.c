#include "item.h"

#include <stdio.h>
#include <stdlib.h>

// 以下は構造体定義

// 構造体 Item
// 価値valueと重さweightが格納されている
struct item {
    double value;
    double weight;
};

// 構造体 Item
// 価値valueと重さweightが格納されている
// Itemポインタをmallocする必要あり
struct itemset {
    size_t number;
    Item *item;
};

// 構造体をポインタで確保するお作法を確認してみよう
Itemset *init_itemset(size_t number, int seed) {
    Itemset *list = (Itemset *)malloc(sizeof(Itemset));

    Item *item = (Item *)malloc(sizeof(Item) * number);

    srand(seed);
    for (int i = 0; i < number; i++) {
        item[i].value = 0.25 * (rand() % 200);
        item[i].weight = 0.25 * (rand() % 200 + 1);
    }
    *list = (Itemset){.number = number, .item = item};
    return list;
}

// itemset の free関数
void free_itemset(Itemset *list) {
    free(list->item);
    free(list);
}

// 表示関数
void print_itemset(const Itemset *list) {
    size_t n = list->number;
    const char *format = "v[%d] = %4.1f, w[%d] = %4.1f\n";
    for (int i = 0; i < n; i++) {
        Item *item = get_item(list, i);
        printf(format, i, get_itemvalue(item), i, get_itemweight(item));
    }
    printf("----\n");
}

Item *get_item(const Itemset *list, size_t index) {
    return &(list->item[index]);
}

size_t get_nitem(const Itemset *list) { return list->number; }

double get_itemweight(const Item *item) { return item->weight; }

double get_itemvalue(const Item *item) { return item->value; }

Itemset *load_itemset(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "error: unable to open data file\n");
        exit(1);
    }

    size_t nitem;
    if (fread(&nitem, sizeof(size_t), 1, fp) != 1) {
        fprintf(stderr, "error: unable to read number of items from file\n");
        exit(1);
    }

    double *values = (double *)malloc(sizeof(double) * nitem);
    if (fread(values, sizeof(double), nitem, fp) != nitem) {
        free(values);
        fprintf(stderr, "error: unable to read item values from file\n");
        exit(1);
    }

    double *weights = (double *)malloc(sizeof(double) * nitem);
    if (fread(values, sizeof(double), nitem, fp) != nitem) {
        free(weights);
        fprintf(stderr, "error: unable to read item weights from file\n");
    }

    Itemset *list = (Itemset *)malloc(sizeof(Itemset));
    Item *item = (Item *)malloc(sizeof(Item) * nitem);

    for (int i = 0; i < nitem; ++i) {
        item[i] = (Item){.value = values[i], .weight = weights[i]};
    }

    list->number = nitem;
    list->item = item;

    free(values);
    free(weights);
    fclose(fp);

    return list;
}

void save_itemset(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "error: unable to open target file to save\n");
        exit(1);
    }

    const size_t nitem = 100;
    Itemset *items = init_itemset(nitem, 1234);

    double *values = (double *)malloc(sizeof(double) * nitem);
    double *weights = (double *)malloc(sizeof(double) * nitem);

    for (int i = 0; i < nitem; ++i) {
        Item *item = get_item(items, i);
        values[i] = item->value;
        weights[i] = item->weight;
    }

    fwrite(&nitem, sizeof(size_t), 1, fp);
    fwrite(values, sizeof(double), nitem, fp);
    fwrite(values, sizeof(double), nitem, fp);

    free_itemset(items);
}
