// ============================================================
// 行列累乗ライブラリ (Matrix Exponentiation)
// AtCoder等の競技プログラミング用
//
// 使い方:
//   Matrix A(2, 2, MOD);      // 2x2 のゼロ行列, mod = MOD
//   A[0][0] = 1; A[0][1] = 1;
//   A[1][0] = 1; A[1][1] = 0;
//   Matrix E = Matrix::identity(2, MOD);
//   Matrix B = A * E;         // 行列積
//   Matrix C = mat_pow(A, n); // A^n (繰り返し二乗法, O(k^3 log n))
//
// フィボナッチ数列の例:
//   Matrix A(2, 2, MOD);
//   A[0][0]=1; A[0][1]=1; A[1][0]=1; A[1][1]=0;
//   Matrix R = mat_pow(A, n);
//   // fib(n) = R[0][1] (fib(0)=0, fib(1)=1 として)
// ============================================================
#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int h, w;                       // 行数, 列数
    long long mod;                  // 法 (0 の場合は mod を取らない)
    vector<vector<long long>> a;

    Matrix() : h(0), w(0), mod(0) {}

    // h x w のゼロ行列を作る。mod=0 ならオーバーフローに注意(mod無し用途向け)
    Matrix(int h_, int w_, long long mod_ = 0)
        : h(h_), w(w_), mod(mod_), a(h_, vector<long long>(w_, 0)) {}

    vector<long long>& operator[](int i) { return a[i]; }
    const vector<long long>& operator[](int i) const { return a[i]; }

    // n x n の単位行列
    static Matrix identity(int n, long long mod_ = 0) {
        Matrix I(n, n, mod_);
        for (int i = 0; i < n; i++) I[i][i] = 1;
        return I;
    }

    // 行列の加算
    Matrix operator+(const Matrix& other) const {
        assert(h == other.h && w == other.w);
        Matrix res(h, w, mod);
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++) {
                res[i][j] = a[i][j] + other[i][j];
                if (mod) res[i][j] %= mod;
            }
        return res;
    }

    // 行列の乗算 (h x w) * (w x other.w) = (h x other.w)
    Matrix operator*(const Matrix& other) const {
        assert(w == other.h);
        Matrix res(h, other.w, mod);
        for (int i = 0; i < h; i++) {
            for (int k = 0; k < w; k++) {
                if (a[i][k] == 0) continue;
                long long aik = a[i][k];
                for (int j = 0; j < other.w; j++) {
                    // __int128 を使ってオーバーフローを回避
                    __int128 val = (__int128)res[i][j] + (__int128)aik * other[k][j];
                    if (mod) val %= mod;
                    res[i][j] = (long long)val;
                }
            }
        }
        return res;
    }

    Matrix& operator*=(const Matrix& other) {
        *this = (*this) * other;
        return *this;
    }
};

// 正方行列 A の n 乗を繰り返し二乗法で計算する。O(k^3 log n) (k は行列サイズ)
// n = 0 のときは単位行列を返す
Matrix mat_pow(Matrix A, long long n) {
    assert(A.h == A.w);
    int k = A.h;
    Matrix res = Matrix::identity(k, A.mod);
    while (n > 0) {
        if (n & 1) res *= A;
        A *= A;
        n >>= 1;
    }
    return res;
}

// ベクトル(1 x k)に行列を繰り返し二乗法の途中で適用したい場合など、
// v (長さ k) に対して A^n * v を計算するヘルパー(列ベクトルとして扱う)
vector<long long> mat_pow_vec(Matrix A, vector<long long> v, long long n) {
    assert(A.h == A.w && (int)v.size() == A.h);
    Matrix R = mat_pow(A, n);
    int k = A.h;
    vector<long long> res(k, 0);
    for (int i = 0; i < k; i++) {
        __int128 sum = 0;
        for (int j = 0; j < k; j++) sum += (__int128)R[i][j] * v[j];
        if (R.mod) sum %= R.mod;
        res[i] = (long long)sum;
    }
    return res;
}
