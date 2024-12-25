# ソフトウェアII 第3回課題 ペイントソフト

## 実施した内容

以下の基本課題および発展課題に取り組んだ。

- 課題1（`paint1.c`, `paint1.h`）
- 課題2（`paint2.c`, `paint2.h`）
  - 履歴ファイルが存在しない場合や読み込めない場合と、正しく読み込めた場合で異なるメッセージを表示するようにした。
  - `paint2.txt`には、幅60、高さ30のキャンバスで簡単な顔を描写した際の履歴が入っている。
- 課題3（`paint3.c`, `paint3.h`）
  - 最初の履歴に`chpen *`を自動で追加して`undo`時の整合性を保つとともに、最初の履歴が`undo`されないようにした。

### 課題4（発展課題）（`paint4.c`, `paint4.h`）

基本課題のペイントソフトに、以下のコマンドを追加した。

- 描画機能
  - `fill <x> <y>`：指定した座標と周囲の文字が同じ場合、描画文字で塗りつぶす。
    - [Span filling](https://en.wikipedia.org/wiki/Flood_fill#Span_filling)アルゴリズムを実装した。- 指定した座標の文字と同じ文字の接続領域を塗りつぶす。
    - 指定座標が範囲外の場合はエラーメッセージを表示する。
- 保存機能
  - `savebmp <filename>`：ペイントを**BMPファイル**に保存する。ファイル名が指定されていない場合は、`your_paint.bmp`として保存する。
    - 空白文字を白、それ以外の文字を黒として書き出す。
    - BMPファイルの情報ヘッダの形式にはINFOタイプを使用。ビット数は1ビットの白黒画像として保存。非圧縮。
    - `paint2.txt`を書き出したサンプルを`paint2.bmp`として同梱している。
  - `savetxt <filename>`：ペイントを**テキストファイル**に保存する。ファイル名が指定されていない場合は、`your_paint.txt`として保存する。
  - `save <filename>`：（課題配布時の実装）現在までの**履歴**を指定したファイル名で保存する。
- コピー（カット）＆ペースト機能
  - `copy <x> <y> <rect_width> <rect_height>`：指定した矩形範囲（左上頂点、横幅、縦幅）をコピーする。既にコピー（切り取り）されたデータは上書きされる。
    - 左上頂点が範囲外の場合はエラーメッセージを表示するが、矩形範囲が範囲外にはみ出てしまう場合は自動で範囲を調整してコピーする。
  - `cut <x> <y> <rect_width> <rect_height>`：指定した矩形範囲を切り取る。既に切り取り（コピー）されたデータは上書きされる。
  - `paste <x> <y>`：指定した座標を左上の頂点としてコピーしたデータを貼り付ける。連続して繰り返しペーストできる。
    - コピーされたデータがない場合はエラーメッセージを表示する。
  - なお、コピー対象のデータのサイズに応じて動的にメモリを確保、開放するようにしている。
  - また、これらのコマンドは履歴として保存される。
- 履歴機能
  - `redo`：`undo`で取り消した操作を再実行する。`undo`が複数回連続で実行された場合、`redo`も同様に複数回連続して実行できる。
  　- `History`構造体を双方向リストに変更し、`undo`された際に履歴上で現在の位置を保持するようにした。
  - `save <filename>`：現在までのを指定したファイル名で保存する。配布時の実装を変更し、`redo`された履歴は含めず、現在位置までの履歴を保存するようにした。

## 参考にしたサイト

- https://en.wikipedia.org/wiki/Flood_fill
- https://qiita.com/zaru/items/29ea3c76b66eb1c1ac8b
- https://stackoverflow.com/questions/56317418/malloc-corrupted-top-size
- https://www.setsuki.com/hsp/ext/bmp.htm
- https://megumish.hatenablog.com/entry/2016/05/30/002847
- https://ruche-home.net/program/bmp/struct#image-data
- https://learn.microsoft.com/ja-jp/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
- https://monozukuri-c.com/langc-funclist-binaryfile/
- https://af-e.net/c-language-pragma-pack/
- https://eeic-software1.github.io/2024/week6/
