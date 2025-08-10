# C++ チートシート: 二分探索 (`lower_bound` / `upper_bound`)

ソート済みのコンテナ（`vector`など）から、特定の値を高速に検索するためのアルゴリズムです。

---
## `std::lower_bound`
指定したキー **以上** (`>= key`) の値が現れる、最初の要素の位置（イテレータ）を返します。

* **イメージ**: 「この値は、配列のどの位置から始まるか？」

---
## `std::upper_bound`
指定したキー **より大きい** (`> key`) 値が現れる、最初の要素の位置（イテレータ）を返します。

* **イメージ**: 「この値は、配列のどの位置で終わるか？」

---
## 実践的なコード例
`lower_bound`と`upper_bound`を組み合わせることで、「配列内に特定の値がいくつ存在するか」を効率的に計算できます。

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // lower_bound, upper_bound
#include <iterator>  // distance

int main() {
    // 必ずソート済みの配列を用意する
    std::vector<int> vec = {10, 20, 30, 30, 30, 40, 50};
    int key = 30;

    // --- lower_bound の使用例 ---
    // auto を使うと、長いイテレータの型名を省略できる！
    auto it_lower = std::lower_bound(vec.begin(), vec.end(), key);

    // イテレータからインデックス番号を取得
    long long idx_lower = std::distance(vec.begin(), it_lower);
    
    std::cout << "lower_bound(30): " << std::endl;
    std::cout << "  - 値: " << *it_lower << std::endl;      // -> 30
    std::cout << "  - インデックス: " << idx_lower << std::endl; // -> 2


    // --- upper_bound の使用例 ---
    auto it_upper = std::upper_bound(vec.begin(), vec.end(), key);
    long long idx_upper = std::distance(vec.begin(), it_upper);

    std::cout << "upper_bound(30): " << std::endl;
    std::cout << "  - 値: " << *it_upper << std::endl;      // -> 40
    std::cout << "  - インデックス: " << idx_upper << std::endl; // -> 5


    // --- 応用: keyの個数を数える ---
    long long count = std::distance(it_lower, it_upper);
    std::cout << "値が30の要素数: " << count << std::endl; // -> 3

    return 0;
}
```

---
## 重要なポイント 📌
* **ソート済みが必須！**: 二分探索は、データがソートされていることが大前提です。使用前に必ずソートしてください。
* **戻り値はイテレータ**: 関数が返すのはインデックス番号ではなく、要素の位置を指し示す「イテレータ」です。
* **インデックスの取得**: イテレータからインデックス番号に変換するには、`std::distance(コンテナ.begin(), イテレータ)` を使います。
* **`auto`の活用**: `auto`キーワードを使うと、長くて複雑なイテレータの型を記述する必要がなくなり、コードが非常にスッキリします。
* **存在しない場合**: 探しているキーが配列内のどの要素よりも大きい場合、`lower_bound`も`upper_bound`も `vec.end()` を返します。
