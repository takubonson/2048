# 2048
## How to play
Run 
```
gcc -o exec main.c
./exec
```
-------------------------
## プログラムの説明

### 全体説明
盤面は4*4の2次配列である、ゲームが始まると盤面が表示され（print_board関数)、入力の方向キーに従って数字が移動したり合体したり、その下にScoreが表示される。

### オリジナル要素
- 各行（列）の足し算の回数を一回までとすることで、従来の2048ゲームと比べて難易度を少しあげた

### random_in_range関数

引数rand_maxを受け取り、0以上rand_max未満の乱数を返す。
- まず任意の乱数を発生させる
- 乱数を`rand_max`で割った余り(0以上rand_max未満)を返す

### print_board関数

引数として4*4の2次配列の`board[4][4]`を受け取り、二重ループでそれぞれの要素の値を調べて、ゼロであれば空白、ゼロでなければその数字に色をつけてプリントアウトする関数である。(`_`と`|`で盤面が4×4に区切られている。)
- colorは数字の色を決める変数であり、数字の値のlog2をとり、合計6色あるので、6で割った余りで色を割り当てる。`printf("\x1b[3%dm", color);`
- printfが終わった後に色をデフォルトに戻す`printf("\x1b[39m");`

### check_if_full関数

引数として4*4の2次配列の`board[4][4]`を受け取り、二重ループで全ての要素の値をチェックし、空(=0)の要素がなければ`1`,空(=0)の要素があれば`0`を返す

### put_random_2_in関数

盤面にランダムに`2`を発生させる関数

引数として4*4の2次配列の`board[4][4]`を受け取り、もし盤面に空の要素がなければ何も入れずに終了するが、もし盤面に空の要素があれば、ランダムに位置を選んで、その位置は空でなければ選び直し、空の位置であればその位置に2を入れて(0を2と置き換えて)終了する。
- check_if_full関数で空の要素があるかどうかを調べる
- 2を入れていない間にflagの値を0とし、2を入れたらflagを1にすることで、必ず2が一つだけ入れられることが保証される。

### start_game関数

ゲームが始まる時に実行する関数である
引数として4*4の2次配列の`board[4][4]`を受け取り、盤面にランダムに`2`を2つ入れる関数
- put_random_2_inを2回実行する

### move up 関数

↑キーが押された時に実行する関数である
引数として4*4の2次配列の`board[4][4]`を受け取り、2048のゲームのように数字が上に動いて同じ数字同士が足し算して結合する。
- ここ`flag[4] = {0, 0, 0 ,0}`を入れて、それぞれの列で足し算が行われたら、その列に対応するflagの要素を1にして、その列にそれ以上足し算を行わないようにする(公式の2048のルールと異なる可能性があるが、ここでは各列（行）の足し算の回数を一回以内と定める)
- この関数で3重ループが使われている、全ての要素についてそれぞれ上にある要素と比べて、上に0(空）があれば上に移り、上に同じ値があれば上の数値と合体する。

### move_down, move_left, move_right関数
move_up関数と似ているので省略する。
