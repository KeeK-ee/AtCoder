# C++ チートシート: std::set と std::multiset

## std::set
**重複する要素を許さず**、自動的に要素を昇順にソートして保持するコンテナです。

---
### 基本的な操作 (set)

#### ヘッダと宣言
```cpp
#include <set>
set<要素の型> s;
```

#### 要素の追加: `insert`
* `s.insert(x)`:
    セットに要素 `x` を追加します。すでに `x` が存在する場合は、**何も起こりません**。計算量は `O(log N)` です。

#### 要素の削除: `erase`
* `s.erase(x)`:
    セットから要素 `x` を削除します。計算量は `O(log N)` です。

#### 要素の存在チェック: `count`
* `s.count(x)`:
    要素 `x` が存在すれば `1`、存在しなければ `0` を返します。`if (s.count(x))` の形で使うのが一般的です。

#### サイズと状態
* `s.size()`: 要素数を返します。
* `s.empty()`: セットが空なら `true`、そうでなければ `false` を返します。

---
### ループ処理 (set)
範囲for文を使うと、ソートされた状態で全要素に簡単にアクセスできます。

```cpp
// s の全要素を小さい順に出力
for (auto element : s) {
    std::cout << element << " ";
}
```

---
### 重要なポイント (set) 📌
* **ユニーク**: 同じ値の要素を複数保持することはできません。
* **自動ソート**: 要素は常に追加された時点で昇順にソートされます。
* **高速な検索**: 特定の要素が存在するかどうかのチェックが `O(log N)` で非常に高速です。

---
---

## std::multiset
**重複する要素を許す**ことを除けば、`std::set`とほぼ同じ機能を持つコンテナです。自動ソート機能も備えています。

---
### 基本的な操作 (multiset)

#### ヘッダと宣言
```cpp
#include <set> // setと同じヘッダ
multiset<要素の型> ms;
```

#### 要素の追加: `insert`
* `ms.insert(x)`:
    マルチセットに要素 `x` を追加します。すでに `x` が存在する場合でも、**新たに追加されます**。

#### 要素の削除: `erase`
`erase`には2つの使い方があり、挙動が異なるため注意が必要です。

* `ms.erase(value)`:
    指定した**値 `value` と一致する全ての要素**を削除します。
* `ms.erase(iterator)`:
    指定した**イテレータ `iterator` が指す1つの要素だけ**を削除します。

#### 要素の個数チェック: `count`
* `ms.count(x)`:
    マルチセット内に要素 `x` が**いくつ存在するか**を返します。

---
### 実践的なコード例 (multiset)

```cpp
#include <iostream>
#include <set>

int main() {
    std::multiset<int> ms;

    // 要素の追加 (重複を許す)
    ms.insert(10);
    ms.insert(30);
    ms.insert(20);
    ms.insert(10); // 2つ目の10が追加される
    ms.insert(10); // 3つ目の10が追加される

    // 全要素を出力
    std::cout << "Elements in multiset: ";
    for (int val : ms) {
        std::cout << val << " "; // -> 10 10 10 20 30
    }
    std::cout << std::endl;

    // 個数チェック
    std::cout << "Count of 10: " << ms.count(10) << std::endl; // -> 3

    // 値を指定して削除 (全ての10が消える)
    ms.erase(10);
    std::cout << "After erasing value 10: ";
    for (int val : ms) {
        std::cout << val << " "; // -> 20 30
    }
    std::cout << std::endl;

    // イテレータを使って1つだけ削除する
    ms.insert(40);
    ms.insert(40);
    // 最初の40を見つけて、そのイテレータを渡す
    auto it = ms.find(40);
    if (it != ms.end()) {
        ms.erase(it);
    }
    std::cout << "After erasing one 40: ";
    for (int val : ms) {
        std::cout << val << " "; // -> 20 30 40
    }
    std::cout << std::endl;

    return 0;
}
```

---
### `set` と `multiset` の使い分け
* **`set`**: 要素の**存在有無**だけが重要な場合。（例: 訪問済みの頂点管理）
* **`multiset`**: 要素の**個数**や、**重複を含めた順序**が重要な場合。（例: 数列の中央値の管理）
