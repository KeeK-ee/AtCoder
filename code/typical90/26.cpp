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

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
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
 * これは二部グラフの問題と気づけるか
 * 片方を黒で塗った時, 白もしくは黒の頂点の個数はN/2を超える(必ずしも半々で塗れるとは限らない)
 * 木は必ず二部グラフ
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vvl G(N);
    rep(i, 0, N-1){
        ll a, b; cin >> a >> b; a--; b--;
        G[a].push_back(b); G[b].push_back(a);
    }

    vl ans;
    queue<pll> q; vb vis(N);
    q.push({0, 1}); vis[0]=true; ans.push_back(0);
    while(!q.empty()){
        auto [v, p] = q.front(); q.pop();
        for(auto to : G[v]){
            if(vis[to]) continue;
            vis[to]=true;
            int np = 1-p;
            if(np) ans.push_back(to);
            q.push({to, np});
        }
    }

    sort(all(ans));
    vb ex(N);
    rep(i, 0, sz(ans)) ex[ans[i]]=true;
    if(sz(ans)>=N/2){
        ll cnt=0;
        rep(i, 0, N) {
            if(ex[i]) {
                cout << i+1 << " ";
                cnt++;
                if(cnt>=N/2) break;
            }
        }
    }
    else{
        ll cnt=0;
        rep(i, 0, N) {
            if(!ex[i]) {
                cout << i+1 << " ";
                cnt++;
                if(cnt>=N/2) break;
            }
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