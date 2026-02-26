# 競プロ用 C++ 回文判定チートシート

最終更新: 2025-08-29

競技プログラミングで「**回文かどうか**」を高速・簡潔に判定するためのスニペット集。  
どれも **O(n)**、追加メモリは原則 **O(1)**（必要なら `reverse` 方式は O(n)）。想定は C++17 以降。

---

## 基本：二点ポインタ（最速・安定）

```cpp
// s が回文なら true
bool is_pal(const string& s) {
    for (size_t i = 0, j = s.size() ? s.size() - 1 : 0; i < j; ++i, --j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}
```

- 文字列長 0/1 も自然に true。
- `size_t` を使い負の値にしない。空文字時は `j` の初期化に注意（上記は安全）。

### 汎用（配列・vector など任意のランダムアクセス範囲）

```cpp
template <class It>
bool is_pal_range(It first, It last) {
    if (first == last) return true;            // 空
    --last;                                    // 末尾要素へ
    while (first < last) {
        if (!(*first == *last)) return false;  // 演算子== が必要
        ++first; --last;
    }
    return true;
}
```

---

## 反転比較（ワンライナー・簡潔）

```cpp
bool is_pal_rev(string s) {
    string t = s;
    reverse(t.begin(), t.end());   // O(n) 追加メモリ
    return s == t;
}
```

- 簡潔だがメモリを使う（大きな入力や多ケースでは二点ポインタ推奨）。

---

## 英数字のみ・大小文字無視（LeetCode/AtCoder で頻出）

- 英数字以外をスキップ、`A`–`Z` を小文字化して比較。

```cpp
bool is_pal_alnum_casefold(const string& s) {
    auto is_alnum = [](unsigned char c){ return isalnum(c); };
    auto lowerc   = [](unsigned char c){ return (unsigned char)tolower(c); };
    size_t i = 0, j = s.size();
    if (j) --j;
    while (i < j) {
        while (i < j && !is_alnum(s[i])) ++i;
        while (i < j && !is_alnum(s[j])) --j;
        if (i >= j) break;
        if (lowerc(s[i]) != lowerc(s[j])) return false;
        ++i; --j;
    }
    return true;
}
```

> 注意: `ctype.h` 系は **`unsigned char` にキャスト**してから渡す。未定義動作回避。

---

## k 箇所まで不一致を許容（ほぼ回文判定）

```cpp
bool is_pal_k_mismatch(const string& s, int k) {
    int mism = 0;
    for (size_t i = 0, j = s.size() ? s.size() - 1 : 0; i < j; ++i, --j) {
        if (s[i] != s[j] && ++mism > k) return false;
    }
    return true;
}
```

- 例: 1 文字までズレ OK なら `k=1`。

---

## 1 回削除で回文にできるか（削除許可 1 回）

- 二点が初めて不一致のとき、片方をスキップして残りが回文か確認。

```cpp
bool is_pal_after_one_delete(const string& s) {
    auto check = [&](size_t l, size_t r) {
        while (l < r) if (s[l++] != s[r--]) return false;
        return true;
    };
    size_t i = 0, j = s.size();
    if (j) --j;
    while (i < j) {
        if (s[i] == s[j]) { ++i; --j; }
        else return check(i+1, j) || check(i, j-1);
    }
    return true;
}
```

---

## ローリングハッシュでの回文判定（高速比較の応用）

- 多数クエリ（区間回文判定）に有効。単発なら上の二点で十分。

```cpp
// 典型的な多項式ハッシュ（mod 2^64 で自然オーバーフロー）
struct RH {
    using ull = unsigned long long;
    static constexpr ull B = 911382323ull;
    vector<ull> h, p;
    RH(const string& s) {
        size_t n = s.size();
        h.assign(n+1, 0); p.assign(n+1, 1);
        for (size_t i = 0; i < n; ++i) {
            h[i+1] = h[i]*B + (unsigned char)s[i];
            p[i+1] = p[i]*B;
        }
    }
    // [l, r) のハッシュ
    ull get(size_t l, size_t r) const { return h[r] - h[l]*p[r-l]; }
};
// 例: s の部分文字列 [l, r) が回文か？
bool is_pal_substr_by_hash(const string& s, size_t l, size_t r) {
    string rs = s;
    reverse(rs.begin(), rs.end());
    RH f(s), g(rs);
    // 反転側の対応区間: [n-r, n-l)
    size_t n = s.size();
    return f.get(l, r) == g.get(n - r, n - l);
}
```

- `2^64` では稀に衝突。厳密性が必要なら **二重ハッシュ**や大きな素数 mod を使用。

---

## 罠・落とし穴（WA/RE を避ける）

- `tolower`/`isalnum` へ **負の char を渡さない**（`unsigned char` にキャスト）。
- `size_t j = s.size() - 1;` は **空文字でアンダーフロー**。本書の初期化に倣う。
- Unicode（全角／サロゲートなど）は **ここでは非対応**。競プロでは基本 ASCII 想定。
- 反転比較は **O(n) メモリ**、TLE/MLE 余裕がなければ二点ポインタ。

---

## 使い所メモ

- **単発判定**: `is_pal`（二点）
- **多ケース一括**: `is_pal` または `is_pal_range`
- **整形つき**（英数字のみ・ケース無視）: `is_pal_alnum_casefold`
- **許容誤差**: `is_pal_k_mismatch`
- **1 文字削除可**: `is_pal_after_one_delete`
- **区間クエリ多発**: ローリングハッシュ

---

## ミニテスト

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<pair<string,bool>> tc = {
        {"", true},
        {"a", true},
        {"abba", true},
        {"abcba", true},
        {"abca", false},
        {"A man, a plan, a canal: Panama", true}, // with alnum+casefold
        {"No lemon, no melon", true},              // with alnum+casefold
    };
    for (auto& [s, expect] : tc) {
        bool b1 = is_pal(s);
        bool b2 = is_pal_rev(s);
        bool b3 = is_pal_alnum_casefold(s);
        cout << s << " | is_pal=" << b1
             << " rev=" << b2
             << " alnumCase=" << b3 << endl;
    }
}
```

---

## ヘッダ最小セット（典型）

```cpp
#include <bits/stdc++.h>
using namespace std;
```

- 競プロでは `bits/stdc++.h` が手軽（AtCoder/GCC 環境など）。

---

### ライセンス

パブリックドメイン相当。自由にコピペ・改変して使ってください。
