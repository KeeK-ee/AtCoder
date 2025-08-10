# C++ チートシート: std::vector

動的にサイズを変更できる配列（可変長配列）です。C++で最も基本的かつ強力なコンテナの一つです。

---
## 1次元vectorの宣言と初期化

### 基本的な宣言
```cpp
#include <vector>
vector<要素の型> v; // 空のvector
```

### サイズを指定した初期化
* `vector<型> v(N);`
    `N`個の要素を持つvectorを作成します。各要素はそれぞれの型の初期値（`int`なら`0`）で初期化されます。

* `vector<型> v(N, value);`
    `N`個の要素を持つvectorを作成し、すべての要素を`value`で初期化します。

```cpp
// 5個の要素を0で初期化
vector<int> v1(5); // {0, 0, 0, 0, 0}

// 5個の要素を100で初期化
vector<int> v2(5, 100); // {100, 100, 100, 100, 100}
```

---
## 基本的な操作

* `v.push_back(x)`
    vectorの**末尾**に要素`x`を追加します。計算量は通常O(1)です。

* `v.pop_back()`
    vectorの**末尾**の要素を削除します。

* `v.size()`
    vectorの要素数を返します。

* `v[i]`
    `i`番目の要素にアクセスします。**範囲外のインデックスにアクセスすると未定義動作となる**ため注意が必要です。

---
## 2次元vectorの宣言

### 固定サイズの2次元配列
`M`行`N`列の2次元配列を作成し、全要素を`initial_value`で初期化します。

```cpp
int M = 3, N = 4;
int initial_value = 0;
vector<vector<int>> vv(M, vector<int>(N, initial_value));
```

### 可変サイズの2次元配列（ジャグ配列）
行ごとに要素数が異なる配列を作りたい場合に使います。

```cpp
int M = 3;
vector<vector<int>> vv(M); // M個の空のvectorを持つvector

vv[0].push_back(1);
vv[0].push_back(2);
vv[1].push_back(3);
// vv[0]のサイズは2, vv[1]のサイズは1, vv[2]のサイズは0
```

---
## ループとソート

### 範囲for文によるループ
```cpp
vector<int> v = {10, 20, 30};
for (int x : v) {
    cout << x << " "; // 10 20 30
}
```

### ソート
`<algorithm>`ヘッダが必要です。`sort`関数にコンテナの先頭と末尾のイテレータを渡します。

* `sort(v.begin(), v.end());` // 昇順ソート
* `sort(v.rbegin(), v.rend());` // 降順ソート (リバースイテレータを使用)

---
## 実践的なコード例

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // sort

int main() {
    // サイズ5、初期値0で宣言
    std::vector<int> v(5);

    // forループで値を代入
    for (int i = 0; i < v.size(); ++i) {
        v[i] = (i + 1) * 10;
    }
    // v = {10, 20, 30, 40, 50}

    // 末尾に追加
    v.push_back(60);
    // v = {10, 20, 30, 40, 50, 60}

    // 末尾を削除
    v.pop_back();
    // v = {10, 20, 30, 40, 50}

    // 範囲for文で出力
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // 降順ソート
    std::sort(v.rbegin(), v.rend());
    // v = {50, 40, 30, 20, 10}

    std::cout << "Sorted descending: ";
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}
