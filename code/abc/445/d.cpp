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
using ull = unsigned long long;
using ld = long double;
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

const ll INF = 8000000000000000000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * 感覚としては大きいものから配置していきそう
 * どう配置していけばいいか全く思いつかなかった
 * ☆分割の手順から"縦もしくは横が最大のピースが必ず存在する"
 * - (縦, 横, idx),  (横, 縦, idx)をそれぞれ別のpqに入れる
 * - (y, x)=(0, 0)からスタート
 * - 縦もしくは横が最大のものを取り出して, H, W, y, xを更新
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll H, W, N; cin >> H >> W >> N;
    vl h(N), w(N);
    rep(i, 0, N) cin >> h[i] >> w[i];

    priority_queue<tuple<ll, ll, ll>> qt, qy;
    rep(i, 0, N){
        qt.push({h[i], w[i], i});
        qy.push({w[i], h[i], i});
    }

    vb used(N);
    vpll ans(N);
    ll y=0, x=0;
    while(!qt.empty() && !qy.empty()){
        auto[h1, w1, i1]=qt.top();
        if(used[i1]){
            qt.pop(); continue;
        }
        if(h1==H){
            qt.pop();
            ans[i1].first=y; ans[i1].second=x;
            x+=w1; W-=w1;
            used[i1]=true;
            continue;
        }

        auto[w2, h2, i2]=qy.top();
        if(used[i2]){
            qy.pop(); continue;
        }
        if(w2==W){
            qy.pop();
            ans[i2].first=y; ans[i2].second=x;
            y+=h2; H-=h2;
            used[i2]=true;
            continue;
        }
    }

    rep(i, 0, N) cout << ans[i].first+1 << " " << ans[i].second+1 << '\n';
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