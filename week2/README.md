# ソフトウェアII 第2回課題 ダーツ・他

## 実施した内容

以下の基本課題および発展課題に取り組んだ。

- 課題1（`struct_alignment.c`, `struct_alignment.md`）
- 課題2（`struct_compare/`）
- 課題3（`my_darts1.c`, `my_darts1.h`）
  - セパレートルールを採用して、インブル50点、アウターブル25点でスコアを計算するようにした。
  - `my_calculate_score`関数および`my_print_score`関数を実装し、Board構造体に追加したscoreを更新、表示している。
  - Pointのxy座標は、円の中心を原点とし、x軸方向を水平右方向、y軸方向を垂直下方向とするものとした。
- 課題4（`my_darts2.c`, `my_darts2.h`）
  - ユーザーの入力を元に、狙うべき位置を計算する`my_calculate_target`関数を実装した。この関数は`my_parse_type`関数と`my_parse_area`関数を用いて極座標系における狙い位置を求めたあと、直交座標系での位置を返却する。
  - ユーザーの入力がなかったり、不正であったりする場合は、ブルを狙うようにした。
  - `getopt`を利用して`-v`オプションで標準偏差を指定できるように実装した。想定されていない引数がある際には、プログラムを終了するようにした。

### 発展課題

`my_darts3.c`, `my_darts3.h`に課題4までダーツゲームに以下の機能を追加したゲームを実装した。

- 現実のダーツ盤のようにダーツ盤に色をつけて表示する。
  - 領域ごとに色を交互に塗るようにした。
  - 矢が刺さった位置は、目立つよう黄色背景で表示。
- 複数人(1人～4人)でのプレイ・複数ラウンド(1～15ラウンド)のプレイ。
　- プレイヤー数とラウンド数は、コマンドライン引数`-n`と`-r`で指定。不正な値はエラーを表示して終了する。
- ラウンド別・プレイヤー別のスコア表示。
  - 合計得点も表示する。
  - 「カウントアップ」ゲームをベースに、得点はシンプルに積算するルールにした。
- プレイヤーの入力タイミングで標準偏差を決定する。
  - 狙い位置が入力されるまでの時間を計測し、その時間をもとに標準偏差を決定している。
  - 標準偏差はlogスケールで増加するようにし、時間が経ちすぎたときに大きくなりすぎないようにした。
  - ただし、`-v`オプションで標準偏差が指定されたときは、指定値を利用する。
- コマンドライン引数`-h`でヘルプを表示。
- 現実のダーツにあるようなプレイヤー交代時のアクション（`Enter`キーを押して次のプレイヤーに交代）。

## 参考にしたサイト

### 実装

- https://marycore.jp/prog/c-lang/convert-number-to-char/
- https://hiroyukichishiro.com/scanf-problems-in-c-language/
- https://qiita.com/tobira-code/items/24e583c30f07c4853f8f
- https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
- https://daeudaeu.com/c-printf-color/
- https://www.delftstack.com/ja/howto/c/gettimeofday-in-c/

### ダーツのルール等

- https://bar-ryuk.com/archives/802
- https://darts.kit-work.com/rule/count.html
- https://www.darts-atlas.com/2020/10/rule/
- https://nayo-darts.com/countup
