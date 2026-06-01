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

// void solve() {
//     ll N; cin >> N;
//     ll sx, sy, gx, gy;
//     cin >> sx >> sy >> gx >> gy;
//     ll si, gi;
//     vb VIS(N); queue<ll> Q;
//     vl X(N), Y(N), R(N);
//     rep(i, 0, N) {
//         cin >> X[i] >> Y[i] >> R[i];
//         if(llpow(X[i]-sx, 2)+llpow(Y[i]-sy, 2)==llpow(R[i], 2)){
//             si=i; VIS[i]=true; Q.push(i);
//         }
//         else if(llpow(X[i]-gx, 2)+llpow(Y[i]-gy, 2)==llpow(R[i], 2)){
//             gi=i;
//         }
//     }
//     while(!Q.empty()){
//         auto idx=Q.front(); Q.pop();
//         rep(i, 0, N) if(!VIS[i]){
//             ll d=llpow(X[idx]-X[i], 2)+llpow(Y[idx]-Y[i], 2);
//             if(llpow(abs(R[idx]-R[i]), 2)<=d&&d<=llpow(R[idx]+R[i], 2)){
//                 VIS[i]=true; Q.push(i);
//             }
//         }
//     }
//     if(VIS[gi]) Yes;
//     else No;
// }

/**
 * グラフを構築してから普段通りのBFSの方が楽かも
 */
void solve() {
    ll N; cin >> N;
    ll sx, sy, gx, gy;
    cin >> sx >> sy >> gx >> gy;
    ll si, gi;
    vl X(N), Y(N), R(N);
    vb VIS(N); queue<ll> Q;
    rep(i, 0, N) {
        cin >> X[i] >> Y[i] >> R[i];
        if(llpow(X[i]-sx, 2)+llpow(Y[i]-sy, 2)==llpow(R[i], 2)){
            si=i; VIS[i]=true; Q.push(i);
        }
        else if(llpow(X[i]-gx, 2)+llpow(Y[i]-gy, 2)==llpow(R[i], 2)){
            gi=i;
        }
    }
    vvl G(N);
    rep(i, 0, N-1)rep(j, i+1, N){
        ll d=llpow(X[i]-X[j], 2)+llpow(Y[i]-Y[j], 2);
        if(llpow(R[i]-R[j], 2)<=d&&d<=llpow(R[i]+R[j], 2)){
            G[i].push_back(j); G[j].push_back(i);
        }
    }
    while(!Q.empty()){
        auto v=Q.front(); Q.pop();
        for(auto to : G[v]) if(!VIS[to]){
            VIS[to]=true;
            Q.push(to);
        }
    }
    if(VIS[gi]) Yes;
    else No;
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