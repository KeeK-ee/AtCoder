# C++ チートシート: 三角関数

C++の三角関数を扱う際の、角度の単位（弧度法と度数法）の変換や、主要な関数についてまとめます。

---
## 【最重要】角度の単位は「弧度法 (Radian)」
C++の三角関数（`sin`, `cos`, `tan`など）は、引数として**弧度法（ラジアン）**の値を取ります。私たちが普段使う**度数法（ディグリー）**の値をそのまま渡すと、意図しない結果になります。

### 度数法から弧度法への変換
度数法の角度 `d` を弧度法の角度 `r` に変換する公式は以下の通りです。
`r = d * PI / 180.0`

```cpp
#include <cmath> // M_PI を使うため (環境による)

// 円周率PIは自分で高精度なものを定義するのが確実
const double PI = 3.14159265358979323846;

double degree = 30.0;
double radian = degree * PI / 180.0; // 30度をラジアンに変換
```

---
## 主要な三角関数
`<cmath>`ヘッダが必要です。引数はすべて**弧度法**です。

* `sin(rad)`: サイン (正弦)
* `cos(rad)`: コサイン (余弦)
* `tan(rad)`: タンジェント (正接)

---
## 逆三角関数 (Arc Functions)
値から角度（**弧度法**）を求めます。

* `asin(val)`: アークサイン。`-1 <= val <= 1` の値を引数にとり、`-PI/2` から `PI/2` の範囲の角度（ラジアン）を返す。
* `acos(val)`: アークコサイン。`-1 <= val <= 1` の値を引数にとり、`0` から `PI` の範囲の角度（ラジアン）を返す。
* `atan(val)`: アークタンジェント。`y/x` の値を引数にとり、`-PI/2` から `PI/2` の範囲の角度（ラジアン）を返す。
* `atan2(y, x)`: **(推奨)** 座標 `(x, y)` から角度を求めるのに非常に便利。`x`軸の正の方向に対する角度（ラジアン）を `-PI` から `PI` の範囲で正しく返してくれる。

---
## 実践的なコード例

```cpp
#include <iostream>
#include <cmath>
#include <iomanip> // fixed, setprecision

int main() {
    // 円周率を定義
    const double PI = 3.141592653589793;

    // 角度を度数法で入力
    double degree;
    std::cin >> degree;

    // 度数法を弧度法に変換
    double radian = degree * PI / 180.0;

    // 小数点以下12桁で出力する設定
    std::cout << std::fixed << std::setprecision(12);

    std::cout << "sin(" << degree << " deg) = " << sin(radian) << std::endl;
    std::cout << "cos(" << degree << " deg) = " << cos(radian) << std::endl;
    std::cout << "tan(" << degree << " deg) = " << tan(radian) << std::endl;

    // 逆三角関数の例
    double x = 4.0, y = 3.0;
    double angle_rad = atan2(y, x);
    double angle_deg = angle_rad * 180.0 / PI;

    std::cout << "Angle for (x=4, y=3) is " << angle_deg << " degrees." << std::endl;

    return 0;
}
```

---
## 重要なポイント 📌
* **ヘッダ**: 三角関数を使うには `<cmath>` が必要です。
* **単位の徹底**: 計算の最初に入力値を弧度法に変換し、最後に出力する際に度数法に戻す、という流れを徹底するのがバグを減らすコツです。
* **`atan2(y, x)` を使う**: 座標から角度を求める際は、`atan(y/x)` よりも `atan2(y, x)` を使う方が、象限を正しく判定してくれるため安全で簡単です。
