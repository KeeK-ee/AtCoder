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

/**
 * (x, y)の少なくとも一方は、全決勝のうち過半数に出場している
 * 過半数に出場している人の候補は高々4人(Nが奇数のときは高々2人)であるから、候補ごとに独立に考えて間に合う 候補列挙にO(N)
 * 候補xを固定したとき、xが出場していない全ての決勝について、人ごとの出場回数をカウント　M-(xの出場回数)であればOK 各xに対してO(N)全体でもO(N)
 * 重複はset<pair>で回避
 */
void solve() {
    ll N, M; cin >> N >> M;
    set<pll> s;
    ll half=(M+1)/2;
    vl A(M), B(M);
    rep(i, 0, M) {
        cin >> A[i] >> B[i]; A[i]--; B[i]--;
    }
    vl cnt(N);
    rep(i, 0, M){ cnt[A[i]]++; cnt[B[i]]++; }
    vl can;
    rep(i, 0, N) if(cnt[i]>=half) can.push_back(i);
    if(can.empty()){ out(0); return; }
    for(auto c : can){
        vl cnt2(N);
        rep(i, 0, M){
            if(A[i]!=c and B[i]!=c){
                cnt2[A[i]]++; cnt2[B[i]]++;
            }
        }
        rep(i, 0, N){
            if(i==c) continue;
            if(cnt2[i]==M-cnt[c]){
                ll x=c, y=i;
                if(x>y) swap(x, y);
                s.insert({x, y});
            }
        }
    }
    out(sz(s));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}