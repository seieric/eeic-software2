# ソフトウェアII 第4回課題

## 実施した内容

以下の基本課題および発展課題に取り組んだ。

- 課題1（`paint/`）
  - 授業内と同じ方法でディレクトリを整理して、Makefileも作成した。
　- 履歴部分の実装をライブラリ化して、線形リストによる実装と配列による実装のいずれでも同じmain関数でコンパイルできるようにした。
    - `make`で線形リストのライブラリでコンパイルされ、`bin/paintapp`に実行ファイルが生成される。
    - `make array`で配列のライブラリでコンパイルされ、`bin/paintapp_array`に実行ファイルが生成される。
- 課題2（`mtfuji/`）
  - 授業内と同じ方法でディレクトリを整理して、Makefileも作成した。
  - `bin/mtfuji data.csv`で標高と気温のデータを読み込み、最小二乗法によってy=ax+bのaとbを求め、富士山頂の気温が推定される。
    - 推定結果は、3.984981℃であった。
  - プログラムの出力結果の冒頭にテーブル形式で、標高に基づいてソートしたデータが表示される。

### 課題3（発展課題）（`adv/｀）

ニューラルネットワークを用いて、入学試験の合否を予測する回帰プログラムを作成した。

#### プログラムの概要

- 実行方法
  - `make`でコンパイルし、`bin/nn data/student_admission_record_dirty.csv`で実行する。
  - 冒頭にデータの中身、初期状態の重みが表示され、その後、各エポックでの損失、学習された重み、テストデータに対する推論結果が表示される。
- ニューラルネットワークの構造
  - 入力層：4ノード
  - 中間層：3ノード
    - 活性化関数：ReLU
  - 出力層：1ノード（合否の確率）
    - 活性化関数：Sigmoid
  - 重みの数（パラメータ数）：4x3 + 3x1 = 15
- 目的関数：交差エントロピー誤差
- データ：[Student Admission Records](https://www.kaggle.com/datasets/zeeshier/student-admission-records)
  - Kaggleからダウンロードしたデータを`adv/data/student_admission_record_dirty.csv`に同梱している。
  - 年齢、性別、試験の点数、高校の成績、合否の項目のみを利用している。
    - これらの項目が欠損している行は読み込み時に除外する仕組みになっている。

#### 実装の詳細

- ニューラルネットワークに必要となる機能を複数分割して実装した。
  - 行列構造体・行列の演算：`adv/matrix.h`・`adv/matrix.c`
    - `Matrix`構造体のメンバー変数はポインタで隠蔽して、すべての操作は関数で行うようにしている。
  - 活性化関数：`adv/activation.h`・`adv/activation.c`
  - 目的関数（損失関数）：`adv/criterion.h`・`adv/criterion.c`
  - データの読み込み：`adv/data.h`・`adv/data.c`
  - 訓練・推論：`adv/net.h`・`adv/net.c`
    - エポック・バッチのループ処理として、順伝播・逆伝播を実装している。
  - main関数：`adv/adv_regression.c`
    - データの読み込み、訓練用とテスト用データの分割、重みの初期化、学習、推論の結果を表示する。
- 重みの初期化
　- Heの初期化手法で重み行列を初期化している。
- 順伝播の実装
  - 行列積および行列への活性化関数の適用。
- 逆伝播の実装
  - 誤差逆伝播法を用いて、勾配を計算し、最急降下法によって重みを更新する。

## 参考にしたサイト

- https://route3776.jp/
- https://qiita.com/kenta1984/items/59a9ef1788e6934fd962
- https://otafuku-lab.co/aizine/cross-entropy1022/
- https://hanon05.hatenablog.com/entry/2019/01/26/001705
- https://zenn.dev/schnell/articles/579df242f79964
- https://qiita.com/SabanoMizuni/items/ab4b73cd9b8e733da11a
- https://qiita.com/yosshi4486/items/d111272edeba0984cef2
- https://toukei-lab.com/relu
- https://nisshingeppo.com/ai/relu-funcrion/
- https://www.gavo.t.u-tokyo.ac.jp/~dsk_saito/lecture/software2/resource/lecture2.html#section-8
- https://qiita.com/Fumio-eisan/items/d697fbd96347ef7e49d5