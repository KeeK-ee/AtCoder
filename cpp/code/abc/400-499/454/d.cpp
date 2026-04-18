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

/**
 * xの数が違う->No
 * xxや()でそれぞれ削除していく->WA
 * (xx)をxxに置換していく->AC(未証明)
 * 直感的には()を消去してから任意の位置に追加できるから
 * 一度()を全て消去したものが同じであればいい
 */
void solve() {
    // ロジックをちゃんと考える！！！
    string A, B; cin >> A >> B;
    ll xa=0, xb=0;
    for(auto c : A) if(c=='x') xa++;
    for(auto c : B) if(c=='x') xb++;
    if(xa!=xb){ No; return; }

    vc VA, VB;
    for(auto c: A){
        if(VA.empty()) VA.push_back(c);
        else{
            if(c=='x' || c=='(') VA.push_back(c);
            else{
                if(sz(VA)<3) VA.push_back(c);
                else{
                    ll s=sz(VA);
                    if(VA[s-3]=='(' && VA[s-2]=='x' && VA[s-1]=='x' && c==')'){
                        rep(i, 0, 3) VA.pop_back();
                        VA.push_back('x'); VA.push_back('x');
                    }
                    else VA.push_back(c);
                }
            }
        }
    }
    for(auto c: B){
        if(VB.empty()) VB.push_back(c);
        else{
            if(c=='x' || c=='(') VB.push_back(c);
            else{
                if(sz(VB)<3) VB.push_back(c);
                else{
                    ll s=sz(VB);
                    if(VB[s-3]=='(' && VB[s-2]=='x' && VB[s-1]=='x' && c==')'){
                        rep(i, 0, 3) VB.pop_back();
                        VB.push_back('x'); VB.push_back('x');
                    }
                    else VB.push_back(c);
                }
            }
        }
    }
    if(VA==VB) Yes;
    else No;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}