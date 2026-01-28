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
 * 解けてない
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vpll AB(M);
    rep(i, 0, M) {
        cin >> AB[i].first >> AB[i].second;
        AB[i].first--; AB[i].second--;
    }
    ll Q; cin >> Q;
    vvl query(Q);
    rep(i, 0, Q){
        int op; cin >> op;
        query[i].push_back(op);
        if(op==1){
            ll x; cin >> x; x--;
            query[i].push_back(x);
        }
        else{
            ll u, v; cin >> u >> v; u--; v--;
            query[i].push_back(u); query[i].push_back(v);
        }
    }
    dsu uf(N);
    vb ans;

    rrep(i, 0, Q){
        // query[i]に対して
        if(query[i][0]==1){
            uf.merge(AB[query[i][1]].first, AB[query[i][1]].second);
        }
        else{
            if(uf.same(query[i][1], query[i][2])) ans.push_back(true);
            else ans.push_back(false);
        }
    }

    reverse(all(ans));
    rep(i, 0, sz(ans)){
        if(ans[i]) Yes;
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