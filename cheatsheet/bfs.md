# C++ チートシート: BFS (幅優先探索)

キュー（Queue）を使い、スタート地点から近い順に探索範囲を広げていくアルゴリズムです。重みなしグラフ（すべての辺のコストが同じグラフ）における**最短経路**を求めるのに使われます。

---
## アルゴリズムの考え方

1.  **準備**:
    * 探索する頂点を入れるためのキュー `q` を用意する。
    * 各頂点へのスタートからの最短距離を記録する配列 `dist` を用意し、全要素を未訪問の印（例: `-1`）で初期化する。

2.  **初期化**:
    * スタート頂点 `s` をキュー `q` に入れる (`q.push(s)`)。
    * スタート頂点の距離を `0` に設定する (`dist[s] = 0`)。

3.  **探索ループ**:
    * キュー `q` が空になるまで、以下の処理を繰り返す。
        a. キューの先頭から頂点 `u` を取り出す (`u = q.front(); q.pop();`)。
        b. `u` に隣接するすべての頂点 `v` について、以下を調べる。
            i. もし `v` が未訪問 (`dist[v] == -1`) ならば:
                - `v` を訪問済みにする (`dist[v] = dist[u] + 1`)。
                - `v` をキュー `q` に追加する (`q.push(v)`)。

---
## 実装例 (グリッド上の最短経路)
あなたのコードは、このアルゴリズムをグリッド上で見事に実装したものです。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// 4方向への移動ベクトル (右, 下, 左, 上)
const vector<int> dx = {1, 0, -1, 0};
const vector<int> dy = {0, 1, 0, -1};

// 計算量: O(R*C) (R:行数, C:列数)
int main() {
    int R, C;
    cin >> R >> C;
    int sy, sx, gy, gx;
    cin >> sy >> sx >> gy >> gx;
    sy--, sx--, gy--, gx--; // 0-indexedに変換

    vector<string> grid(R);
    for (int i = 0; i < R; ++i) cin >> grid[i];

    // 1-a. 探索キュー
    queue<pair<int, int>> q;
    // 1-b. 距離を記録する2次元配列 (-1は未訪問)
    vector<vector<int>> dist(R, vector<int>(C, -1));

    // 2. 初期化
    q.push({sy, sx});
    dist[sy][sx] = 0;

    // 3. 探索ループ
    while (!q.empty()) {
        auto [y, x] = q.front(); // 3-a. 現在地を取り出す
        q.pop();

        // 3-b. 隣接マスを調べる
        for (int dir = 0; dir < 4; ++dir) {
            int ny = y + dy[dir];
            int nx = x + dx[dir];

            // 範囲外チェック
            if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
            // 壁チェック
            if (grid[ny][nx] == '#') continue;
            // 3-b-i. 訪問済みチェック
            if (dist[ny][nx] != -1) continue;

            // 訪問処理
            dist[ny][nx] = dist[y][x] + 1;
            q.push({ny, nx});
        }
    }

    // ゴールまでの最短距離を出力
    cout << dist[gy][gx] << endl;

    return 0;
}
```

---
## 重要なポイント 📌
* **キュー (FIFO)**: BFSでは「先入れ先出し」のキューを使うことで、スタートから近い順（距離1の点、距離2の点…）に探索を進めることができます。これが最短経路を保証する理由です。
* **`dist`配列の役割**:
    1.  スタートからの最短距離を記録する。
    2.  一度訪れた頂点を再度キューに入れないようにする「訪問済み」の目印となる。これにより、無限ループを防ぎ、計算量を `O(頂点数 + 辺数)` に抑えます。
* **応用**: 迷路の最短路、連結成分の判定、二部グラフ判定など、多くの問題に応用できます。
