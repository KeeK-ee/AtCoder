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
#include <unordered_set>
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

/**
 * D:「マスに対する色塗りあるある」クエリ後ろから見がち を発動(ABC464-E)
色が決定していないマスのsetをうまく管理する 管理が甘く(タイルが存在するマスをeraseしていなかった)ためにTLEで3ペナ
 */
void solve() {
    ll N, Q; cin >> N >> Q;
    Vec<int> OP(Q);
    Vec<ll> X(Q, -1);
    Vec<char> C(Q, '.');
    Vec<bool> not_tile(N, true);
    unordered_set<ll> not_decide; rep(i, 0, N) not_decide.insert(i);
    Vec<char> ans(N, '.');
    rep(i, 0, Q){
        int op; cin >> op; OP[i]=op;
        if(op==1){
            ll x; cin >> x; x--; X[i]=x;
            not_tile[x]=not not_tile[x];
            if(not not_tile[x]){
                if(not_decide.count(x)) not_decide.erase(x);
            }
            else{
                if(ans[x]=='.') not_decide.insert(x);
            }
        }
        else{
            char c; cin >> c; C[i]=c;
        }
    }

    // for(auto v : not_tile) cout << v << " ";
    // cout << '\n';

    rrep(i, 0, Q){
        int op=OP[i];
        if(op==1){
            ll x=X[i];
            not_tile[x]=not not_tile[x];
            if(not not_tile[x]){
                if(not_decide.count(x)) not_decide.erase(x);
            }
            else{
                if(ans[x]=='.') not_decide.insert(x);
            }
            // cout << i << ":";
            // for(auto v : not_tile) cout << v << " ";
            // cout << '\n';
        }
        else{
            auto it=not_decide.begin();
            char c=C[i];
            while(it!=not_decide.end()){
                if(not_tile[*it]){
                    ans[*it]=c;
                    // cout  << i << ":" << *it << " " << c << '\n';
                    it=not_decide.erase(it);
                }
                else it=next(it);
            }
        }
    }

    rep(i, 0, N) {
        if(ans[i]=='.') cout << 'a';
        else cout << ans[i];
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