#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <functional>
#include <ranges>
#include <cctype>
#include <iomanip>
#include <random>
using namespace std;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
using ld = long double;
using pll = pair<ll, ll>;
template <typename T> using Vec = vector<T>;
using mint = modint1000000007;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string dir = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, vector<T>, greater<T>>; //小さい順

ll llpow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

template <typename T>
void debug_print(const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const vector<vector<T>>& v) {
    for (const auto& row : v) {
        debug_print(row);
    }
}

template<class T>
bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T>
bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

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

/**
 * 行列累乗
 */
void solve() {
    ll N, K; cin >> N >> K;
    Matrix A(N, N, (ll)mint::mod());
    rep(i, 0, N)rep(j, 0, N){
        ll a; cin >> a; A[i][j]=a;
    }
    Matrix M =mat_pow(A, K);
    mint ans=0;
    rep(i, 0, N)rep(j, 0, N) ans+=M[i][j];
    out(ans.val());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}