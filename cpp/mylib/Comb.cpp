#include <vector>
#include <iostream>

using ll = long long;

// a^b (mod m) を計算する関数 (繰り返し二乗法)
// 計算量: O(log b)
ll modPow(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// 組み合わせ nCr (mod m) を計算する構造体
// 注意: m は素数であることを前提とします
struct Comb {
    int MAX;
    ll MOD;
    std::vector<ll> fact, finv;

    // コンストラクタで前計算を行う
    // 計算量: O(max_n)
    Comb(int max_n, ll mod) : MAX(max_n), MOD(mod), fact(max_n), finv(max_n) {
        fact[0] = 1;
        for (int i = 1; i < MAX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        // フェルマーの小定理より、a^(m-2) ≡ a^-1 (mod m)
        finv[MAX - 1] = modPow(fact[MAX - 1], MOD - 2, MOD);
        for (int i = MAX - 2; i >= 0; i--) {
            finv[i] = finv[i + 1] * (i + 1) % MOD;
        }
    }

    // nCr を計算する
    // 計算量: O(1)
    ll nCr(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        return fact[n] * (finv[k] * finv[n - k] % MOD) % MOD;
    }
    
    // 順列 nPr を計算する場合 (おまけ)
    ll nPr(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        return fact[n] * finv[n - k] % MOD;
    }
};

// 使用例
// int main() {
//     ll MOD = 998244353;
    
//     // a^b (mod m) の単体利用
//     ll a = 2, b = 10;
//     std::cout << "2^10 = " << modpow(a, b, MOD) << "\n"; // 1024
    
//     // 組み合わせライブラリの初期化 (最大N=500000、mod=998244353)
//     // ※ 余裕を持たせて問題の制約の最大値より少し大きめに設定します
//     Comb cb(500000, MOD);
    
//     // 100 C 5 を求める
//     std::cout << "100 C 5 = " << cb.nCr(100, 5) << "\n";
    
//     // 異常値 (n < k など) は 0 を返すようになっています
//     std::cout << "5 C 10 = " << cb.nCr(5, 10) << "\n"; // 0

//     return 0;
// }