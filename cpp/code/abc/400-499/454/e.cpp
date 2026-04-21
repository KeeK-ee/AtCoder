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
 * 判定
 * パリティを考える。移動の度にパリティが変化する
 * Nが奇数->SとGのパリティは等しい（黒）。残りN^2-3マスは白->黒->...->白
 * だがN^2-3は偶数のため矛盾
 * Nが偶数->(A, B)が黒だとダメ
 * 
 * あとは2列ずつ見てうまく構築する（ムズイ）
 * - (A, B)をうまく避けながら進む
 * - (A, B)をまだ通過していない
 * - (A, B)をすでに通過した
 * に分けて動きを実装
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, A, B; cin >> N >> A >> B; A--; B--;

    // 判定
    if(N%2){ No; return; }
    else if((A+B)%2==0) { No; return; }
    Yes;

    // 構築
    string ans="";
    ll y=0, x=0;
    while(true){
        if(N<=x) break;
        if(x==2*(B/2)||x==2*(B/2)+1){
            // (A, B)を避ける
            // 右下左下
            rep(i, 0, A/2) ans+="RDLD";
            if(B%2) ans+="DR";
            else ans+="RD";
            rep(i, 0, (N-A-1)/2) ans+="DLDR";
            ans += 'R';
            x+=2; y=N-1;
        }
        else if(x<2*(B/2)){
            // 下→右→上→右
            ans += string(N-1, 'D');
            ans += 'R';
            ans += string(N-1, 'U');
            ans += 'R';
            x+=2;
        }
        else if(2*(B/2)+1<x){
            // 上→右→下→右
            ans += string(N-1, 'U');
            ans += 'R';
            ans += string(N-1, 'D');
            ans += 'R';
            x+=2;
        }
        else{
            assert(false);
        }
    }
    ans.pop_back();
    out(ans);
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