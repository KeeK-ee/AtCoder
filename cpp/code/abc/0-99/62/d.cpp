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
using mint = modint998244353;

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
// Bit Vector
struct BitRank {
    // block: bit vector
    // count: the number of 1 within each block
    vector<unsigned long long> block;
    vector<unsigned int> count;
    
    // constructor
    BitRank() {}
    void resize(const unsigned int num) {
        block.resize(((num + 1) >> 6) + 1, 0);
        count.resize(block.size(), 0);
    }
    
    // set val(0 or 1) onto i-th bit
    void set(const unsigned int i, const unsigned long long val) {
        block[i >> 6] |= (val << (i & 63));
    }
    void build() {
        for (unsigned int i = 1; i < block.size(); i++) {
            count[i] = count[i - 1] + __builtin_popcountll(block[i - 1]);
        }
    }
    
    // the number of 1 in [0, i)
    unsigned int rank1(const unsigned int i) const {
        return count[i >> 6] +
        __builtin_popcountll(block[i >> 6] & ((1ULL << (i & 63)) - 1ULL));
    }
    // the number of 1 in [i, j)
    unsigned int rank1(const unsigned int i, const unsigned int j) const {
        return rank1(j) - rank1(i);
    }
    // the number of 0 in [0, i)
    unsigned int rank0(const unsigned int i) const {
        return i - rank1(i);
    }
    // the number of 0 in [i, j)
    unsigned int rank0(const unsigned int i, const unsigned int j) const {
        return rank0(j) - rank0(i);
    }
};
// http://drken1215.hatenablog.com/entry/2023/10/15/003821
// Wavelet Matrix
template<class T> struct WaveletMatrix {
    // inner data
    int height;
    vector<BitRank> bv;
    vector<int> pos;
    vector<vector<long long>> rui;

    // constructor (sigma: the number of characters)
    WaveletMatrix() {}
    WaveletMatrix(vector<T> vec) :
        WaveletMatrix(vec, *max_element(vec.begin(), vec.end()) + 1) {}
    WaveletMatrix(vector<T> vec, T sigma) {
        init(vec, sigma);
    }
    void init(vector<T> &vec, T sigma) {
        height = (sigma == 1) ? 1 : (64 - __builtin_clzll(sigma - 1));
        bv.resize(height), pos.resize(height);
        vector<T> A = vec;
        rui.resize(height + 1);
        for (int i = 0; i < height; ++i) {
            bv[i].resize(vec.size());
            for (int j = 0; j < vec.size(); ++j) {
                bv[i].set(j, get(vec[j], height - i - 1));
            }
            bv[i].build();
            auto it = stable_partition(vec.begin(), vec.end(), [&](int c) {
                return !get(c, height - i - 1);
            });
            pos[i] = it - vec.begin();
        }
        for (int i = 0; i <= height; ++i) {
            rui[i].resize((int)A.size() + 1);
            for (int j = 1; j <= (int)A.size(); ++j) {
                rui[i][j] = rui[i][j - 1] + A[j - 1];
            }
            if (i == height) break;
            stable_partition(A.begin(), A.end(), [&](int c) {
                return !get(c, height - i - 1);
            });
        }
    }
    
    // the i-th bit of "val" (0 or 1)
    int get(const T val, const int i) {
        return val >> i & 1;
    }
    
    // the number of "val" in [l, r)
    int rank(const T val, const int l, const int r) {
        return rank(val, r) - rank(val, l);
    }
    
    // the number of "val" in [0, i)
    int rank(T val, int i) {
        int p = 0;
        for (int j = 0; j < height; ++j) {
            if (get(val, height - j - 1)) {
                p = pos[j] + bv[j].rank1(p);
                i = pos[j] + bv[j].rank1(i);
            } else {
                p = bv[j].rank0(p);
                i = bv[j].rank0(i);
            }
        }
        return i - p;
    }
    
    // the k-th (0-indexed) smallest value in [l, r)
    T k_th_smallest(int k, int l, int r) {
        T res = 0;
        for (int i = 0; i < height; ++i) {
            const int j = bv[i].rank0(l, r);
            if (j > k){
                l = bv[i].rank0(l);
                r = bv[i].rank0(r);
            } else {
                l = pos[i] + bv[i].rank1(l);
                r = pos[i] + bv[i].rank1(r);
                k -= j;
                res |= (1LL << (height - i - 1));
            }
        }
        return res;
    }
    
    // the k-th (0-indexed) largest value in [l, r)
    T k_th_largest(int k, int l, int r) {
       return k_th_smallest(r - l - k - 1, l, r);
    }
    
    // the sum of the top-k sum in [l, r)
    T top_k_sum(int k, int l, int r) {
        if (l == r) return 0;
        T res = 0, val = 0;
        for (int i = 0; i < height; ++i) {
            const int j = bv[i].rank0(l, r);
            if (j > k) {
                l = bv[i].rank0(l);
                r = bv[i].rank0(r);
            } else {
                int l2 = bv[i].rank0(l);
                int r2 = bv[i].rank0(r);
                res += rui[i + 1][r2] - rui[i + 1][l2];
                l = pos[i] + bv[i].rank1(l);
                r = pos[i] + bv[i].rank1(r);
                k -= j;
                val |= (1LL << (height - i - 1));
            }
        }
        res += (long long)val * k;
        return res;
    }
    
    // the number of value between [loewr, upper) in [l, r)
    int range_freq(const int i, const int j, const T lower, const T upper,
                   const int l, const int r, const int x) {
        if (i == j || r <= lower || upper <= l) return 0;
        int mid = (l + r) >> 1;
        if (lower <= l && r <= upper) {
            return j - i;
        } else {
            T left = range_freq(bv[x].rank0(i), bv[x].rank0(j), lower, upper, l, mid, x + 1);
            T right = range_freq(pos[x] + bv[x].rank1(i), pos[x] + bv[x].rank1(j),
                                 lower, upper, mid, r, x + 1);
            return left + right;
        }
    }
    int range_freq(const int l, const int r, const T lower, const T upper){
        return range_freq(l, r, lower, upper, 0, 1LL << height, 0);
    }
    
    // the minmum value between [lower, upper) in [l, r)
    int range_min(const int i, const int j, const T lower, const T upper,
                  const int l, const int r, const int x, const int val){
        if (i == j || r <= lower || upper <= l) return -1;
        if (r - l == 1) return val;
        int mid = (l + r) >> 1;
        int res = range_min(bv[x].rank0(i), bv[x].rank0(j), lower, upper, l, mid, x + 1, val);
        if (res < 0) {
            return range_min(pos[x] + bv[x].rank1(i), pos[x] + bv[x].rank1(j),
                             lower, upper, mid, r, x + 1, val + (1LL << (height - x - 1)));
        } else return res;
    }
    int range_min(int l, int r, T lower, T upper) {
        return range_min(l, r, lower, upper, 0, 1LL << height, 0, 0);
    }
    
    // the max value (< val) in [l, r)
    T prev_value(int l, int r, T val) {
        int num = range_freq(l, r, 0, val);
        if (num == 0) return T(-1);
        else return k_th_smallest(l, r, num - 1);
    }
    
    // the min value (>= val) in [l, r)
    T next_value(int l, int r, T val) {
        int num = range_freq(l, r, 0, val);
        if (num == r - l) return T(-1);
        else return k_th_smallest(l, r, num);
    }
};

// 2D range count
template<class T> struct OrthogonalRangeCount {
    // inner data
    using ptt = pair<T, T>;
    const int sz;
    vector<T> X, Y;
    WaveletMatrix<T> wm;
    
    // constructor
    OrthogonalRangeCount(vector<ptt> candidate) : sz((int)candidate.size()), X(sz), Y(sz) {
        sort(candidate.begin(), candidate.end());
        vector<int> vec(sz);
        for (int i = 0; i < sz; ++i) {
            X[i] = candidate[i].first, Y[i] = candidate[i].second;
        }
        sort(Y.begin(), Y.end());
        Y.erase(unique(Y.begin(), Y.end()), Y.end());
        for (int i = 0; i < sz; ++i) {
            vec[i] = lower_bound(Y.begin(), Y.end(), candidate[i].second) - Y.begin();
        }
        wm.init(vec, Y.size());
    }
    
    // the number of points in [lx, rx) × [ly, ry)
    int query(const T lx, const T ly, const T rx, const T ry){
        const int lxid = lower_bound(X.begin(), X.end(), lx) - X.begin();
        const int rxid = lower_bound(X.begin(), X.end(), rx) - X.begin();
        const int lyid = lower_bound(Y.begin(), Y.end(), ly) - Y.begin();
        const int ryid = lower_bound(Y.begin(), Y.end(), ry) - Y.begin();
        if (lxid >= rxid || lyid >= ryid) return 0;
        return wm.range_freq(lxid, rxid, lyid, ryid);
    }
};

/**
 * top_k_sum:"昇順"のtop-k-sum(小さい順にk個の和)
 * ある境目があって、「それより左の大きい順k個のsum-それより右の小さい順k個のsum」のmaxが答え　境目は全探索できる　大きい順k個のsumは配列全体を-1倍して最後に-1倍する
 */
void solve() {
    ll N; cin >> N;
    Vec<ll> A(3*N);
    rep(i, 0, 3*N) cin >> A[i];
    Vec<ll> B(3*N);
    rep(i, 0, 3*N) B[i]=-A[i];
    WaveletMatrix WM1(B);
    WaveletMatrix WM2(A);

    ll ans=-INF;
    rep(i, N, 2*N+1){
        ll a=WM1.top_k_sum(N, 0, i);
        ll b=WM2.top_k_sum(N, i, 3*N);
        chmax(ans, -a-b);
    }
    out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}