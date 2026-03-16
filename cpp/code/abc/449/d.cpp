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
#include <random>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

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
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;
using bint = cpp_int;

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

/**
 * x座標は固定しそう
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll L, R, D, U; cin >> L >> R >> D >> U;
    ll ans=0;
    rep(x, L, R+1){
        // x座標をxで固定し, x上の黒を数える
        ll p = max(abs(D), abs(U)), q=min(abs(D), abs(U));
        ll a=abs(x);
        if(p<=a) {
            if(!(a%2)) ans+=(U-D+1);
        }
        else if(a<=q){
            ll c=U-D+1;
            if(c%2==0) ans+=c/2;
            else {
                if(U%2) ans+=c/2;
                else ans+=(c+1)/2;
            }
        }
        else{
            ll nq,np;
            if(q==abs(D)) {nq=D; np=U;}
            else {nq=U; np=D;}
            ll c1;
            if(x>=0) c1=x-nq+1;
            else c1=-nq-x+1;
            if(!(a%2)) ans+=(c1);
            // cout << "c1:" << c1 << " ";
            ll c2=U-D+1-(c1);
            if(c2%2==0) ans+=c2/2;
            else {
                if(np%2) ans+=c2/2;
                else ans+=(c2+1)/2;
            }
            // cout << "c2:" << c2 << " ";
        }
        // cout << ans << " ";
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