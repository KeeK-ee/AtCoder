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
 * BFSの計算量=O(N+M)(N:頂点数, M:辺の数)
 * ランプの状態(2^N)を頂点に
 * 操作(M*2^N)を辺にみなした有効グラフを構築
 * 頂点2^N-1に到達できるかの判定問題に帰着
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vl A(N);
    rep(i, 0, N) cin >> A[i];
    vl X(M), Y(M), Z(M);
    rep(i, 0, M) {
        cin >> X[i] >> Y[i] >> Z[i];
        X[i]--; Y[i]--; Z[i]--;
    }

    vvl G(1<<N);
    rep(i, 0, 1<<N){
        rep(j, 0, M){
            //頂点iから操作Mに対応する有向辺を張る
            ll tmp = i;
            if(i&(1<<X[j])) tmp -= (1<<X[j]);
            else tmp += (1<<X[j]);
            if(i&(1<<Y[j])) tmp -= (1<<Y[j]);
            else tmp += (1<<Y[j]);
            if(i&(1<<Z[j])) tmp -= (1<<Z[j]);
            else tmp += (1<<Z[j]);
            G[i].push_back(tmp);
        }
    }

    ll s=0;
    rep(i, 0, N) s+=(A[i]<<i);
    vl dist(1<<N, INF);
    dist[s]=0;
    deque<ll> q;
    q.push_back(s);
    while(!q.empty()){
        auto v = q.front(); q.pop_front();
        for(auto nv : G[v]){
            if(dist[nv]!=INF) continue;
            q.push_back(nv);
            dist[nv] = dist[v]+1;
        }
    }
    if(dist[(1<<N)-1]==INF) out("-1");
    else out(dist[(1<<N)-1]);
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