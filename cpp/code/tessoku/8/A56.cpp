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

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
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

/**
 * ハッシュを計算する
 * 1. 文字列を数列に(a->1, b->2...(※0始まりはダメ))
 * 2. S[0.. i]のハッシュを計算(累積和みたいなノリ)
 * 3. b進法でハッシュを計算するとしてb^iを前計算(b=100なのはアルファベットが26個だから？)
 * 4. S[x, y]のハッシュ：S[0, y]のハッシュ - S[0, x]のハッシュ*b^(y-x+1)
 * ハッシュは巨大な数になるため大きい数でmodを取る(mint使う)
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, Q; cin >> N >> Q;
    string S; cin >> S;

    vl T(N); //Sを数字に変換a->1, b->2...
    rep(i, 0, N) T[i] = (S[i]-'a')+1;

    vector<mint> U(N); // U[i]: S[0, i]のハッシュ値
    U[0]=T[0];
    rep(i, 1, N) U[i]=(U[i-1]*100)+T[i];

    vector<mint> B(N+1); // B[i]=100^iのmod998
    B[0]=1;
    rep(i, 1, N+1) B[i] = B[i-1]*100;

    auto h = [&](ll x, ll y) -> mint {
        //S[x, y]のハッシュをmod998で計算する
        mint res = 0;
        if(x-1<0) res = U[y];
        else res = U[y] - U[x-1]*B[y-x+1];
        return res.val();
    };

    rep(i, 0, Q){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        if(h(a, b).val()==h(c, d).val()) Yes;
        else No;
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