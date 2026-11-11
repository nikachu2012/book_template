# book_template

LuaLaTeX（`ltjsbook`）で技術書や同人誌を組むためのテンプレートです。  
1つの原稿から、**印刷入稿用（トンボ付き）** と **電子書籍版（表紙・裏表紙付き）** の2種類のPDFを同時に出力します。

## 特徴

- B5判・本文9pt・両面レイアウト
- `latexmk` コマンド1つで紙版・電子版をまとめて生成
- 紙版はトンボ（`gentombow`）付き、電子版は表紙・裏表紙（表1・表4）を自動挿入
- アクセントカラーを用いた見出し・目次・箇条書き
- 2行構成のノンブル（2行目はページ番号の16進表記）
- キャプション付きソースコード環境・各種コールアウト（参考・警告・注意）
- 印刷を考慮したCMYKカラー定義

## 必要な環境

- **TeX Live**（LuaLaTeX, `latexmk`, `luatexja` などを含む環境）
- **フォント**（デフォルト設定）
  - ヒラギノ角ゴ ProN / ヒラギノ明朝 ProN
  - Helvetica Neue
  - Roboto Mono

> [!NOTE]  
> ヒラギノと Helvetica Neue は macOS 標準フォントです。  
> macOS 以外で使う場合は、`main.tex` のフォント設定を変更してください（原ノ味フォントを使う設定例をコメントアウトで用意しています）。

## ビルド

```sh
latexmk
```

`_temp/` に中間ファイル、`_output/` に以下のPDFが出力されます。

| ファイル | 内容 |
| --- | --- |
| `_output/_paper.pdf` | **印刷入稿用**（トンボ付き・表紙なし） |
| `_output/_digital.pdf` | **電子書籍版**（表紙・裏表紙付き） |

片方のみビルドする場合は `latexmk _paper.tex` のようにファイルを指定します。

## ファイル構成

```
.
├── .latexmkrc       # latexmk の設定（LuaLaTeX の指定や出力先など）
├── _paper.tex       # 紙版ビルドの開始ファイル（\isPaperPublishing を定義）
├── _digital.tex     # 電子版ビルドの開始ファイル
├── main.tex         # 原稿の本体（書名・著者・フォント設定・各章の読み込み）
├── mybook.sty       # スタイル定義（余白・見出し・デザインなど）
├── _preface.tex     # はじめに
├── sample.tex       # サンプル章
├── _afterword.tex   # あとがき
├── _colophon.tex    # 奥付
├── _title/          # 表紙（hyou1.pdf）と裏表紙（hyou4.pdf）
├── image/           # 本文で使う画像フォルダ
└── sourcecode/      # 外部から読み込むプログラムコードのフォルダ
```

## 使い方

### 書誌情報の設定

`main.tex` の先頭で書名や著者名を設定します。PDFのメタデータにも反映されます。

```latex
\newcommand{\mybooktitle}   {本のタイトル}
\newcommand{\mybooksubtitle}{サブタイトル}
\newcommand{\mybookauthor}  {著者名}
\newcommand{\mybookkeywords}{キーワード1, キーワード2}
```

奥付は `_colophon.tex`、表紙・裏表紙は `_title/hyou1.pdf`・`_title/hyou4.pdf` を差し替えてください。

### 章の追加

章ごとに `subfiles` を使ったファイルを作成し、`main.tex` から読み込みます。

```latex
% chapter1.tex
\documentclass[main.tex]{subfiles}
\graphicspath{{image/}}
\begin{document}
\chapter{章タイトル}
...
\end{document}
```

```latex
% main.tex
\subfile{chapter1.tex}
```

### テーマカラーの変更

配色は `mybook.sty` で定義しています。印刷を考慮し、必ずCMYKで指定してください。

| 色名 | 用途 |
| --- | --- |
| `mybookmaincolor` | 見出しや目次などのアクセントカラー |
| `mybookwarncolor` | `warn`（警告）ボックスの枠線 |
| `mybookcautioncolor` | `caution`（注意）ボックスの枠線 |

### 独自の環境・コマンド

使用例の詳細は `sample.tex` を参照してください。

```latex
% キャプション・番号付きソースコード
\begin{sourcecode}[label=lst:src]{キャプション}
int main(void) {}
\end{sourcecode}

% 枠のみのソースコード（キャプションなし）
\begin{sourcecode*}
int main(void) {}
\end{sourcecode*}

% 外部ファイルのソースコードを読み込み
\begin{codebox}
    \lstinputlisting{sourcecode/test.cpp}
\end{codebox}

% コールアウト（補足・警告・注意）
\begin{note}    ... \end{note}     % 参考
\begin{warn}    ... \end{warn}     % 警告
\begin{caution} ... \end{caution}  % 注意
\begin{simplebox} ... \end{simplebox}

% スタイル付き参照
\myref{ソースコード}{lst:src}  % → 「ソースコード1.1」
\mypageref{chapter}            % → 「ページ3」
```

### 余白の調整

`mybook.sty` 冒頭の数値で調整できます。

```latex
\def\topbottommargin{15truemm} % 上下
\def\nodomargin{25truemm}      % ノド（綴じ側）
\def\kogutimargin{15truemm}    % 小口（外側）
\newcommand{\mybookBleedSize}{3truemm} % 塗り足し
```

## 公開前チェック

入稿や頒布の前に、[CHECKLIST.md](CHECKLIST.md) で奥付や書誌情報、誤字脱字などを確認してください。

## ライセンス

[MIT License](LICENSE)
