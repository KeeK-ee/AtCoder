# C++ チートシート: 各桁の和 (Sum of Digits)

整数の各桁の数字を足し合わせる、典型的なアルゴリズムについてまとめます。

---
## アルゴリズムの考え方
整数 `n` に対して、以下の操作を `n` が `0` になるまで繰り返します。

1.  **`n % 10`**: `10`で割った余りを求めることで、**一番下の桁の数字**を取り出します。
2.  **`n /= 10`**: `10`で割ることで、**一番下の桁を取り除きます**。

例えば `n = 123` の場合：
1. `sum += 123 % 10` (sumに3が足される), `n = 123 / 10` (nが12になる)
2. `sum += 12 % 10` (sumに2が足される), `n = 12 / 10` (nが1になる)
3. `sum += 1 % 10` (sumに1が足される), `n = 1 / 10` (nが0になる)
4. `n`が`0`になったのでループが終了します。

---
## 実装 (整数演算)
あなたのメモにある、最も効率的で標準的な実装です。

```cpp
#include <iostream>

// 各桁の和を計算する関数
int findSumOfDigits(int n) {
    int sum = 0;
    // nが負数の場合も考慮するなら abs(n) を使う
    // n = std::abs(n); 
    
    while (n > 0) { // n が 0 になるまで
        sum += n % 10; // 一番下の桁をsumに加える
        n /= 10;     // 一番下の桁を取り除く
    }
    return sum;
}

int main() {
    int number = 12345;
    int result = findSumOfDigits(number);
    std::cout << "The sum of digits of " << number << " is " << result << std::endl; // -> 15
    return 0;
}
```

---
## 別解 (文字列を利用する方法)
一度数値を文字列に変換し、各文字を数値に戻して足し合わせる方法です。発想がシンプルで分かりやすいのが特徴です。

```cpp
#include <iostream>
#include <string>
#include <numeric> // std::accumulate

int sumDigitsWithString(int n) {
    std::string s = std::to_string(n);
    int sum = 0;
    for (char c : s) {
        // 文字 '0' を引くことで、文字を数値に変換する
        sum += c - '0';
    }
    return sum;
}
```

---
## 重要なポイント 📌
* **効率性**: 一般的に、整数演算のまま処理する方が、文字列への変換オーバーヘッドがないため高速です。
* **負の数**: `n`が負の場合、`findSumOfDigits(-123)`は`0`を返します。もし負の数も各桁の和（例: `1+2+3=6`）を計算したい場合は、最初に関数の先頭で`n = std::abs(n);`のように絶対値を取る処理を追加します。
* **`long long`への対応**: 入力される数値が`int`の範囲を超える可能性がある場合は、引数や変数の型を`long long`に変更することで簡単に対処できます。
