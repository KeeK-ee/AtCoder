# C++ チートシート: std::queue

「先入れ先出し」（FIFO: First-In, First-Out）の原則でデータを管理するコンテナアダプタです。お店の行列のように、一番最初に追加された要素からしか取り出せません。

---
## 基本的な操作

### ヘッダと宣言
```cpp
#include <queue>
queue<要素の型> q;
```

### 主要なメンバ関数

* `q.push(x)`
    キューの**最後尾**に要素 `x` を追加します。

* `q.pop()`
    キューの**一番前**の要素を削除します。この関数は値を返さないことに注意してください。

* `q.front()`
    キューの**一番前**の要素を参照します（値を返します）。キューが空のときに呼び出すと未定義動作となるため、`empty()`で確認してから使います。

* `q.size()`
    キュー内の要素数を返します。

* `q.empty()`
    キューが空（要素数が0）であれば `true`、そうでなければ `false` を返します。

---
## 実践的なコード例

チケットの待機列をシミュレートする簡単な例です。

```cpp
#include <iostream>
#include <string>
#include <queue>

int main() {
    std::queue<std::string> waiting_line;

    // 1. 人が列に並ぶ (push)
    std::cout << "Aliceが並びました。" << std::endl;
    waiting_line.push("Alice");
    std::cout << "Bobが並びました。" << std::endl;
    waiting_line.push("Bob");
    std::cout << "Charlieが並びました。" << std::endl;
    waiting_line.push("Charlie");

    std::cout << "\n現在の待ち人数: " << waiting_line.size() << "人\n" << std::endl;

    // 2. 列が空になるまで、先頭から対応する
    while (!waiting_line.empty()) {
        // 先頭の人を確認 (front)
        std::string current_person = waiting_line.front();
        std::cout << current_person << "さんの番です。対応します。" << std::endl;

        // 先頭の人を列から削除 (pop)
        waiting_line.pop();
    }

    std::cout << "\n列は空になりました。" << std::endl;

    return 0;
}
```

---
## 重要なポイント 📌
* **FIFO構造**: 「最初に入ったものが、最初に出る」という単純なルールです。
* **一方通行**: `front()`で先頭、`back()`で末尾の要素にアクセスできますが、途中の要素にアクセスすることはできません。
* **`pop()`は値を返さない**: 先頭の要素を取得したい場合は、`front()`を呼び出してから`pop()`を呼び出す必要があります。
* **用途**: 幅優先探索（BFS）の実装、タスクのスケジューリングなど、処理の順番が重要な場面で広く使われます。
