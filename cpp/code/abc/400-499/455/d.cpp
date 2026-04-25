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

// void solve() {
//     // ロジックをちゃんと考える！！！
//     ll N, Q; cin >> N >> Q;
//     vector<tuple<ll, ll, ll>> C(N);
//     rep(i, 0, N){
//         C[i]={-1, -1, i};
//     }
//     rep(qi, 0, Q){
//         ll c, p; cin >> c >> p; c--; p--;
//         auto[x, y, z]=C[p];
//         C[p]={c, y, z};
//         auto[l, m, n]=C[c];
//         if(m!=-1){
//             auto[e, f, g]=C[m];
//             C[m]={-1, f, g};
//         }
//         C[c]={l, p, -1};
//     }
//     // for(auto [a, b, c] : C) cout << a << " " << b  << " " << c << '\n';
//     vl ans(N);
//     queue<ll> q;
//     rep(i, 0, N){
//         auto[a, b, c]=C[i];
//         if(c!=-1) q.push(i);
//     }
//     while(!q.empty()){
//         ll v=q.front(); q.pop();
//         auto[a, b, c]=C[v];
//         ans[c]++;
//         while(a!=-1){
//             ans[c]++;
//             auto[x, y, z]=C[a];
//             a=x;
//         }
//     }
//     for(auto v : ans) cout << v << " ";
// }

/**
 * 各カードについてどの山にいるか管理するとO(N^2)になってしまう
 * ->各カードについて上下のカードのみを管理する
 * 各山の底に動かさない仮想のカードN, N+1....2*Nを考えると実装が少なくなる
 * 各操作について、カードc, カードp, 元々カードcの下にあったカードについての情報が変化する
 * ansを求めるには仮想カードN, N+1...2*Nを始点としてDFSすればいい(各カードについて必ず1回しか訪れないから全体でO(N)で探索できる)
 */
void solve() {
    ll N, Q; cin >> N >> Q;
    vpll G(2*N);
    rep(i, 0, N){
        G[i]={-1, N+i}; G[N+i]={i, -1};
    }
    rep(qi, 0, Q){
        ll c, p; cin >> c >> p; c--; p--;
        G[p].first=c;
        G[G[c].second].first=-1;
        G[c].second=p;
    }
    vl ans(N);
    rep(i, 0, N){
        ll c=-1;
        ll v=N+i;
        while(v!=-1){
            c++; v=G[v].first;
        }
        ans[i]=c;
    }
    for(auto v: ans) cout << v << " ";
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