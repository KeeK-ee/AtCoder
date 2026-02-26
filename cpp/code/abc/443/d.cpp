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
 * 行番号の小さい順にその位置で確定させる貪欲
 * ある列cの行番号r確定させたときに, c+1, c-1列目の行番号が2以上離れているときはr+1にする必要がある. さらにこの2つの列の行番号はこれで確定する(c列目の行番号は最も小さいから)
 * priority_queueでO(NlogN)(一度確定した列は二度と更新されない)
 * よく見たらダイクストラなんやこれ
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vl R(N);
    rep(i, 0, N){
        cin >> R[i];
        R[i]--;
    }
    vl A(N);
    rep(i, 0, N) A[i]=R[i];
    priority_queue<pll, vector<pll>, greater<pll>> q;
    rep(i, 0, N){
        q.push({R[i], i});
    }
    // 行番号の小さい順に貪欲に決める
    while(!q.empty()){
        auto [r, c] = q.top(); q.pop();
        if(A[c] != r) continue; // すでに確定している場合はAが異なるからスキップ
        if(c <= N-2 && A[c+1]>=r+2){
            A[c+1]=r+1;
            q.push({r+1, c+1});
        }
        if(1 <= c && A[c-1]>=r+2){
            A[c-1]=r+1;
            q.push({r+1, c-1});
        }
    }
    ll ans=0;
    rep(i, 0, N) ans += (R[i]-A[i]);
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