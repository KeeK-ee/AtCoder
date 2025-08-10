# C++ チートシート: std::set

重複する要素を許さず、自動的に要素を昇順にソートして保持するコンテナです。

---
## 基本的な操作

### ヘッダと宣言
```cpp
#include <set>
set<要素の型> s;
```

### 要素の追加: `insert`
* `s.insert(x)`:
    セットに要素 `x` を追加します。すでに `x` が存在する場合は、何も起こりません。計算量は `O(log N)` です。

### 要素の削除: `erase`
* `s.erase(x)`:
    セットから要素 `x` を削除します。計算量は `O(log N)` です。

### 要素の存在チェック
`find` を使う方法と `count` を使う方法があります。`count` の方がシンプルで推奨されます。

* `s.count(x)`:
    要素 `x` が存在すれば `1`、存在しなければ `0` を返します。`if (s.count(x))` の形で使うのが一般的です。

* `s.find(x) != s.end()`:
    `find` は要素 `x` を探し、見つかればその要素を指すイテレータを、見つからなければ `s.end()` を返します。これを利用して存在チェックができます。

### サイズと状態
* `s.size()`: 要素数を返します。
* `s.empty()`: セットが空なら `true`、そうでなければ `false` を返します。

---
## ループ処理
範囲for文を使うと、ソートされた状態で全要素に簡単にアクセスできます。

```cpp
// s の全要素を小さい順に出力
for (auto element : s) {
    std::cout << element << " ";
}
```

---
## 実践的なコード例

```cpp
#include <iostream>
#include <set>
#include <vector>

int main() {
    std::set<int> s;

    // 要素の追加
    s.insert(10);
    s.insert(30);
    s.insert(20);
    s.insert(10); // 重複する10は無視される

    // 全要素を出力（自動でソートされている）
    std::cout << "Elements in set: ";
    for (int val : s) {
        std::cout << val << " "; // -> 10 20 30
    }
    std::cout << std::endl;

    // サイズ確認
    std::cout << "Size: " << s.size() << std::endl; // -> 3

    // 存在チェック
    if (s.count(20)) {
        std::cout << "20 is in the set." << std::endl;
    }
    if (!s.count(40)) {
        std::cout << "40 is not in the set." << std::endl;
    }

    // 要素の削除
    s.erase(20);
    std::cout << "After erasing 20, elements are: ";
    for (int val : s) {
        std::cout << val << " "; // -> 10 30
    }
    std::cout << std::endl;

    return 0;
}
```

---
## 重要なポイント 📌
* **ユニーク**: 同じ値の要素を複数保持することはできません。
* **自動ソート**: 要素は常に追加された時点で昇順にソートされます。
* **高速な検索**: 特定の要素が存在するかどうかのチェックが `O(log N)` で非常に高速です。
* **`unordered_set`との違い**: ソートが不要で、より高速な追加・削除・検索（平均`O(1)`）を求める場合は `std::unordered_set` を検討します。
