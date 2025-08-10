# C++ チートシート: std::map

キーと値をペアで管理するデータ構造。キーを基準に自動でソートされるのが最大の特徴です。

---
## 基本的な操作

### 宣言
```cpp
#include <map>
map<キーの型, 値の型> m;
```

### 要素の追加とアクセス
`m[key]` と `m.at(key)` は似ていますが、キーが存在しない場合の挙動が異なります。

* `m[key] = value;`
    * キーが存在すれば、値を上書きします。
    * **キーが存在しなければ、新しい要素を値の型の初期値で自動的に作成します。** (例: `int`なら`0`)

* `m.at(key)`
    * キーが存在すれば、その値を返します。
    * **キーが存在しなければ、エラー（`std::out_of_range`）を発生させます。**

---
## 要素の確認と削除

* `m.count(key)`: キーが存在すれば`1`、存在しなければ`0`を返します。`if (m.count(key))` の形で存在チェックによく使われます。
* `m.erase(key)`: 指定したキーを持つ要素を削除します。

---
## サイズと状態

* `m.size()`: 要素数を返します。
* `m.empty()`: マップが空なら`true`、そうでなければ`false`を返します。

---
## 最大・最小キーの取得

マップはキーでソートされているため、最初と最後の要素が最小・最大のキーを持つ要素になります。

* `(*m.begin()).first`: **最小のキー**を取得します。
* `(*m.rbegin()).first`: **最大のキー**を取得します。（`rbegin`は逆イテレータの先頭）

---
## 実践的なコード例

```cpp
#include <iostream>
#include <string>
#include <map>

int main() {
    // map<キー, 値>
    std::map<std::string, int> score;

    // [] を使った追加
    score["Alice"] = 100;
    score["Charlie"] = 75;
    score["Bob"] = 90; // キーの順番に関わらず、自動でソートされる

    // アクセス
    std::cout << "Alice's score: " << score["Alice"] << std::endl; // -> 100

    // 存在しないキーに[]でアクセスすると、要素が自動で作られる
    std::cout << "David's score (default): " << score["David"] << std::endl; // -> 0

    // 存在チェック
    if (score.count("Charlie")) {
        std::cout << "Charlie exists." << std::endl;
    }

    // 要素の削除
    score.erase("David");

    // サイズ確認
    std::cout << "Size: " << score.size() << std::endl; // -> 3

    // 最大・最小キーの取得
    if (!score.empty()) {
        std::cout << "Min key: " << (*score.begin()).first << std::endl;  // -> "Alice"
        std::cout << "Max key: " << (*score.rbegin()).first << std::endl; // -> "Charlie"
    }

    // 全要素をループ（C++17の構造化束縛を使うと綺麗）
    std::cout << "--- All scores ---" << std::endl;
    for (const auto& [key, value] : score) {
        std::cout << key << ": " << value << std::endl;
    }
    // 出力はキーのアルファベット順になる:
    // Alice: 100
    // Bob: 90
    // Charlie: 75

    return 0;
}
```

---
## 重要なポイント 📌
* **自動ソート**: `std::map`は常にキーでソートされています。そのため、要素の追加や削除には `O(log N)` の計算時間がかかります。
* **キーのユニーク性**: 同じキーを複数登録することはできません。後から追加したもので上書きされます。
* **`unordered_map`との違い**: ソートが不要で、とにかく速さを求める場合は`std::unordered_map`を検討します。こちらはハッシュテーブルを使い、平均 `O(1)` でアクセスできます。
