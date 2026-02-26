# C++ チートシート: std::priority_queue

常に最も優先度が高い要素（デフォルトでは最大値）が先頭に来るように、要素を自動的にソートして保持するコンテナアダプタです。ヒープというデータ構造で実装されています。

---
## 基本的な使い方 (最大値を取り出す: Max Heap)

### ヘッダと宣言
`<queue>`ヘッダが必要です。デフォルトでは、最も大きい要素が先頭(`top`)に来ます。

```cpp
#include <queue>
priority_queue<要素の型> pq;
```

### 主要なメンバ関数
* `pq.push(x)`
    優先度付きキューに要素 `x` を追加します。追加後、内部で自動的に並べ替えが行われます。計算量は `O(log N)` です。

* `pq.pop()`
    先頭の要素（最も優先度が高い要素）を**削除します**。値を返さないことに注意してください。

* `pq.top()`
    先頭の要素を**参照します**（値を返します）。キューが空のときに呼び出すと未定義動作となるため、`empty()`で確認してから使います。

* `pq.size()`
    キュー内の要素数を返します。

* `pq.empty()`
    キューが空であれば `true`、そうでなければ `false` を返します。

---
## 応用: 最小値を取り出す (Min Heap)
最も小さい要素を先頭に持ってきたい場合は、宣言時に追加の引数を指定する必要があります。

```cpp
// 最小値を取り出すための宣言 (Min Heap)
priority_queue<要素の型, vector<要素の型>, greater<要素の型>> pq_min;
```greater<要素の型>` が、大小比較を逆転させるための比較関数です。

---
## 実践的なコード例

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <functional> // greater

int main() {
    // 1. 最大値を取り出す (Max Heap)
    std::priority_queue<int> pq_max;
    pq_max.push(30);
    pq_max.push(10);
    pq_max.push(50);
    pq_max.push(20);

    std::cout << "Max Heap (descending order): ";
    while (!pq_max.empty()) {
        std::cout << pq_max.top() << " "; // -> 50 30 20 10
        pq_max.pop();
    }
    std::cout << std::endl;


    // 2. 最小値を取り出す (Min Heap)
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq_min;
    pq_min.push(30);
    pq_min.push(10);
    pq_min.push(50);
    pq_min.push(20);

    std::cout << "Min Heap (ascending order): ";
    while (!pq_min.empty()) {
        std::cout << pq_min.top() << " "; // -> 10 20 30 50
        pq_min.pop();
    }
    std::cout << std::endl;

    return 0;
}
```

---
## 重要なポイント 📌
* **ヒープ構造**: 内部はヒープという木構造で実装されており、これにより `O(log N)` での要素追加と `O(1)` での先頭要素アクセスを実現しています。
* **アクセス制限**: `top()`以外でキューの途中にある要素にアクセスすることはできません。
* **用途**: ダイクストラ法による最短経路探索、シミュレーション問題でのイベント管理、貪欲法など、常に「最も大きい（小さい）もの」を処理する必要がある場面で非常に強力です。
* **ペア(pair)の格納**: `pair`を格納した場合、デフォルトでは`first`要素を第一キー、`second`要素を第二キーとして比較されます。
