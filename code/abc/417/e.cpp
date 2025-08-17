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

//#include "../../../ac-library-master/atcoder/dsu.hpp"
//#include <atcoder/all>
//using namespace atcoder;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

const ll INF = 1e18;
const int MOD = 1000000007;
const string LOWALP = "abcdefghijklmnopqrstuvwxyz";
const string UPALP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (int i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (int i = (int)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

int N, M, X, Y;
vvi G(M);
vector<bool> visited(N);
vi ans;
bool finish;

void dfs(int v){
    //今頂点vにきた。
    if(finish) return;
    visited[v]=true;
    ans.push_back(v);
    if(v==Y){
        finish = true;
        return;
    }
    for(auto to : G[v]){
        if(finish) return;
        if(visited[to]) continue;
        dfs(to);
    }
}

void solve() {
    cin >> N >> M >> X >> Y;
    X--;Y--;
    G = vvi(N);
    rep(i, 0, M){
        int u, v;
        cin >> u >> v;
        u--;v--;
        G[u].push_back(v);G[v].push_back(u);
    }
    rep(i, 0, N) sort(all(G[i]));
    visited = vector<bool>(N, false);
    finish = false;
    dfs(X);
    rep(i, 0, sz(ans)) cout << ans[i] << ' ';
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}