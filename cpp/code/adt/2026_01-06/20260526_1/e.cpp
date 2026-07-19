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
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
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
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)
#define se second
#define fi first

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

// A進法の string -> 10進法の ll
ll baseToDec(const string& S, ll A) {
    ll res = 0;
    for (char c : S) {
        ll digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else {
            digit = c - 'A' + 10; // 11進法以上 (A~Z) に対応
        }
        res = res * A + digit;
    }
    return res;
}

// 10進法の ll -> A進法の string
string decToBase(ll N, ll A) {
    if (N == 0) return "0";
    
    string res = "";
    while (N > 0) {
        int rem = N % A;
        if (rem < 10) {
            res += (char)('0' + rem);
        } else {
            res += (char)('A' + rem - 10); // 11進法以上 (A~Z) に対応
        }
        N /= A;
    }
    // 下の桁から順番に文字列に足されているので、最後に反転させる
    reverse(res.begin(), res.end());
    
    return res;
}

/**
 * 0, 2, 4, 6, 8のみからなる
 * ->全体を/2する
 * 0, 1, 2, 3, 4のみからなる(0, 1, 2, 3, 4, 10, 11, 12 ...)
 * ->これは5進法そのもの
 * ->N番目は5進法でどう書けるか？
 * 5進法の0, 1, 2, 3, 4, 10, 11, 12 ...は
 * 10進法の0, 1, 2, 3, 4, 5, 6, 7 ...だから
 * 求める数=N-1の5進法表記の各桁を(10進法表記における)2倍したもの
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    string ans=decToBase(N-1, 5);
    for(auto c : ans){
        ll a=(c-'0');
        cout << 2*a;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}