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

/**
 * 各要素は0~K
 * 第1項：0~K=A1
 * 第2項：0~(K-A1)/2
 * 第3項：0~(K-A1-A2)/3
 * 
 * Nが小さいことに着目すると前から決めていくN重ループの再帰全探索をしたくなる
 * 辞書順は出力直前にソートすればOK
 * 数列の後ろにいくにつれて、候補がかなり少なくなるはず(/Nが効いていそう)
 * 計算量見積はできません、、、、
 */
void solve() {
    ll N, K; cin >> N >> K;
    Vec<Vec<ll>> Ans;

    Vec<ll> Tmp;
    auto dfs =[&](auto dfs, ll idx, ll sum) -> void {
        if(idx==N){
            if((K-sum)%idx!=0) return;
            ll v=(K-sum)/idx;
            Tmp.push_back(v);
            dfs(dfs, idx+1, sum+idx*v);
            Tmp.pop_back();
        }
        else if(idx==N+1){
            if(sum!=K) return;
            Ans.push_back(Tmp); return;
        }
        else{
            rep(v, 0, (K-sum)/idx+1){
                Tmp.push_back(v);
                dfs(dfs, idx+1, sum+idx*v);
                Tmp.pop_back();
            }
        }
    };
    dfs(dfs, 1, 0);
    sort(all(Ans));
    for(auto vec : Ans){
        rep(j, 0, sz(vec)) cout << vec[j] << " ";
        cout << '\n'; 
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}