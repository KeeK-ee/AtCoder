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
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

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

void solve() {
// ロジックをちゃんと考える！！！
    string T; cin >> T;
    ll N; cin >> N;
    vl A(N);
    vector<vs> S(N);
    rep(i, 0, N){
        ll a; cin >> a; A[i]=a;
        rep(j, 0, a){
            string s; cin >> s;
            S[i].push_back(s);
        }
    }

    vvl dp(N+1, vl(sz(T)+1, INF));
    rep(i, 0, N+1) dp[i][0]=0;
    
    rep(i, 1, N+1)rep(j, 0, sz(T)+1){
        chmin(dp[i][j], dp[i-1][j]);
        rep(k, 0, A[i-1]){
            if(j-sz(S[i][k])<0) chmin(dp[i+1][j], dp[i][j]);
            else if(S[i][k]==T.substr(j-sz(S[i][k]), sz(S[i][k]))) dp[i][j] = min(dp[i-1][j], dp[i-1][j-sz(S[i][k])]+1);
            else chmin(dp[i+1][j], dp[i][j]);
        }
    }

    if(dp[N][sz(T)]==INF) out(-1);
    else out(dp[N][sz(T)]);
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