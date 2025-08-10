# C++ チートシート: Union-Find (DSU)

**AtCoder Library** に含まれる `dsu` 構造体を使ったUnion-Findの実装です。グループ分け（互いに素な集合の管理）を高速に行うことができます。

---
## 基本的な使い方

### ヘッダと宣言
`atcoder/all` をインクルードし、`atcoder` 名前空間を使います。

```cpp
#include <atcoder/all>
using namespace atcoder;

// 頂点数Nで初期化
int N = 10;
dsu uf(N); // 0からN-1までのN個の要素が、それぞれ別のグループとして初期化される
```
**注意**: **0-indexed** です。頂点番号は `0` から `N-1` までとなります。

### 主要なメンバ関数

* `uf.merge(u, v)`
    頂点 `u` と頂点 `v` が属するグループを1つに統合（併合）します。すでに同じグループにいる場合は何も起こりません。計算量はほぼ定数時間 `O(α(N))` です。

* `uf.same(u, v)`
    頂点 `u` と頂点 `v` が同じグループに属しているかを判定します。同じなら `true`、違うなら `false` を返します。

* `uf.leader(u)`
    頂点 `u` が属するグループの代表元（リーダー）を返します。

* `uf.size(u)`
    頂点 `u` が属するグループの要素数を返します。

---
## 連結成分の数を数える
Union-Findを使ってグラフの連結成分の数を数えるのは典型的なテクニックです。

1.  最初は、全頂点がバラバラなので、連結成分の数は頂点数 `N` と同じです。
2.  まだ連結されていない2つの頂点 `u`, `v` を `merge` するたびに、グループが1つ減るので、連結成分の数を1つ減らします。

```cpp
int N; // 頂点数
// ...
dsu uf(N);
int connected_components = N; // 初期状態

for (/* 各辺 (u, v) について */) {
    if (!uf.same(u, v)) {
        uf.merge(u, v);
        connected_components--;
    }
}
```uf.groups().size()` を使っても連結成分の数を取得できますが、`merge`のたびに数を更新する方が効率的な場合があります。

---
## 実践的なコード例

```cpp
#include <iostream>
#include <atcoder/all>
#include <vector>

using namespace std;
using namespace atcoder;

int main() {
    int N = 7; // 頂点0から6
    dsu uf(N);

    // グループを統合
    uf.merge(0, 1);
    uf.merge(1, 2); // これで {0, 1, 2} が同じグループに
    
    uf.merge(3, 4);

    // 連結判定
    if (uf.same(0, 2)) {
        cout << "0 and 2 are in the same group." << endl;
    }
    if (!uf.same(0, 3)) {
        cout << "0 and 3 are in different groups." << endl;
    }

    // グループのサイズとリーダーを確認
    cout << "Size of group containing 0: " << uf.size(0) << endl; // -> 3
    cout << "Leader of group containing 4: " << uf.leader(4) << endl;

    // 連結成分のリストを取得
    // groups()は {{0,1,2}, {3,4}, {5}, {6}} のようなリストを返す
    cout << "Number of connected components: " << uf.groups().size() << endl; // -> 4

    return 0;
}
```

---
## 重要なポイント 📌
* **用途**: グラフが連結かどうかの判定、辺を追加しながら連結成分の数を管理する、クラスカル法で最小全域木を求める、などに応用できます。
* **計算量**: `merge`, `same`, `leader` などの操作は、経路圧縮とサイズによるマージの最適化により、非常に高速（アッカーマン関数の逆関数 `α(N)` に比例する時間）です。実質的に定数時間と考えて問題ありません。
