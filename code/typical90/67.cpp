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
using namespace std;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;

const ll INF = 1e18;
const ll MOD = 998244353;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

using ull = unsigned long long;

/**
 * N進法展開
 * ゴミ
 * 桁が大きい時はなるべくstringで受け取る方法を考える
 * n進法->10進法はres = res*n + (s[i]-'0')でsの上から見てできる
 * 10進法->n進法はwhile(x>0) { res = (x%n) +res; x /= n; }でできる
 * 
 * 適宜関数を使おう
 */
void solve() {
// ロジックをちゃんと考える！！！
    string N; cin >> N;
    ull K; cin >> K;
    if(N == "0"){
        out(0);
        return;
    }

    auto b8tol = [&](string s) -> ull {
        ull res = 0;
        rep(i, 0, sz(s)){
            res = res*8 + (s[i]-'0');
        }
        return res;
    };

    auto ltob9 = [&](ull x) -> string {
        string res="";
        while(x > 0){
            res = (char)(x%9 + '0') + res;
            x /= 9;
        }
        return res;
    };

    rep(ki, 0, K){
        N = ltob9(b8tol(N));
        rep(i, 0, sz(N))if(N[i]=='8')N[i]='5';
    }

    out(N);
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