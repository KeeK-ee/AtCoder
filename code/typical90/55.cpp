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

/**
 * 単純に考えるとN<=100におけるO(N^5)で10^10回の計算は間に合わないと考えてしまう
 * だが, この問題は全探索が間に合う
 * ->nC5はだいたいN^5/5!=N^5/120で定数倍が非常に軽い
 * long longの最大値はだいたい10^18程度なので, 10^9を5つかけるとオーバーフローする
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, P, Q; cin >> N >> P >> Q;
    vl A(N);
    rep(i, 0, N){
        ll a; cin >> a;
        a %= P; A[i]=a;
    }
    ll ans=0;
    rep(i, 0, N)rep(j, i+1, N)rep(k, j+1, N)rep(l, k+1, N)rep(m, l+1, N){
        ll a = (A[i]*A[j])%P;
        ll b = (A[k]*A[l])%P;
        ll c = (a*b)%P;
        ll d = (c*A[m])%P;
        if(d==Q) ans++;
    }
    out(ans);
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