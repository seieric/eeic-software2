#pragma once
#include <stddef.h> // size_t のため必要

typedef struct item Item;
typedef struct itemset Itemset;


// Itemsetを初期化し、そのポインタを返す関数
// 乱数シードを第2引数にとる
Itemset *init_itemset(size_t number, int seed);

// Itemsetの動的確保された領域を解放する
void free_itemset(Itemset *list);

// Itemsetの内容を標準出力に表示する関数
void print_itemset(const Itemset *list);

// Itemset の当該indexのアイテムへのポインタを取得
Item *get_item(const Itemset *list, size_t index);

// Itemの個数を取得
size_t get_nitem(const Itemset *list);

// Item の Weightを取得
double get_itemweight(const Item *item);

// Item の Valueを取得
double get_itemvalue(const Item *item);

//ファイルからItemsetを設定 [未実装, 課題1] 
Itemset *load_itemset(char *filename);

//Itemsetのパラメータを記録したバイナリファイルを出力する関数 [未実装, テスト用]
void save_itemset(char *filename);

