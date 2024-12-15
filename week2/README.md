# ソフトウェアII 第2回課題 ダーツ・他

## 実施した内容

以下の基本課題に取り組んだ。発展課題には取り組んでいない。

- 課題1（`struct_alignment.c`, `struct_alignment.md`）
- 課題2（`struct_compare/`）
- 課題3（`my_darts1.c`, `my_darts1.h`）
  - セパレートルールを採用して、インブル50点、アウターブル25点でスコアを計算するようにした。
  - `my_calculate_score`関数および`my_print_score`関数を実装し、Board構造体に追加したscoreを更新、表示している。
  - Pointのxy座標は、円の中心を原点とし、x軸方向を水平右方向、y軸方向を垂直下方向とするものとした。
- 課題4（`my_darts2.c`, `my_darts2.h`）
  - ユーザーの入力を元に、狙うべき位置を計算する`my_calculate_target`関数を実装した。この関数は`my_parse_type`関数と`my_parse_area`関数を用いて極座標系における狙い位置を求めたあと、直交座標系での位置を返却する。
  - `getopt`を利用して`-v`オプションで標準偏差を指定できるように実装した。想定されていない引数がある際には、プログラムを終了するようにした。

## 参考にしたサイト

- https://marycore.jp/prog/c-lang/convert-number-to-char/
- https://darts.kit-work.com/rule/count.html
- https://bar-ryuk.com/archives/802
- https://hiroyukichishiro.com/scanf-problems-in-c-language/
- https://qiita.com/tobira-code/items/24e583c30f07c4853f8f
- https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
