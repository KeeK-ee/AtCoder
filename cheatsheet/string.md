# C++ チートシート: std::string

文字列の連結、部分文字列の取得、文字種の判定など、競技プログラミングで頻出の`std::string`操作をまとめます。

---
## 文字列の連結

`+`または`+=`演算子を使って、文字列や文字を簡単に追加できます。

* `S += T;` または `S = S + T;`
    文字列`S`の末尾に、文字列`T`を連結します。

* `S += c;` または `S = S + c;`
    文字列`S`の末尾に、`char`型の文字`c`を1文字追加します。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s1 = "At";
    std::string s2 = "Coder";
    
    s1 += s2; // s1が "AtCoder" になる
    std::cout << s1 << std::endl;

    s1 += '!'; // s1が "AtCoder!" になる
    std::cout << s1 << std::endl;
    return 0;
}
```

---
## 部分文字列の取得: `substr`

文字列の一部を切り出して新しい文字列として取得します。**インデックスは0から始まる**ことに注意してください。

* `S.substr(l)`
    文字列`S`の **`l`番目**の文字から**最後まで**の部分文字列を返します。

* `S.substr(l, r)`
    文字列`S`の **`l`番目**の文字から**`r`文字分**の部分文字列を返します。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "abcdefg";
    // インデックス:  0123456

    // 2番目の 'c' から最後まで
    std::cout << s.substr(2) << std::endl; // -> "cdefg"

    // 1番目の 'b' から3文字分
    std::cout << s.substr(1, 3) << std::endl; // -> "bcd"
    return 0;
}
```

---
## 文字種の判定

`<cctype>`ヘッダにある関数を使って、1文字が英大文字か英小文字かを判定できます。

* `isupper(c)`
    文字`c`が**英大文字** (`A`～`Z`) の場合、`0`以外の整数（真）を返します。

* `islower(c)`
    文字`c`が**英小文字** (`a`～`z`) の場合、`0`以外の整数（真）を返します。

**ポイント**: 戻り値は`bool`型ではないですが、`if`文の条件式でそのまま使えます。

```cpp
#include <iostream>
#include <string>
#include <cctype> // isupper, islower を使うために必要

int main() {
    char c1 = 'A';
    char c2 = 'b';
    char c3 = '7';

    if (isupper(c1)) {
        std::cout << c1 << " is an uppercase letter." << std::endl;
    }
    if (islower(c2)) {
        std::cout << c2 << " is a lowercase letter." << std::endl;
    }
    if (!isupper(c3) && !islower(c3)) {
        std::cout << c3 << " is not an alphabet letter." << std::endl;
    }
    return 0;
}
```

---
## その他の便利な操作

* `S.size()` / `S.length()`
    文字列の長さを返します。どちらも機能は同じです。

* `S.front()` / `S.back()`
    それぞれ先頭の文字、末尾の文字を返します。

* `S[i]`
    `i`番目の文字にアクセスします。
