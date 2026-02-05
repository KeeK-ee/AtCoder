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

const ll INF = 1000000000000000000LL; // 10^18
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
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

ull power(ull a, ull b, ull mod){
    ull p=a, ans=1;
    rep(i, 0, 30){
        if((b>>i)%2) {
            ans *= p;
            ans %= mod;
        }
        p = (p*p) % mod;       
    }
    return ans;
}

void solve() {
// ロジックをちゃんと考える！！！
    ull L, R; cin >> L >> R;
    ull ans=0, m=1000000007;

    vector<ull> i10(20); i10[0]=1;
    rep(i, 1, 20) i10[i] = i10[i-1]*10;

    ull ldig=0, rdig=0, Ltmp=L, Rtmp=R;
    while(Ltmp != 0) {
        Ltmp /= 10;
        ldig++;
    }
    while(Rtmp != 0) {
        Rtmp /= 10;
        rdig++;
    }
    
    rep(i, ldig, rdig+1){
        ull l = max(i10[i-1], L);
        ull r = min(i10[i]-1, R);
        if (l > r) continue;
        ans += ((((l+r)%m)*((r-l+1)%m))%m)*i*power(2, m-2, m);
        ans %= m;
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