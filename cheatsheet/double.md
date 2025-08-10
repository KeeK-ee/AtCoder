# C++ チートシート: 小数 (double)

浮動小数点数を扱う際の、出力フォーマット、四捨五入、および特有の注意点についてまとめます。

---
## 小数点以下の桁数を指定した出力

### 方法1: `cout` と `<iomanip>` (C++スタイル)
`std::fixed` と `std::setprecision(k)` を組み合わせて使います。
* **`fixed`**: 小数点表記を強制します。（例: `123.000` のように表示）
* **`setprecision(k)`**: 小数点以下の桁数を `k` 桁に指定します。

一度設定すると、再度変更するまで効果が持続します。

```cpp
#include <iostream>
#include <iomanip> // fixed, setprecision

int main() {
    double pi = 3.141592653589793;

    // 小数点以下10桁まで出力
    std::cout << std::fixed << std::setprecision(10);
    std::cout << pi << std::endl; // -> 3.1415926536 (四捨五入される)

    return 0;
}
```

### 方法2: `printf` (Cスタイル)
書式指定文字列を使って、出力形式を細かく制御できます。
* **`%.kf`**: 小数点以下 `k` 桁で出力します。

`printf` は `cout` の設定に影響されず、その場限りの出力に便利です。

```cpp
#include <cstdio> // printf

int main() {
    double pi = 3.141592653589793;
    printf("%.10f\n", pi); // -> 3.1415926536
    return 0;
}
```

---
## 丸め処理（四捨五入・切り上げ・切り捨て）

`<cmath>` ヘッダにある関数を使います。

* **`round(x)`**: `x` を**四捨五入**して最も近い整数値（`double`型）を返します。
* **`ceil(x)`**: `x` を**切り上げ**て、`x` 以上の最小の整数値（`double`型）を返します。
* **`floor(x)`**: `x` を**切り捨て**て、`x` 以下の最大の整数値（`double`型）を返します。

```cpp
#include <iostream>
#include <cmath> // round, ceil, floor

int main() {
    double a = 10.0, b = 3.0;
    double val = a / b; // 3.333...

    std::cout << "round(3.333) = " << round(val) << std::endl;   // -> 3
    std::cout << "ceil(3.333) = " << ceil(val) << std::endl;     // -> 4
    std::cout << "floor(3.333) = " << floor(val) << std::endl;   // -> 3

    double val2 = 3.7;
    std::cout << "round(3.7) = " << round(val2) << std::endl;     // -> 4
    
    return 0;
}
```

---
## 重要なポイント 📌
* **誤差 (Precision Error)**: `double`は内部的に2進数で小数を表現するため、`0.1`のような単純な10進数ですら正確に表現できず、ごくわずかな誤差が生じます。
* **`==`での比較は危険**: 上記の誤差のため、`double a == double b` のような直接比較は、意図通りに動作しないことがあります。
* **差分で比較する**: 2つの`double`値が等しいか判定したい場合は、その差の絶対値が非常に小さい値（イプシロン, `epsilon`）より小さいかどうかで判定するのが安全です。
    ```cpp
    double a, b;
    const double EPS = 1e-9; // 許容誤差
    if (std::abs(a - b) < EPS) {
        // aとbはほぼ等しいと見なす
    }
    ```
* **整数で計算する**: 可能な限り、計算は整数で行い、最後の出力の段階で割り算をして小数にするのが、誤差を避けるための最も良い方法です。
