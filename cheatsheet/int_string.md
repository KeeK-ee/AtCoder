# C++ チートシート: intとstringの相互変換

数値計算と文字列操作を組み合わせる際に必須となる、整数(`int`, `long long`)と文字列(`string`)の相互変換についてまとめます。

---
## 文字列 (string) から 整数 (int) へ

### `std::stoi()` / `std::stoll()`
文字列を数値に変換します。`long long`型に変換したい場合は`stoll()`を使います。

* **`stoi(string)`**: `string` を `int` に変換
* **`stoll(string)`**: `string` を `long long` に変換

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "12345";
    std::cout << "元の文字列: " << s << std::endl;

    // 文字列として操作
    s += "6"; // "123456"

    // 文字列を整数に変換
    int num = std::stoi(s);

    std::cout << "変換後の整数: " << num << std::endl;

    // 整数として計算
    num++; // 123457

    std::cout << "計算後の整数: " << num << std::endl;

    return 0;
}
```

**注意点**:
* 変換できない文字列（例: `"abc"`）を渡すと、`std::invalid_argument` エラーが発生します。
* `int`や`long long`の範囲を超える巨大な数値の文字列を渡すと、`std::out_of_range` エラーが発生します。

---
## 整数 (int) から 文字列 (string) へ

### `std::to_string()`
数値を文字列に変換します。`int`でも`long long`でも同じ関数を使えます。

```cpp
#include <iostream>
#include <string>

int main() {
    int num = 1234;
    std::cout << "元の整数: " << num << std::endl;

    // 整数として計算
    num++; // 1235

    // 整数を文字列に変換
    std::string s = std::to_string(num);

    std::cout << "変換後の文字列: " << s << std::endl;

    // 文字列として操作（連結）
    s += "678"; // "1235678"

    std::cout << "操作後の文字列: " << s << std::endl;

    return 0;
}
```

---
## 応用: 1文字の数字と整数値の変換
`'0'`から`'9'`までの1文字の数字を、`0`から`9`までの整数値に変換する、またはその逆を行う場合は、文字コードの性質を利用した以下の方法が高速で便利です。

* **文字 から 数値へ**: `int value = character - '0';`
* **数値 から 文字へ**: `char character = value + '0';`

```cpp
#include <iostream>
#include <string>

int main() {
    // 文字 '7' を 数値 7 に変換
    char c = '7';
    int val = c - '0';
    std::cout << "'" << c << "' -> " << val << std::endl;

    // 数値 9 を 文字 '9' に変換
    int v = 9;
    char ch = v + '0';
    std::cout << v << " -> '" << ch << "'" << std::endl;

    return 0;
}
```

---
## 重要なポイント 📌
* **ヘッダ**: `stoi`, `stoll`, `to_string` を使うには、`<string>` ヘッダをインクルードする必要があります。
* **使い分け**:
    * 文字列全体を一つの数値として扱いたい → `stoi`, `stoll`
    * 数値を文字列として連結したり、桁を操作したい → `to_string`
    * 1桁の数字だけを扱いたい → `c - '0'` の計算が最速
