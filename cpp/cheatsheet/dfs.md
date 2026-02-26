# C++ チートシート: DFS (深さ優先探索) - 再帰編

スタックの代わりに再帰関数呼び出しを利用して、深さ優先探索を実装する方法です。「行けるところまで進み、行き止まりになったら一つ前に戻って別の道を探す」という動きを直感的にコードに落とし込めます。

---
## アルゴリズムの考え方

再帰DFSは、以下の要素からなる関数を定義することで実装します。

1.  **基底ケース (Base Case)**: 再帰を終了する条件です。
    * 例: ゴールに到達した、これ以上進める隣接頂点がない、など。

2.  **再帰ステップ (Recursive Step)**: 各頂点で行う処理です。
    a. 現在いる頂点 `v` を「訪問済み」にする。
    b. `v` に関連する処理を行う（例: グローバルな答えを更新する、状態を記録する）。
    c. `v` に隣接する頂点 `to` のうち、まだ訪問していない頂点に対して、再帰的に自分自身（DFS関数）を呼び出す。

---
## 実装例1: 全ての単純パスを探索する (最長経路問題)
全ての頂点を始点として、全ての単純パス（同じ頂点を2度通らないパス）を探索し、最長のものを見つける問題です。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
    ll N, M;
    cin >> N >> M;
    vector<vector<pair<ll, ll>>> g(N);
    for (int i = 0; i < M; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    ll ans = 0;

    // auto self を引数に取ることで、ラムダ式内部で自分自身を再帰呼び出しできる
    auto dfs = [&](auto self, ll v, vector<bool> visited, ll dist) -> void {
        // 訪問済みにする
        visited[v] = true;
        // 現時点の距離で答えを更新
        ans = max(ans, dist);

        // 隣接頂点を探索
        for (auto [to, c] : g[v]) {
            if (visited[to]) continue; // 訪問済みならスキップ
            // 距離を更新して再帰呼び出し
            self(self, to, visited, dist + c);
        }
    };

    // 全ての頂点を始点としてDFSを開始
    for (int i = 0; i < N; ++i) {
        dfs(dfs, i, vector<bool>(N, false), 0);
    }

    cout << ans << endl;
    return 0;
}
```
**ポイント**:
* 各始点ごとに独立した探索を行うため、`dfs`を呼び出すたびに新しい`visited`配列を用意しています。
* `visited`を値渡しすることで、あるパスの探索が別のパスに影響を与えないようにしています（簡易的なバックトラック）。

---
## 実装例2: 始点から終点へのパスを探索する (XOR和問題)
始点`0`から終点`N-1`までの全ての単純パスを探索し、条件を満たすもの（この場合はXOR和が最小）を見つける問題です。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
    ll N, M;
    cin >> N >> M;
    vector<vector<pair<ll, ll>>> g(N);
    for (int i = 0; i < M; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    ll ans = 2e18; // 非常に大きい値で初期化

    auto dfs = [&](auto self, ll v, vector<bool> visited, ll current_xor) -> void {
        visited[v] = true;

        // 基底ケース: ゴールに到達
        if (v == N - 1) {
            ans = min(ans, current_xor);
            return;
        }

        // 再帰ステップ
        for (auto [to, w] : g[v]) {
            if (visited[to]) continue;
            self(self, to, visited, current_xor ^ w);
        }
    };

    // 始点0から探索開始
    dfs(dfs, 0, vector<bool>(N, false), 0);

    cout << ans << endl;
    return 0;
}
```
**ポイント**:
* `v == N-1` という明確な基底ケースが存在します。
* `current_xor ^ w` のように、パスの状態を引数で引き継いでいきます。

---
## 重要なポイント 📌
* **`visited`配列**: グラフに閉路がある場合に無限ループに陥るのを防ぐために必須です。
* **ラムダ式の再帰**: `auto dfs = [&](auto self, ...)` という形式は、C++17以降で使える便利な再帰ラムダの書き方です。
* **バックトラック**: より効率的な実装では、`visited`配列を参照渡し(`&`)にし、再帰呼び出しの後に `visited[v] = false;` と状態を戻す「手動バックトラック」を行うことがあります。これにより、`vector`のコピーコストを削減できます。
