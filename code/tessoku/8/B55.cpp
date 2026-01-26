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

const ll INF = 1e18;
const ll MOD = 1000000007;
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
 * x以上の最小値->にぶたん
 * ではx以下の最大値は？
 * -> すべての要素を-1倍した世界でにぶたんして, 結果を-1倍
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll Q; cin >> Q;
    set<ll> s1, s2;
    rep(qi, 0, Q){
        int op; cin >> op;
        if(op==1){
            ll x; cin >> x;
            s1.insert(x);
            s2.insert(-x);
        }
        else{
            ll x; cin >> x;
            auto it1 = s1.lower_bound(x);
            auto it2 = s2.lower_bound(-x);
            ll abs1=INF, abs2=INF;
            if(it1 != s1.end()) abs1 = *it1 - x;
            if(it2 != s2.end()) abs2 = *it2 + x;
            if(abs1 == INF && abs2 == INF) out("-1");
            else out(min(abs1, abs2));
        }
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